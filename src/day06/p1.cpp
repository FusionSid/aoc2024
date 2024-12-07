#include <complex>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../utils/utils.h"

using std::cin, std::cout, std::string, std::vector, std::complex;

void solve(const vector<string>& grid) {
    const complex<int> right = {0, 1};

    complex<int> position;
    int w = grid.size();
    int h = grid[0].size();

    for (int row = 0; row < h; row++) {
        for (int col = 0; col < w; col++) {
            if (grid[row][col] == '^') {
                position = {col, row};
            }
        }
    }

    complex<int> direction = {0, -1};
    std::set<std::pair<int, int>> visited;

    while (true) {
        int x = position.real();
        int y = position.imag();

        bool in_area = x >= 0 && y >= 0 && x < w && y < h;
        if (!in_area) {
            break;
        }

        visited.insert({x, y});

        complex<int> next_position = position + direction;
        if (grid[next_position.imag()][next_position.real()] == '#') {
            direction *= right;
            continue;
        }

        position = next_position;
    }

    cout << visited.size() << "\n";
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
