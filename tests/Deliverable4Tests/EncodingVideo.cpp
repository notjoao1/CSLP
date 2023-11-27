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

    // Initialize VideoManipulator with the input file argument
    VideoManipulator* v = new VideoManipulator(inputFile);

    // Initialize BitStreamWrite with the output file argument
    BitStreamWrite* stream = new BitStreamWrite(outputFile);

    // Create Encoder and encode
    Encoder e(v, stream);
    e.encode();

    // Free allocated memory
    delete v;
    delete stream;

    return 0;
}