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

    printf("%s", argv[1]);

    if (argv[1] == "convert") {
        return Tools::convert(argc, argv);
    }
    else if (argv[1] == "resize") {

    }
    else if (argv[1] == "new") {

    }
    else if (argv[1] == "info") {

    }
}