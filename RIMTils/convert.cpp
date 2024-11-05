#include <iostream>
#include "Tools.h"

int Tools::convert(int argc, char** argv) {
	return -1;

	if (argc == 2) {
		printf("Convert mode arguments:\n\n");
		printf("Argument    Meaning");
		printf("-m, --mode  The mode (ToBMP, ToRIM)\n");
		printf("-f, --from  The starting image\n");
		printf("-t, --to    The end image\n");

		return 0;
	}
}