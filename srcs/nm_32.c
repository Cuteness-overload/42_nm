#include "ft_nm.h"

static int symbols_32(Elf32_Ehdr *elf_header, Elf32_Shdr *shs_table, uint16_t i, char *file_content, flags_t *flags, size_t file_size)
{
	char 		file_endian = elf_header->e_ident[EI_DATA];

	// Get sh_link to determine string table index (sh_link of symbol table is a string table)
	// Get sh_offset to determine where the symbol table is located
	uint32_t	sh_link = uint32_to_host(shs_table[i].sh_link, file_endian);
	uint32_t	sh_offset = uint32_to_host(shs_table[i].sh_offset, file_endian);

	// Get the symbol table from the file content
	// Check if the offset is within the bounds of the file size
	if (sh_offset >= file_size)
		return 1;
	Elf32_Sym	*sym_table = (Elf32_Sym *)(file_content + sh_offset);

	// Get the number of symbols in the symbol table
	// Verify symbol table entries are correct size
	if (sizeof(Elf32_Sym) != uint32_to_host(shs_table[i].sh_entsize, file_endian))
		return 1;
	size_t		sym_count = (uint32_to_host(shs_table[i].sh_size, file_endian) / sizeof(Elf32_Sym));
	
	// Get string table from the file content
	// check that the offset is within the bounds of the file size
	if (uint32_to_host(shs_table[sh_link].sh_offset, file_endian) >= file_size)
		return 1;
	char		*str_table = file_content + uint32_to_host(shs_table[sh_link].sh_offset, file_endian);

	// Allocate memory for the symbols
	sym_t		*symbols = malloc(sizeof(sym_t) * sym_count);
	if (!symbols)
		return perror(strerror(errno)), 2;
	
	// Iterate through the symbol table and populate the symbols array
	// First symbol entry is reserved, so we start at 1
	size_t sym_index = 0;
	for (size_t j = 1; j < sym_count; j++) {
			// Get symbol address (value)
			symbols[sym_index].value = uint32_to_host(sym_table[j].st_value, file_endian);

			// Set the letter representing the symbol type
			symbols[sym_index].letter = get_letter_32(sym_table[j], shs_table, str_table, file_endian);

			// Get the symbol name from the string table -- Set to "(null)" if invalid
			if (is_valid_cstring(str_table + uint32_to_host(sym_table[j].st_name, file_endian),
				str_table + uint32_to_host(shs_table[sh_link].sh_size, file_endian)))
				symbols[sym_index].name = str_table + uint32_to_host(sym_table[j].st_name, file_endian);
			else
				symbols[sym_index].name = "(null)";

			// set boolean flags based on the symbol type
			symbols[sym_index].is_external = ELF32_ST_BIND(sym_table[j].st_info) != STB_LOCAL;
			symbols[sym_index].is_undefined = (uint16_to_host(sym_table[j].st_shndx, file_endian) == SHN_UNDEF);

			sym_index++;
	}

	// Check sort flags
	if (!flags->p && !flags->u) {
		if (flags->r)
			reverse_merge_sort(symbols, 0, sym_index - 1);
		else
			merge_sort(symbols, 0, sym_index - 1);
	}

	for (size_t j = 0; j < sym_index; j++) {
		if (flags->u && !symbols[j].is_undefined)
			continue; // Skip defined symbols if -u flag is set
		else if (flags->g && !symbols[j].is_external)
			continue; // Skip non-external symbols if -g flag is set
		else if (!flags->a && ((symbols[j].letter == 'N') || (symbols[j].letter =='A') || (symbols[j].letter == 'a')))
			continue; // Skip debugging symbols if -a flag is not set
		// now to print the symbol
		if (symbols[j].is_undefined)
			ft_printf("%16c %c %s\n", ' ', symbols[j].letter, symbols[j].name);
		else
			ft_printf("%016x %c %s\n", symbols[j].value, symbols[j].letter, symbols[j].name);
	}
	free(symbols);

	return 0;
}

int ft_nm_32(char *file_content, struct stat file_stat, const char *filename, flags_t *flags)
{
	Elf32_Ehdr	*elf_header = (Elf32_Ehdr *)file_content;
	// need to handle endianness
	char 		file_endian = elf_header->e_ident[EI_DATA];
	uint16_t	e_shnum = uint16_to_host(elf_header->e_shnum, file_endian);
	uint32_t	e_shoff = uint32_to_host(elf_header->e_shoff, file_endian);
	uint16_t	e_shstrndx = uint16_to_host(elf_header->e_shstrndx, file_endian);
	uint16_t	e_type = uint16_to_host(elf_header->e_type, file_endian);
	uint16_t	e_machine = uint16_to_host(elf_header->e_machine, file_endian);

	// Check machine architecture specified in ELF header
	if (e_machine == EM_NONE)
		return ft_printf("ft_nm: '%s': Architecture not handled\n", filename);

	// Check if the file is an executable, shared object, or relocatable file
	if (e_type != ET_EXEC && e_type != ET_DYN && e_type != ET_REL)
		return ft_printf("ft_nm: '%s': file format not recognized\n", filename);

	// check for e_shnum value. Cannot be greater than SHN_LORESERVE
	// also check if e_shoff greater than file size (section header offset)
	if ((e_shnum >= SHN_LORESERVE) || (e_shoff >= (long unsigned int)file_stat.st_size))
		return ft_printf("ft_nm: '%s': file format not recognized\n", filename);

	Elf32_Shdr	*shs_table = (Elf32_Shdr *)(file_content + e_shoff);

	// iterate through section headers and find symbol table
	for (uint16_t i = 0; i < e_shnum; i++) {
		// check if we are in bounds of string table
		// sh_name is Elf64_Word, sh_size is Elf64_Xword
		if (uint32_to_host(shs_table[i].sh_name, file_endian) > uint32_to_host(shs_table[e_shstrndx].sh_size, file_endian))
			return ft_printf("ft_nm: '%s': file format not recognized\n", filename);
	
		int ret;
		if (uint32_to_host(shs_table[i].sh_type, file_endian) == SHT_SYMTAB) {
			if ((ret = symbols_32(elf_header, shs_table, i, file_content, flags, file_stat.st_size))) {
				if (ret == 1)
					return ft_printf("ft_nm: '%s': file format not recognized\n", filename);
				else
					return 1;
			}
			else
				return 0; // Successfully processed the symbol table
		}
	}
	ft_printf("ft_nm: '%s': no symbols\n", filename);
	return 0; // No symbol table found
}