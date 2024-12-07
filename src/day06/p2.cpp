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

const complex<int> right = {0, 1};

bool is_paradox(vector<string>& grid, complex<int> position) {
    int w = grid.size();
    int h = grid[0].size();

    complex<int> direction = {0, -1};
    std::set<std::array<int, 4>> visited;

    while (true) {
        int x = position.real();
        int y = position.imag();

        bool in_area = x >= 0 && y >= 0 && x < w && y < h;
        if (!in_area) {
            return false;
        }

        std::array<int, 4> pos = {x, y, direction.real(), direction.imag()};
        if (visited.find(pos) != visited.end()) {
            return true;
        }

        visited.insert(pos);

        complex<int> next_position = position + direction;
        if (grid[next_position.imag()][next_position.real()] == '#') {
            direction *= right;
            continue;
        }

        position = next_position;
    }
}

void solve(vector<string> grid) {
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

    int paradoxes = 0;
    for (int row = 0; row < h; row++) {
        for (int col = 0; col < w; col++) {
            if (grid[row][col] != '.') {
                continue;
            }

            grid[row][col] = '#';
            if (is_paradox(grid, position)) {
                paradoxes++;
            }
            grid[row][col] = '.';
        }
    }

    cout << paradoxes << "\n";
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
