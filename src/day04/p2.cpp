#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../utils/utils.h"

using std::cin, std::cout, std::string, std::vector;

void solve(const vector<string>& input) {
    const string TO_FIND = "XMAS";

    int xmas_count = 0;

    for (int row = 0; row < input.size(); row++) {
        for (int col = 0; col < input.size(); col++) {
            bool valid_position =
                col >= 1 && row >= 1 && col <= input[row].length() - 2 &&
                row <= input.size() - 2 && input[row][col] == 'A';

            if (!valid_position) {
                continue;
            }

            string diag1 = "", diag2 = "";

            diag1 += input[row - 1][col - 1];
            diag1 += input[row + 1][col + 1];

            diag2 += input[row - 1][col + 1];
            diag2 += input[row + 1][col - 1];

            std::sort(diag1.begin(), diag1.end());
            std::sort(diag2.begin(), diag2.end());

            if (diag1 == "MS" && diag2 == "MS") {
                xmas_count++;
            }
        }
    }

    cout << xmas_count << "\n";
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