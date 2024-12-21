#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../utils/utils.h"

using std::cin, std::cout, std::string, std::vector;

vector<long int> blink(string s) {
    long int number = std::stol(s);

    if (number == 0) {
        return {1};
    } else if (!(s.length() & 1)) {
        string half = s.substr(0, s.length() / 2);
        string other_half = s.substr(s.length() / 2);
        return {std::stoi(half), std::stoi(other_half)};
    }

    return {number * 2024};
}

void solve(const vector<string>& input) {
    vector<string> og_stones;
    const string& line = input[0];
    std::istringstream stream(line);

    string str;
    while (getline(stream, str, ' ')) {
        og_stones.push_back(str);
    }

    vector<string> stones = og_stones;

    for (int i = 0; i < 25; i++) {
        vector<string> new_stones;

        for (const auto& stone : stones) {
            for (auto value : blink(stone)) {
                new_stones.push_back(std::to_string(value));
            }
        }

        stones = new_stones;
    }

    cout << stones.size();
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
