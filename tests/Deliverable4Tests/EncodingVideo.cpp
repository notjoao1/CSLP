#include "../../src/Encoder.h"

// Display usage information
void displayUsage(const char* programName) {
    std::cerr << "Usage: " << programName << " <input_file> <output_file>" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        displayUsage(argv[0]);
        return 1;
    }

    // Parse input and output file arguments
    const char* inputFile = argv[1];
    const char* outputFile = argv[2];

    // Create Encoder and encode
    Encoder e(inputFile, outputFile, 1, 4, 4);
    e.encode();


    return 0;
}