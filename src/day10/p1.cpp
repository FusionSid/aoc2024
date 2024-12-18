#include <complex>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../utils/utils.h"

using std::cin, std::cout, std::string, std::vector, std::complex;

std::vector<complex<int>> find_adj(vector<vector<int>>& grid,
                                   complex<int> pos) {
    std::vector<complex<int>> adjacent_spots;
    std::vector<complex<int>> directions = {1, -1, {0, 1}, {0, -1}};

    for (auto direction : directions) {
        complex<int> spot = direction + pos;
        int x = spot.real();
        int y = spot.imag();

        if (x >= 0 && x < grid[y].size() && y < grid.size() && y >= 0) {
            adjacent_spots.push_back(spot);
        }
    }

    return adjacent_spots;
}

int find_trails(vector<vector<int>>& grid, complex<int> start) {
    std::set<std::pair<int, int>> trails_found;
    std::queue<std::pair<complex<int>, complex<int>>> q;
    std::set<std::pair<int, int>> visited;

    q.push({start, 1});

    while (!q.empty()) {
        const auto [node, next] = q.front();
        q.pop();

        if (grid[node.imag()][node.real()] == 9) {
            trails_found.insert({node.real(), node.imag()});
        }

        visited.insert({node.real(), node.imag()});
        for (auto i : find_adj(grid, node)) {
            if (visited.find({i.real(), i.imag()}) != visited.end()) {
                continue;
            }
            if (grid[i.imag()][i.real()] == next) {
                q.push({i, next + 1});
            }
        }
    }

    return trails_found.size();
}
void solve(const vector<string>& input) {
    auto ctoi = [](char c) { return c - 48; };

    vector<vector<int>> grid;
    vector<complex<int>> trailheads;

    for (int i = 0; i < input.size(); i++) {
        vector<int> row;
        for (int j = 0; j < input[i].length(); j++) {
            char c = input[i][j];
            if (c == '0') {
                trailheads.push_back({j, i});
            }

            row.push_back(ctoi(c));
        }
        grid.push_back(row);
    }

    int total = 0;
    for (auto trailhead : trailheads) {
        total += find_trails(grid, trailhead);
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
