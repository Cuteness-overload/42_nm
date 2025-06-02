#include "ft_nm.h"

char get_letter_64(Elf64_Sym sym, Elf64_Shdr *shs_table, char *str_table, char file_endian, Elf64_Ehdr *elf_header) {
	char 		letter = '?';

	uint8_t 	bind = ELF64_ST_BIND(sym.st_info);
	uint8_t		type = ELF64_ST_TYPE(sym.st_info);
	uint16_t	shndx = uint16_to_host(sym.st_shndx, file_endian);

	const		Elf64_Shdr section = shs_table[shndx];
	const char *section_name = str_table + uint32_to_host(section.sh_name, file_endian);
	uint32_t	section_type = uint32_to_host(section.sh_type, file_endian);
	uint64_t	section_flags = uint64_to_host(section.sh_flags, file_endian);

	if (bind == STB_WEAK) {
		if (type == STT_OBJECT)
			(shndx == SHN_UNDEF) ? (letter = 'v') : (letter = 'V');
		else
			(shndx == SHN_UNDEF) ? (letter = 'w') : (letter = 'W');
	}
	else if (type == STT_GNU_IFUNC)
		letter = 'i';
	else if (bind == STB_GNU_UNIQUE)
		letter = 'u';
	else if (shndx == SHN_UNDEF)
		letter = 'U';
	else if (shndx == SHN_ABS)
		letter = 'A';
	else if (shndx == SHN_COMMON)
		letter = 'c';
	// Handle debug sections
	else if (section_name && ( ft_strncmp(section_name, ".debug", 6) == 0 ||
		  					ft_strncmp(section_name, ".stab", 5) == 0 ||
		  					ft_strncmp(section_name, ".stabstr", 8) == 0)) {
		letter = 'N'; 
	}
	// handle small bss and data sections
	else if (section_flags & SHF_TLS) {
		if (section_type == SHT_NOBITS)
			(bind == STB_LOCAL) ? (letter = 's') : (letter = 'S');
		else
			(bind == STB_LOCAL) ? (letter = 'g') : (letter = 'G');
	}
    // Uninitialized data (BSS)
    else if (section_type == SHT_NOBITS)
        letter = (bind == STB_LOCAL) ? 'b' : 'B';
	// text / code section has to be executable
	else if (section_flags & SHF_EXECINSTR)
		(bind == STB_LOCAL) ? (letter = 't') : (letter = 'T');
	// data section has to be writable
	else if ((section_flags & SHF_ALLOC) && (section_flags & SHF_WRITE))
        letter = (bind == STB_LOCAL) ? 'd' : 'D';
    // Read-only data
    else if ((section_flags & SHF_ALLOC) && !(section_flags & SHF_WRITE))
        letter = (bind == STB_LOCAL) ? 'r' : 'R';
	// not needed but i want to be thorough -- only for PE files
	else if (section_name && ft_strncmp(section_name, ".pdata", 6) == 0)
		letter = 'p';
	
	return letter;
}

char get_letter_32(Elf32_Sym sym, Elf32_Shdr *shs_table, char *str_table, char file_endian, Elf32_Ehdr *elf_header) {
	char 		letter = '?';

	uint8_t 	bind = ELF32_ST_BIND(sym.st_info);
	uint8_t		type = ELF32_ST_TYPE(sym.st_info);
	uint16_t	shndx = uint16_to_host(sym.st_shndx, file_endian);

	const		Elf32_Shdr section = shs_table[shndx];
	const char *section_name = str_table + uint32_to_host(section.sh_name, file_endian);
	uint32_t	section_type = uint32_to_host(section.sh_type, file_endian);
	uint64_t	section_flags = uint32_to_host(section.sh_flags, file_endian);

	if (bind == STB_WEAK) {
		if (type == STT_OBJECT)
			(shndx == SHN_UNDEF) ? (letter = 'v') : (letter = 'V');
		else
			(shndx == SHN_UNDEF) ? (letter = 'w') : (letter = 'W');
	}
	else if (type == STT_GNU_IFUNC)
		letter = 'i';
	else if (bind == STB_GNU_UNIQUE)
		letter = 'u';
	else if (shndx == SHN_UNDEF)
		letter = 'U';
	else if (shndx == SHN_ABS)
		letter = 'A';
	else if (shndx == SHN_COMMON)
		letter = 'c';
	// Handle debug sections
	else if (section_name && ( ft_strncmp(section_name, ".debug", 6) == 0 ||
		  					ft_strncmp(section_name, ".stab", 5) == 0 ||
		  					ft_strncmp(section_name, ".stabstr", 8) == 0)) {
		letter = 'N'; 
	}
	// handle small bss and data sections
	else if (section_flags & SHF_TLS) {
		if (section_type == SHT_NOBITS)
			(bind == STB_LOCAL) ? (letter = 's') : (letter = 'S');
		else
			(bind == STB_LOCAL) ? (letter = 'g') : (letter = 'G');
	}
    // Uninitialized data (BSS)
    else if (section_type == SHT_NOBITS)
        letter = (bind == STB_LOCAL) ? 'b' : 'B';
	// text / code section has to be executable
	else if (section_flags & SHF_EXECINSTR)
		(bind == STB_LOCAL) ? (letter = 't') : (letter = 'T');
	// data section has to be writable
	else if ((section_flags & SHF_ALLOC) && (section_flags & SHF_WRITE))
        letter = (bind == STB_LOCAL) ? 'd' : 'D';
    // Read-only data
    else if ((section_flags & SHF_ALLOC) && !(section_flags & SHF_WRITE))
        letter = (bind == STB_LOCAL) ? 'r' : 'R';
	// not needed but i want to be thorough -- only for PE files
	else if (section_name && ft_strncmp(section_name, ".pdata", 6) == 0)
		letter = 'p';
	
	return letter;
}