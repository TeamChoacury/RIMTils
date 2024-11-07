#include <iostream>
#include <cstring>
#include <fstream>
#include "Tools.h"
#include "Bitmap.h"
#include "RIM.h"

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
		char* from = (char*)"";
		char* to = (char*)"";

		for (size_t i = 2; i < argc; i++)
		{
			if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--mode") == 0) {
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

		if (mode == Mode::ToRIM) {
			std::ifstream bmFile(from, std::ios::binary);
			if (!bmFile) {
				printf("Error opening file");
				return -1;
			}
			std::ofstream rimFile(to, std::ios::binary);
			// It doesn't matter if this file doesn't exist, we override it anyway

			BITMAPFILEHEADER bmFileHeader;
			BITMAPINFOHEADER bmInfoHeader;

			bmFile.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));
			bmFile.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));

			// 4D42 is BM in HEX
			if (bmFileHeader.bfType != 0x4D42) {
				printf("The provided file is not a bitmap");
				return -1;
			}

			int bmRowSize = ((bmInfoHeader.biBitCount * bmInfoHeader.biWidth + 31) / 32) * 4;
			std::vector<uint8_t> bmData(bmRowSize * abs(bmInfoHeader.biHeight));

			bmFile.seekg(bmFileHeader.bfOffBits, std::ios::beg);
			bmFile.read(reinterpret_cast<char*>(bmData.data()), bmData.size());
			bmFile.close();

			std::vector<uint8_t> rimData(bmInfoHeader.biWidth * bmInfoHeader.biHeight * 4);
			for (size_t y = 0; y < bmInfoHeader.biHeight; y++)
			{
				for (size_t x = 0; x < bmInfoHeader.biWidth; x++)
				{
					int bmIndex = y * bmRowSize + x * 3;
					int rimIndex = (y * bmInfoHeader.biWidth + x) * 4;

					uint8_t b = bmData[bmIndex + 0];
					uint8_t g = bmData[bmIndex + 1];
					uint8_t r = bmData[bmIndex + 2];

					rimData[rimIndex + 0] = r;	  // Red
					rimData[rimIndex + 0] = g;    // Green
					rimData[rimIndex + 0] = b;    // Blue
					rimData[rimIndex + 0] = 0xFF; // Alpha
				}
			}

			RIMFILEHEADER rimFileHeader = {
				0x4D4952,
				static_cast<uint32_t>(sizeof(RIMFILEHEADER) + sizeof(RIMINFOHEADER) + rimData.size()),
				0, 0, sizeof(RIMFILEHEADER) + sizeof(RIMINFOHEADER)
			};
			RIMINFOHEADER rimInfoHeader = {
				sizeof(RIMINFOHEADER), bmInfoHeader.biWidth, bmInfoHeader.biHeight,
				1, 32, 0, static_cast<uint32_t>(rimData.size()),
				bmInfoHeader.biXPelsPerMeter, bmInfoHeader.biYPelsPerMeter,
				0, 0
			};

			rimFile.write(reinterpret_cast<const char*>(&rimFileHeader), sizeof(rimFileHeader));
			rimFile.write(reinterpret_cast<const char*>(&rimInfoHeader), sizeof(rimInfoHeader));
			rimFile.write(reinterpret_cast<const char*>(rimData.data()), rimData.size());

			bmFile.close();
			rimFile.close();
		}
		else if (mode == Mode::ToBMP) {
			std::ifstream rimFile(from, std::ios::binary);
			if (!rimFile) {
				printf("Error opening file");
				return -1;
			}
			std::ifstream bmFile(to, std::ios::binary);

			RIMFILEHEADER rimFileHeader;
			RIMINFOHEADER rimInfoHeader;

			rimFile.read(reinterpret_cast<char*>(&rimFileHeader), sizeof(rimFileHeader));
			rimFile.read(reinterpret_cast<char*>(&rimInfoHeader), sizeof(rimInfoHeader));
			
			// 4D4952 is RIM in HEX
			if (rimFileHeader.bfType != 0x4D4952) {
				printf("The provided file is not a RIM");
				return -1;
			}

			rimFile.close();
			bmFile.close();
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