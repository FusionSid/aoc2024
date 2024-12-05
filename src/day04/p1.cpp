#include <fstream>
#include <iostream>
#include <set>
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
            vector<std::pair<int, int>> directions = {
                {-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                {1, 0},   {-1, 1}, {0, 1},  {1, 1}};

            for (auto [dx, dy] : directions) {
                int found = true;
                for (int i = 0; i < 4; i++) {
                    char expected_chr = TO_FIND[i];

                    int x = col + dx * i;
                    int y = row + dy * i;

                    bool valid_position = x >= 0 && y >= 0 &&
                                          x < input[row].length() &&
                                          y < input.size();
                    if (!valid_position) {
                        found = false;
                        break;
                    }

                    if (input[y][x] != expected_chr) {
                        found = false;
                        break;
                    }
                }

                if (found) {
                    xmas_count++;
                }
            }
        }
    }

    cout << xmas_count << "\n";
}

//           S  S  S
//            A A A
//             MMM
//           SAMXMAS
//             MMM
//            A A A
//           S  A  S

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