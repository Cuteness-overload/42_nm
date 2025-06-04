#include "ft_nm.h"

static int symbols_64(Elf64_Shdr *shs_table, uint16_t i, char *file_content, flags_t *flags, size_t file_size, const char *filename)
{
	Elf64_Ehdr	*elf_header = (Elf64_Ehdr *)file_content;
	char 		file_endian = elf_header->e_ident[EI_DATA];

	// Get sh_link to determine string table index (sh_link of symbol table is a string table)
	// Get sh_offset to determine where the symbol table is located
	uint32_t	sh_link = uint32_to_host(shs_table[i].sh_link, file_endian);
	uint64_t	sh_offset = uint64_to_host(shs_table[i].sh_offset, file_endian);

	// Get the symbol table from the file content
	// Check if the offset is within the bounds of the file size
	if (sh_offset >= file_size)
		return 1;
	Elf64_Sym	*sym_table = (Elf64_Sym *)(file_content + sh_offset);

	// Get the number of symbols in the symbol table
	// Verify symbol table entries are correct size
	if (sizeof(Elf64_Sym) != uint64_to_host(shs_table[i].sh_entsize, file_endian))
		return 1;
	size_t		sym_count = (uint64_to_host(shs_table[i].sh_size, file_endian) / sizeof(Elf64_Sym));
	
	// Get string table from the file content
	// check that the offset is within the bounds of the file size
	if (uint64_to_host(shs_table[sh_link].sh_offset, file_endian) >= file_size)
		return 1;
	char		*str_table = file_content + uint64_to_host(shs_table[sh_link].sh_offset, file_endian);

	// Allocate memory for the symbols
	sym_t		*symbols = malloc(sizeof(sym_t) * sym_count);
	if (!symbols)
		return perror(strerror(errno)), 2;
	
	// Iterate through the symbol table and populate the symbols array
	// First symbol entry is reserved, so we start at 1
	size_t sym_index = 0;
	for (size_t j = 1; j < sym_count; j++) {
			// Get symbol address (value)
			symbols[sym_index].value = uint64_to_host(sym_table[j].st_value, file_endian);

			// Set the letter representing the symbol type
			symbols[sym_index].letter = get_letter_64(sym_table[j], shs_table, str_table, file_endian);

			// Get the symbol name from the string table -- Set to "(null)" if invalid
			if (is_valid_cstring(str_table + uint32_to_host(sym_table[j].st_name, file_endian),
				str_table + uint64_to_host(shs_table[sh_link].sh_size, file_endian)))
				symbols[sym_index].name = str_table + uint32_to_host(sym_table[j].st_name, file_endian);
			else
				symbols[sym_index].name = "(null)";

			// set boolean flags based on the symbol type
			symbols[sym_index].is_external = ELF64_ST_BIND(sym_table[j].st_info) != STB_LOCAL;
			symbols[sym_index].is_undefined = (uint16_to_host(sym_table[j].st_shndx, file_endian) == SHN_UNDEF);

			sym_index++;
	}

	if (flags->multiple_files)
		ft_printf("\n%s:\n", filename); // Print filename if multiple files are provided
	sort_print(symbols, sym_index, flags);
	free(symbols);

	return 0;
}

int ft_nm_64(char *file_content, struct stat file_stat, const char *filename, flags_t *flags)
{
	Elf64_Ehdr	*elf_header = (Elf64_Ehdr *)file_content;
	// need to handle endianness
	char 		file_endian = elf_header->e_ident[EI_DATA];
	uint16_t	e_shnum = uint16_to_host(elf_header->e_shnum, file_endian);
	uint64_t	e_shoff = uint64_to_host(elf_header->e_shoff, file_endian);
	uint16_t	e_shstrndx = uint16_to_host(elf_header->e_shstrndx, file_endian);
	uint16_t	e_type = uint16_to_host(elf_header->e_type, file_endian);
	uint16_t	e_machine = uint16_to_host(elf_header->e_machine, file_endian);

	// Check machine architecture specified in ELF header
	if (e_machine == EM_NONE)
		return ft_printf("ft_nm: '%s': Architecture not handled\n", filename);

	// Check if the file is an executable, shared object, or relocatable file
	if (e_type != ET_EXEC && e_type != ET_DYN && e_type != ET_REL)
		return ft_printf("ft_nm: %s: file format not recognized\n", filename);

	// check for e_shnum value. Cannot be greater than SHN_LORESERVE
	// also check if e_shoff greater than file size (section header offset)
	if ((e_shnum >= SHN_LORESERVE) || (e_shoff >= (long unsigned int)file_stat.st_size))
		return ft_printf("ft_nm: %s: file format not recognized\n", filename);

	Elf64_Shdr	*shs_table = (Elf64_Shdr *)(file_content + e_shoff);

	// iterate through section headers and find symbol table
	for (uint16_t i = 0; i < e_shnum; i++) {
		// check if we are in bounds of string table
		// sh_name is Elf64_Word, sh_size is Elf64_Xword
		if (uint32_to_host(shs_table[i].sh_name, file_endian) > uint64_to_host(shs_table[e_shstrndx].sh_size, file_endian))
			return ft_printf("ft_nm: %s: file format not recognized\n", filename);
	
		int ret;
		if (uint32_to_host(shs_table[i].sh_type, file_endian) == SHT_SYMTAB) {
			if ((ret = symbols_64(shs_table, i, file_content, flags, file_stat.st_size, filename)) != 0) {
				if (ret == 1)
					return ft_printf("ft_nm: %s: file format not recognized\n", filename);
				else
					return 1;
			}
			else
				return 0; // Successfully processed the symbol table
		}
	}
	if (flags->multiple_files)
		ft_printf("\n%s:\n", filename); // Print filename if multiple files are provided
	ft_printf("ft_nm: %s: no symbols\n", filename);
	return 0; // No symbol table found
}