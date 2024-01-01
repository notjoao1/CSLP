#include "../../src/Decoder.h"

// Display usage information
void displayUsage(const char* programName) {
    std::cerr << "Usage: " << programName << " <input_file> <output_file>" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        displayUsage(argv[0]);
        return 1;
    }

    const char* inputFile = argv[1];
    const char* outputFile = argv[2];


    Decoder d(inputFile, outputFile);
    d.decode();

    return 0;
}