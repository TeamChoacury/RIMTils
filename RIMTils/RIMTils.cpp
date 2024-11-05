#include <iostream>
#include "Tools.h"

int main(int argc, char** argv)
{
    if (argc == 1) {
        // No extra arguments

        printf("Choacury RIM format Utilities - RIMTils\nhttps://github.com/TeamChoacury/RIMTils\n\nUsage information:\n");
        printf(" [mode] (arguments)\n\nAvailable modes:\n");
        printf(" MODE     DESCRIPTION\n");
        printf(" convert  Converts between Bitmap and RIM\n");
        printf(" resize   Resizes an image\n");
        printf(" new      Creates a blank RIM file\n");
        printf(" info     Fetches the information about a RIM file\n");

        return 0;
    }

    if (strcmp(argv[1], "convert") == 0) {
        return Tools::convert(argc, argv);
    }
    else if (strcmp(argv[1], "resize") == 0) {
        return 0;
    }
    else if (strcmp(argv[1], "new") == 0) {
        return 0;
    }
    else if (strcmp(argv[1], "info") == 0) {
        return 0;
    }
    else {
        printf("\"%s\" is not a valid mode, run RIMTils without any arguments to see the available modes", argv[1]);
        return -1;
    }
}