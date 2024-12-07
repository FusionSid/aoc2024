#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../utils/utils.h"

using std::cin, std::cout, std::string, std::vector;

typedef vector<std::pair<int, int>> r;

bool in_order(r& rules, vector<int> update) {
    for (int i = 0; i < update.size() - 1; i++) {
        int curr = update[i];
        int next = update[i + 1];

        for (auto [first, second] : rules) {
            if (second == curr && first == next) {
                return false;
            }
        }
    }

    return true;
}

bool comparator(int a, int b, const r& rules) {
    for (const auto& [first, second] : rules) {
        if (first == a && second == b) return true;
        if (first == b && second == a) return false;
    }
    return a < b;
}

void solve(const vector<string>& input) {
    int section2_idx = 0;

    r rules;

    for (int i = 0; i < input.size(); i++) {
        const string& line = input[i];

        if (line.empty()) {
            section2_idx = i + 1;
            break;
        }

        int x, y;
        char _;

        std::stringstream stream(line);
        stream >> x >> _ >> y;
        rules.push_back({x, y});
    }

    int total = 0;

    for (int i = section2_idx; i < input.size(); i++) {
        vector<int> update;
        std::stringstream stream(input[i]);

        while (stream.good()) {
            string str;
            getline(stream, str, ',');
            update.push_back(std::stoi(str));
        }

        if (!in_order(rules, update)) {
            std::sort(update.begin(), update.end(),
                      [&](int a, int b) { return comparator(a, b, rules); });
            total += update[update.size() / 2];
        }
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
