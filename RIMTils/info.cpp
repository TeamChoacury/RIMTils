#include <iostream>
#include "Tools.h"
#include "RIM.h"

int Tools::info(int argc, char** argv) {
	if (argc == 2) {
		printf("Usage: \"RIMTils info path/to/file\"");
	} else if(argc == 3) {
		std::ifstream rimFile(argv[2], std::ios::binary);
		if (!rimFile) {
			printf("Error opening file");
			return -1;
		}

		RIMFILEHEADER rimFileHeader;
		RIMINFOHEADER rimInfoHeader;

		rimFile.read(reinterpret_cast<char*>(&rimFileHeader), sizeof(rimFileHeader));
		rimFile.read(reinterpret_cast<char*>(&rimInfoHeader), sizeof(rimInfoHeader));

		// 5249 is RI in HEX
		if (rimFileHeader.bfType != 0x5249) {
			printf("The provided file is not a RIM");
			return -1;
		}

		int rimRowSize = ((rimInfoHeader.biBitCount * rimInfoHeader.biWidth + 31) / 32) * 4;
		std::vector<uint8_t> rimData(rimRowSize * abs(rimInfoHeader.biHeight));

		rimFile.seekg(rimFileHeader.bfOffBits, std::ios::beg);
		rimFile.read(reinterpret_cast<char*>(rimData.data()), rimData.size());
		rimFile.close();

		printf("Information for the file \"%s\"\n", argv[2]);
		printf("Width:  %d\nHeight: %d\n", rimInfoHeader.biWidth, rimInfoHeader.biHeight);
		printf("Type:   %d\n", rimFileHeader.bfType);
		printf("Size:   %d\n", rimData.size());
	}
	else {
		printf("Too many arguments");
	}

	return 0;
}