#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../utils/utils.h"

using std::cin, std::cout, std::string, std::vector, std::regex,
    std::sregex_iterator, std::smatch, std::stoi;

void solve(const vector<string>& input) {
    regex tokens = regex(R"(do\(\)|don\'t\(\)|mul\((\d{1,3}),(\d{1,3})\))");

    int sum = 0;
    bool instructions_enabled = true;

    for (const string& line : input) {
        for (auto i = sregex_iterator(line.begin(), line.end(), tokens);
             i != sregex_iterator(); ++i) {
            smatch m = *i;
            string token = m.str();

            if (token[0] == 'm' && instructions_enabled) {
                sum += stoi(m.str(1)) * stoi(m.str(2));
                continue;
            }

            instructions_enabled = token == "do()";
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
