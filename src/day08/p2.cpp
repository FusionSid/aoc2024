#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../utils/utils.h"

using std::cin, std::cout, std::string, std::vector;
typedef std::pair<int, int> coord;

void solve(const vector<string>& grid) {
    std::map<char, vector<coord>> antennas;

    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid.size(); x++) {
            char point = grid[y][x];
            if (point == '.') continue;

            if (antennas.find(point) == antennas.end()) {
                antennas[point] = {};
            }

            antennas[point].push_back({x, y});
        }
    }

    std::set<coord> antinodes;

    // an1 = (a+k(c-a), b+k(d-b))
    // an2 = (c-k(c-a), d-k(d-b))

    for (const auto& [freq, points] : antennas) {
        for (int i = 0; i < points.size(); i++) {
            for (int j = i + 1; j < points.size(); j++) {
                auto [a, b] = points[i];
                auto [c, d] = points[j];

                auto in_grid = [&](coord c) {
                    auto [x, y] = c;
                    return 0 <= x && x < grid.size() && 0 <= y &&
                           y < grid.size();
                };

                for (int k = 1;; k++) {
                    coord an1 = {a + k * (c - a), b + k * (d - b)};
                    coord an2 = {c - k * (c - a), d - k * (d - b)};

                    bool an1_in_grid = in_grid(an1);
                    bool an2_in_grid = in_grid(an2);

                    if (an1_in_grid) antinodes.insert(an1);
                    if (an2_in_grid) antinodes.insert(an2);

                    if (!an1_in_grid && !an2_in_grid) {
                        break;
                    }
                }
            }
        }
    }

    cout << antinodes.size();
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
