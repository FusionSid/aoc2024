#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../utils/utils.h"

using std::cin, std::cout, std::string, std::vector;

void solve(const vector<string>& input) {
    long long sum = 0;
    for (const string& line : input) {
        long long lhs;
        std::istringstream stream(line);

        stream >> lhs;

        vector<long long> rhs;

        stream.ignore(1, ':');
        stream.ignore(1, ' ');

        long long operand;
        while (stream >> operand) {
            rhs.push_back(operand);
            if (stream.peek() == ' ') {
                stream.ignore(1, ' ');
            }
        }

        string operators = "+*|";
        long long length = rhs.size() - 1;

        long long totalCombinations = 1;
        for (int i = 0; i < length; i++) {
            totalCombinations *= 3;
        }

        for (int i = 0; i < totalCombinations; i++) {
            std::string combination = "";
            int temp = i;

            for (int j = 0; j < length; j++) {
                combination += operators[temp % 3];
                temp /= 3;
            }

            long long total = rhs[0];
            for (int i = 1; i < rhs.size(); i++) {
                char op = combination[i - 1];
                if (op == '*') {
                    total *= rhs[i];
                } else if (op == '+') {
                    total += rhs[i];

                } else {
                    total = std::stoll(std::to_string(total) +
                                       std::to_string(rhs[i]));
                }
            }

            if (total == lhs) {
                sum += lhs;
                break;
            }
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
