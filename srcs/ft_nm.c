#include "ft_nm.h"

static int ft_nm_process(char *file_content, struct stat file_stat, const char *filename, flags_t *flags)
{
	if (file_content[EI_MAG0] == ELFMAG0 && file_content[EI_MAG1] == ELFMAG1 &&
		file_content[EI_MAG2] == ELFMAG2 && file_content[EI_MAG3] == ELFMAG3)
	{
		if (file_content[EI_CLASS] == ELFCLASS64)
		{
			if ((long unsigned int)file_stat.st_size < sizeof(Elf64_Ehdr))
				return ft_printf("ft_nm: '%s' file format not recognized\n", filename);
			else if ((long unsigned int)file_stat.st_size < sizeof(Elf64_Ehdr) + sizeof(Elf64_Shdr))
				return ft_printf("ft_nm: '%s' symbol table or string table not found\n", filename);
			else
				return ft_nm_64(file_content, file_stat, filename, flags);
		}
		else if (file_content[EI_CLASS] == ELFCLASS32)
		{
			if ((long unsigned int)file_stat.st_size < sizeof(Elf32_Ehdr))
				return ft_printf("ft_nm: '%s' file format not recognized\n", filename);
			else if ((long unsigned int)file_stat.st_size < sizeof(Elf32_Ehdr) + sizeof(Elf32_Shdr))
				return ft_printf("ft_nm: '%s' symbol table or string table not found\n", filename);
			else
				return ft_nm_32(file_content, file_stat, filename, flags);
		}
	}
	return ft_printf("ft_nm: '%s': file format not recognized\n", filename);
}

static int ft_nm(int fd, const char *filename, flags_t *flags)
{
	struct stat file_stat;
	char *file_content;

	// If fstat fails, print an error message and return 1
	if (fstat(fd, &file_stat) < 0)
		return ft_printf("ft_nm: '%s': %s\n", filename, strerror(errno));

	// If file is a directory, print a warning and return 1
	if (S_ISDIR(file_stat.st_mode))
		return ft_printf("ft_nm: Warning: '%s' Is a directory\n", filename);

	// https://nathanotterness.com/2021/10/tiny_elf_modernized.html
	// Check for minimum ELF file size (Elf32_Ehdr smaller than Elf64_Ehdr)
	if ((long unsigned int)file_stat.st_size < sizeof(Elf32_Ehdr))
		return ft_printf("ft_nm: %s file format not recognized\n", filename);

	// mmap the file content into memory + check for failure
	if ((file_content = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return ft_printf("ft_nm: Warning: '%s' Cannot map file\n", filename);
	
	// Call the function to process the file content
	int result = ft_nm_process(file_content, file_stat, filename, flags);

	// unmap the file content and check for failure
	if (munmap(file_content, file_stat.st_size) < 0)
		return ft_printf("ft_nm: Warning: '%s' Cannot unmap file\n", filename);

	return result;
}

int main(int argc, char **argv)
{
	flags_t	flags;
	int		fd;
	char	**files;
	int	len_files = 0;
	bool	err = false;

	// get flags and files from command line arguments
	files = parse_args(argc, argv, &flags);
	for (int i = 0; files[i] != NULL; i++)
		len_files++;
	if (len_files > 1)
		flags.multiple_files = true; // Set the flag if multiple files are provided

	// Continue with the rest of the program logic
	for (int i = 0; files[i] != NULL; i++) {
		fd = open(files[i], O_RDONLY);
		if (fd < 0) {
			ft_printf("ft_nm: '%s': %s\n", files[i], strerror(errno));
			err = true;
			free(files[i]);
			continue;
		}
		if (ft_nm(fd, files[i], &flags) != 0)
			err = true;
		close(fd);
		free(files[i]); // Free the file name after processing
	}

	// Cleanup and return
	free(files);
	if (err == true) return 1;
	return 0;

}