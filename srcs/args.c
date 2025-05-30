#include "ft_nm.h"

static void usage() {
	ft_printf("usage: ./ft_nm [option(s)] [file(s)]\n");
	ft_printf(" List symbols in [file(s)] (a.out by default)\n");
	ft_printf(" The options are:\n");
	ft_printf("  -a\tDisplay debugger-only symbols\n");
	ft_printf("  -g\tDisplay only external symbols\n");
	ft_printf("  -u\tDisplay only undefined symbols\n");
	ft_printf("  -r\tReverse the sense of the sort\n");
	ft_printf("  -p\tDo not sort the symbols\n");
	ft_printf("  -h\tDisplay this information\n");
}

static void get_flags(char *arg, flags_t *flags) {

	// Initialize flags to false
	flags->a = false;
	flags->g = false;
	flags->u = false;
	flags->r = false;
	flags->p = false;
	flags->h = false;

	for (int j = 1; arg[j] != '\0'; j++) {
		if (arg[j] == 'a') {
			flags->a = true;
		} else if (arg[j] == 'g') {
			flags->g = true;
		} else if (arg[j] == 'u') {
			flags->u = true;
		} else if (arg[j] == 'r') {
			flags->r = true;
		} else if (arg[j] == 'p') {
			flags->p = true;
		} else if (arg[j] == 'h') {
			flags->h = true;
			usage();
			exit(0);
		} else {
			ft_printf("./ft_nm: invalid option -- '%c'\n", arg[j]);
			usage();
			exit(1);
		}
	}
}

static char **get_files(int argc, char **argv, int file_count) {
	char **files = NULL;
	int index = 0;

	if (file_count == 0){
		if ((files = malloc(sizeof(char *) * 2)) == NULL)
			exit(1);
		files[1] = NULL; // Null-terminate the array of file names
		if ((files[0] = ft_strdup("a.out")) == NULL) {
			free(files);
			exit(1);
		}
	} else {
		files = malloc(sizeof(char *) * (file_count + 1));
		if (files == NULL)
			exit(1);
		files[file_count] = NULL; // Null-terminate the array of file names
		for (int i = 1; i < argc; i++) {
			// If the argument is not an option (is not '-' followed by a character)
			if (!(argv[i][0] == '-' && argv[i][1] != '\0')) {
				files[index] = ft_strdup(argv[i]);
				if (files[index] == NULL) {
					for (int j = 0; j < index; j++)
						free(files[j]);
					free(files);
					exit(1);
				}
				index++;
			}
		}
	}
	return files;
}

char **parse_args(int argc, char **argv, flags_t *flags) {

	// Initialize flags to false
	flags->a = false;
	flags->g = false;
	flags->u = false;
	flags->r = false;
	flags->p = false;
	flags->h = false;

	int file_count = 0;
	char **files;

	// Parse command line arguments
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-' && argv[i][1] != '\0') {
			// If the argument is an option (starts with '-' and has more characters)
			get_flags(argv[i], flags);
		} else {
			// Count non-option arguments (file names)
			file_count++;
		}
	}
	// If no files are specified, default to "a.out"
	// Otherwise get the file names
	files = get_files(argc, argv, file_count);
	return files;
}
