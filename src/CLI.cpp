#include "BlockEncoding.h"
#include "BlockDecoding.h"
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
    std::cerr << "Usage: program_name --input-file <input_file> --output-file <output_file> [--block-size <block_size>] [--keyframe-period <keyframe_period>] [--search-area <search_area>] [--quantizationY <amount>] [--quantizationU <amount>] [--quantizationV <amount>]" << std::endl;
    std::cerr << "Required arguments:" << std::endl;
    std::cerr << "  --input-file <input_file>   : File path to input file." << std::endl;
    std::cerr << "  -i <input_file>             : File path to input file." << std::endl;
    std::cerr << "  --output-file <output_file> : File path to output file." << std::endl;
    std::cerr << "  -o <output_file>            : File path to output file." << std::endl;
    std::cerr << "Only one of the 4 arguments: (if none are provided defaults to '-e')" << std::endl;
    std::cerr << "  --encode : Encoding mode. Encondes input to output." << std::endl;
    std::cerr << "  -e       : Encoding mode. Encondes input to output." << std::endl;
    std::cerr << "  --decode : Decoding mode. Decodes input to output." << std::endl;
    std::cerr << "  -d       : Decoding mode. Decodes input to output." << std::endl;
    std::cerr << "Optional arguments (only required for encode mode):" << std::endl;
    std::cerr << "  --block-size <block_size>           : Size of the block (default: 8)" << std::endl;
    std::cerr << "  -b <block_size>                     : Size of the block (default: 8)" << std::endl;
    std::cerr << "  --keyframe-period <keyframe_period> : Period of keyframes (default: 64)" << std::endl;
    std::cerr << "  -k <keyframe_period>                : Period of keyframes (default: 64)" << std::endl;
    std::cerr << "  --search-area <search_area>         : Size of the search area (default: 64)" << std::endl;
    std::cerr << "  -s <search_area>                    : Size of the search area (default: 64)" << std::endl;
    std::cerr << "  --quantizationY <amount>            : Level of quantization on Y channel. Each level is corresponds to a bitshift." << std::endl;
    std::cerr << "  -qy <amount>                        : Level of quantization on Y channel. Each level is corresponds to a bitshift." << std::endl;
    std::cerr << "  --quantizationU <amount>            : Level of quantization on U channel. Each level is corresponds to a bitshift." << std::endl;
    std::cerr << "  -qu <amount>                        : Level of quantization on U channel. Each level is corresponds to a bitshift." << std::endl;
    std::cerr << "  --quantizationV <amount>            : Level of quantization on V channel. Each level is corresponds to a bitshift." << std::endl;
    std::cerr << "  -qv <amount>                        : Level of quantization on V channel. Each level is corresponds to a bitshift." << std::endl;
}

int main(int argc, char* argv[]) {
    // Check for mandatory arguments
    std::string input_file;
    std::string output_file;
    bool encode_mode = true;

    if (cmdOptionExists(argv, argv + argc, "--input-file")) {
        input_file = getCmdOption(argv, argv + argc, "--input-file");
    }
    if (cmdOptionExists(argv, argv + argc, "-i")) {
        if (cmdOptionExists(argv, argv + argc, "--input-file")){
            std::cerr << "Warn: Two input files provided defaulting to '-i'." << std::endl;
        }
        input_file = getCmdOption(argv, argv + argc, "-i");
    }
    if (input_file.empty()){
        std::cerr << "Error: Please provide input file.\n" << std::endl;
        displayUsage();
        return 1;
    }

    if (cmdOptionExists(argv, argv + argc, "--output-file")) {
        output_file = getCmdOption(argv, argv + argc, "--output-file");
    }
    if (cmdOptionExists(argv, argv + argc, "-o")) {
        if (cmdOptionExists(argv, argv + argc, "--output-file")){
            std::cerr << "Warn: Two input files provided defaulting to '-o'." << std::endl;
        }
        output_file = getCmdOption(argv, argv + argc, "-o");
    }

    if (output_file.empty()){
        std::cerr << "Error: Please provide output file.\n" << std::endl;
        displayUsage();
        return 1;
    }

    if (cmdOptionExists(argv, argv + argc, "--decode")) {
        encode_mode = false;
    }
    if (cmdOptionExists(argv, argv + argc, "-d")) {
        encode_mode = false;
    }

    if (!encode_mode && ( cmdOptionExists(argv, argv + argc, "--encode") || cmdOptionExists(argv, argv + argc, "-e") )){
        std::cerr << "Error: Please use only one mode.\n" << std::endl;
        displayUsage();
        return 1;
    }

    if(encode_mode){
        // default values
        int block_size = 16;
        int search_area = 64;
        int keyframe_period = 64;
        int quantY = 0;
        int quantU = 0;
        int quantV = 0;

        // Check for command line options and update variables accordingly
        if (cmdOptionExists(argv, argv + argc, "--block-size")) {
            block_size = std::stoi(getCmdOption(argv, argv + argc, "--block-size"));
        }
        if (cmdOptionExists(argv, argv + argc, "-b")) {
            if (cmdOptionExists(argv, argv + argc, "--block-size")){
                std::cerr << "Warn: Two block sizes provided defaulting to '-b'." << std::endl;
            }
            block_size = std::stoi(getCmdOption(argv, argv + argc, "-b"));
        }

        if (cmdOptionExists(argv, argv + argc, "--keyframe-period")) {
            keyframe_period = std::stoi(getCmdOption(argv, argv + argc, "--keyframe-period"));
        }
        if (cmdOptionExists(argv, argv + argc, "-k")) {
            if (cmdOptionExists(argv, argv + argc, "--keyframe-period")){
                std::cerr << "Warn: Two keyframes periods provided defaulting to '-k'." << std::endl;
            }
            keyframe_period = std::stoi(getCmdOption(argv, argv + argc, "-k"));
        }

        if (cmdOptionExists(argv, argv + argc, "--search-area")) {
            search_area = std::stoi(getCmdOption(argv, argv + argc, "--search-area"));
        }
        if (cmdOptionExists(argv, argv + argc, "-s")) {
            if (cmdOptionExists(argv, argv + argc, "--search-area")){
                std::cerr << "Warn: Two search areas provided defaulting to '-s'." << std::endl;
            }
            search_area = std::stoi(getCmdOption(argv, argv + argc, "-s"));
        }

        if (cmdOptionExists(argv, argv + argc, "--quantizationY")) {
            quantY = std::stoi(getCmdOption(argv, argv + argc, "--quantizationY"));
        }
        if (cmdOptionExists(argv, argv + argc, "-qy")) {
            if (cmdOptionExists(argv, argv + argc, "--quantizationY")){
                std::cerr << "Warn: Two quantizations levels for Y channel provided defaulting to '-qy'." << std::endl;
            }
            quantY = std::stoi(getCmdOption(argv, argv + argc, "-qy"));
        }

        if (cmdOptionExists(argv, argv + argc, "--quantizationU")) {
            quantY = std::stoi(getCmdOption(argv, argv + argc, "--quantizationU"));
        }
        if (cmdOptionExists(argv, argv + argc, "-qu")) {
            if (cmdOptionExists(argv, argv + argc, "--quantizationU")){
                std::cerr << "Warn: Two quantizations levels for U channel provided defaulting to '-qu'." << std::endl;
            }
            quantU = std::stoi(getCmdOption(argv, argv + argc, "-qu"));
        }

        if (cmdOptionExists(argv, argv + argc, "--quantizationV")) {
            quantV = std::stoi(getCmdOption(argv, argv + argc, "--quantizationV"));
        }
        if (cmdOptionExists(argv, argv + argc, "-qv")) {
            if (cmdOptionExists(argv, argv + argc, "--quantizationV")){
                std::cerr << "Warn: Two quantizations levels for V channel provided defaulting to '-qv'." << std::endl;
            }
            quantV = std::stoi(getCmdOption(argv, argv + argc, "-qv"));
        }

        // Create BlockEncoding object with provided or default values
        BlockEncoding en(input_file, output_file, block_size, search_area, keyframe_period, quantY, quantU, quantV);
        en.encode();
    } else {
        BlockDecoding de(input_file, output_file);
        de.decode();
    }

    return 0;
}
