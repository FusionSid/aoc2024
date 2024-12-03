#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../utils/utils.h"

using std::cin, std::cout, std::string, std::vector, std::regex;

void solve(const vector<string>& input) {
    string pattern = R"(mul\((\d+),(\d+)\))";
    regex re = regex(pattern);

    int sum = 0;

    for (const string& line : input) {
        for (std::sregex_iterator i =
                 std::sregex_iterator(line.begin(), line.end(), re);
             i != std::sregex_iterator(); ++i) {
            std::smatch m = *i;
            int total = std::stoi(m.str(1)) * std::stoi(m.str(2));

            cout << m.str(0) << " " << total << "\n";

            sum += total;
        }
    }

    cout << sum << "\n";
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
