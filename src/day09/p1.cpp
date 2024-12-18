#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../utils/utils.h"

using std::cin, std::cout, std::string, std::vector;

void solve(const vector<string>& input) {
    auto ctoi = [](char c) { return c - 48; };

    string diskmap_input = input[0];
    vector<int> diskmap;

    for (int i = 0; i < diskmap_input.length(); i++) {
        int symbol = i & 1 ? -1 : i / 2;
        for (int j = 0; j < ctoi(diskmap_input[i]); j++) {
            diskmap.push_back(symbol);
        }
    }

    int* hptr = &diskmap[0];
    int* tptr = &diskmap[diskmap.size() - 1];

    while (*hptr != -1) hptr++;
    while (*tptr == -1) tptr--;

    while (tptr > hptr) {
        *hptr = *tptr;
        *tptr = -1;

        while (*hptr != -1) hptr++;
        while (*tptr == -1) tptr--;
    }

    long int total = 0;
    for (int i = 0; i < diskmap.size(); i++) {
        if (diskmap[i] == -1) break;
        total += i * diskmap[i];
    }
    cout << total << "\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: Please provide the input file as an argument!\n";
        return 1;
    }

    string inputFileName = argv[1];

    try {
        solve(readInputFile(inputFileName));
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}