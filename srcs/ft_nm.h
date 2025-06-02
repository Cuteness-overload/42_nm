// http://www.skyfree.org/linux/references/ELF_Format.pdf
// https://uclibc.org/docs/elf-64-gen.pdf

#ifndef FT_NM_H
	#define FT_NM_H

	#include "../libft/libft.h"
	#include "../libft/printf/ft_printf.h"

	#include <elf.h>		// ELF header and related structures and defines
	#include <stdbool.h>	// bool type, true, false
	#include <fcntl.h>		// open
	#include <sys/stat.h>	// fstat
	#include <sys/mman.h>	// mmap, munmap
	#include <unistd.h>		// close, write, exit, getpagesize
	#include <stdio.h>		// perror
	#include <stdlib.h>		// malloc, free, exit
	#include <errno.h>

	// p > r in terms of sorting
	typedef struct flags_s {
		bool a;		// Display all symbols
		bool g;		// Display only external symbols
		bool u;		// Display only undefined symbols
		bool r;		// Reverse the sort order
		bool p;		// Do not sort the symbols
		bool h;		// Display help message
	} flags_t;

	typedef struct sym_s {
		char *name; 	// Name of the symbol
		uint64_t value;	// Address of the symbol
		char letter;	// Letter representing the symbol type: U, T, D, B, R, A, etc.

		bool is_external; // True if the symbol is external (global)
		bool is_undefined; // True if the symbol is undefined
	} sym_t;

	// args.c
	char 		**parse_args(int argc, char **argv, flags_t *flags);

	// nm_32.c
	int 		ft_nm_32(char *file_content, struct stat file_stat, char *filename, flags_t *flags);
	
	// nm_64.c
	int 		ft_nm_64(char *file_content, struct stat file_stat, char *filename, flags_t *flags);

	//  sort.c
	void 		merge_sort(sym_t *array, int left, int right);
	void 		reverse_merge_sort(sym_t *array, int left, int right);

	// symbols.c
	char 		get_letter_32(Elf32_Sym sym, Elf32_Shdr *shs_table, char *str_table, char file_endian, Elf32_Ehdr *elf_header);
	char 		get_letter_64(Elf64_Sym sym, Elf64_Shdr *shs_table, char *str_table, char file_endian, Elf64_Ehdr *elf_header);

	// utils.c
	bool 		is_valid_cstring(const char *str, const char *max_pointer);
	uint16_t	uint16_to_host(uint16_t value, char file_endian);
	uint32_t	uint32_to_host(uint32_t value, char file_endian);
	uint64_t	uint64_to_host(uint64_t value, char file_endian);

#endif