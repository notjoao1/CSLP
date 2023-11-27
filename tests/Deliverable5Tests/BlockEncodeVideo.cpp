#include "../../src/BlockEncoding.h"
#include <iostream>
#include <string>
#include <algorithm> // for std::find

// Function to find the value associated with a command line option
std::string getCmdOption(char **begin, char **end, const std::string &option) {
    char **it = std::find(begin, end, option);
    if (it != end && ++it != end) {
        return *it;
    }
    return "";
}

// Function to check if a command line option exists
bool cmdOptionExists(char **begin, char **end, const std::string &option) {
    return std::find(begin, end, option) != end;
}

// Display usage information
void displayUsage() {
    std::cerr << "Usage: program_name --input-file <input_file> --output-file <output_file> [--block-size <block_size>] [--keyframe-period <keyframe_period>] [--search-area <search_area>]" << std::endl;
    std::cerr << "Optional arguments:" << std::endl;
    std::cerr << "  --block-size <block_size>      : Size of the block (default: 8)" << std::endl;
    std::cerr << "  --keyframe-period <keyframe_period> : Period of keyframes (default: 64)" << std::endl;
    std::cerr << "  --search-area <search_area>    : Size of the search area (default: 16)" << std::endl;
}

int main(int argc, char* argv[]) {
    // Check for mandatory arguments
    if (argc < 3 || !cmdOptionExists(argv, argv + argc, "--input-file") || !cmdOptionExists(argv, argv + argc, "--output-file")) {
        std::cerr << "Error: Please provide input file and output file." << std::endl;
        displayUsage();
        return 1;
    }

    std::string input_file = getCmdOption(argv, argv + argc, "--input-file");
    std::string output_file = getCmdOption(argv, argv + argc, "--output-file");
    // default values
    int block_size = 16;
    int search_area = 16;
    int keyframe_period = 64;

    // Check for command line options and update variables accordingly
    if (cmdOptionExists(argv, argv + argc, "--block-size")) {
        block_size = std::stoi(getCmdOption(argv, argv + argc, "--block-size"));
    }
    if (cmdOptionExists(argv, argv + argc, "--keyframe-period")) {
        keyframe_period = std::stoi(getCmdOption(argv, argv + argc, "--keyframe-period"));
    }
    if (cmdOptionExists(argv, argv + argc, "--search-area")) {
        search_area = std::stoi(getCmdOption(argv, argv + argc, "--search-area"));
    }

    // Create BlockEncoding object with provided or default values
    BlockEncoding be(input_file, output_file, block_size, search_area, keyframe_period);
    be.encode();

    return 0;
}