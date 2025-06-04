#include "ft_nm.h"

static bool check_endianess(char file_endian) {

	static char host_endian = (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) ? ELFDATA2LSB: ELFDATA2MSB;
	
	return (file_endian != host_endian);
}

uint16_t uint16_to_host(uint16_t value, char file_endian) {
	bool swap = check_endianess(file_endian);
	if (swap)
		return (value >> 8) | (value << 8); // endianess only applies past 8 bits
	else
		return value;
}

uint32_t uint32_to_host(uint32_t value, char file_endian) {
	bool swap = check_endianess(file_endian);
	if (swap)
		return ((value & 0x000000FF) << 24) | ((value & 0x0000FF00) << 8) |
		       ((value & 0x00FF0000) >> 8) | ((value & 0xFF000000) >> 24);
	else
		return value;
}

uint64_t uint64_to_host(uint64_t value, char file_endian) {
	bool swap = check_endianess(file_endian);
	if (swap)
		return ((value & 0x00000000000000FF) << 56) | ((value & 0x000000000000FF00) << 40) |
		       ((value & 0x0000000000FF0000) << 24) | ((value & 0x00000000FF000000) << 8) |
		       ((value & 0x000000FF00000000) >> 8) | ((value & 0x0000FF0000000000) >> 24) |
		       ((value & 0x00FF000000000000) >> 40) | ((value & 0xFF00000000000000) >> 56);
	else
		return value;
}

bool is_valid_cstring(const char *str, const char *max_pointer) {
	if (!str || !max_pointer || str >= max_pointer)
		return false;

	while (*str)
		if (str++ >= max_pointer)
			return false;
	return true;
}


void sort_print(sym_t *symbols, size_t sym_index, flags_t *flags) {
	// Check sort flags
	if (!flags->p) {
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
}