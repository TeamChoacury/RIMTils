#include <iostream>
#include "Tools.h"

enum Mode {
	ToBMP = 0,
	ToRIM = 1
};

int Tools::convert(int argc, char** argv) {
	if (argc == 2) {
		printf("Convert mode arguments:\n\n");
		printf("Argument    Meaning\n");
		printf("-m, --mode  The mode (ToBMP, ToRIM)\n");
		printf("-f, --from  The starting image\n");
		printf("-t, --to    The end image\n");
		printf("\nAll of these arguments are required\n");

		return 0;
	}

	if (argc == 8) {
		// This includes:
		// - RIMTils.exe
		// - convert
		// - Every argument

		Mode mode;
		char* from;
		char* to;

		for (size_t i = 2; i < argc; i++)
		{
			if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--mode")) {
				if (i + 1 >= argc) {
					printf("Unexpected amount of arguments provided");
					return -1;
				}

				if (strcmp(argv[i + 1], "ToBMP") == 0) {
					mode = Mode::ToBMP;
				}
				else if (strcmp(argv[i + 1], "ToRIM") == 0) {
					mode = Mode::ToRIM;
				}
				else {
					printf("Invalid mode provided");
					return -1;
				}

				i++;
			}
			else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--from") == 0) {
				if (i + 1 >= argc) {
					printf("Unexpected amount of arguments provided");
					return -1;
				}

				from = argv[i + 1];
				i++;
			}
			else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--to") == 0) {
				if (i + 1 >= argc) {
					printf("Unexpected amount of arguments provided");
					return -1;
				}

				to = argv[i + 1];
				i++;
			}
		}
	}
	else {
		if (argc > 8) {
			printf("Too many arguments provided");
		}
		else if (argc < 8) {
			printf("Too few arguments provided");
		}

		return -1;
	}
}