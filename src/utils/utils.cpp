#include "utils.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

std::vector<std::string> readInputFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Error: Unable to open input file: " +
                                 filename);
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }

    inputFile.close();
    return lines;
}