#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../utils/utils.h"

using std::cin, std::cout, std::string, std::vector;

typedef std::pair<int, int> p;

int find_free_space(vector<p>& diskmap, int desired_size, int start_idx) {
    for (int i = 0; i < diskmap.size(); ++i) {
        const auto& [file, size] = diskmap[i];
        if (file != -1) {
            continue;
        }

        if (i < start_idx && size >= desired_size) {
            return i;
        }
    }

    return -1;
}

long int calc_checksum(const std::vector<std::pair<int, int>>& diskmap) {
    long int checksum = 0;

    int weight = 0;
    for (const auto& [file, length] : diskmap) {
        for (int i = 0; i < length; ++i) {
            if (file != -1) {
                checksum += file * weight;
            }
            ++weight;
        }
    }

    return checksum;
}
void solve(const vector<string>& input) {
    auto ctoi = [](char c) { return c - 48; };

    string diskmap_input = input[0];

    vector<std::pair<int, int>> diskmap;
    int start_file = 0;

    for (int i = 0; i < diskmap_input.length(); i++) {
        int symbol = i & 1 ? -1 : i / 2;
        int size = ctoi(diskmap_input[i]);

        diskmap.push_back({symbol, size});
        start_file = std::max(symbol, start_file);
    }

    for (int i = start_file; i > 0; --i) {
        int curr_idx = diskmap.size() - 1;
        while (diskmap[curr_idx].first != i) {
            curr_idx--;
        }

        const auto [file, size] = diskmap[curr_idx];

        int free_spot_idx = find_free_space(diskmap, size, curr_idx);
        if (free_spot_idx == -1) {
            continue;
        }

        diskmap[free_spot_idx].second -= size;
        diskmap[curr_idx].first = -1;
        diskmap.insert(diskmap.begin() + free_spot_idx, {file, size});
    }

    cout << calc_checksum(diskmap) << "\n";
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