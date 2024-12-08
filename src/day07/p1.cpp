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

        long long length = rhs.size() - 1;
        long long bin = 1 << length;  // 2^length

        vector<string> sequences;
        for (int i = 0; i < bin; i++) {
            std::string sequence = "";

            for (int j = 0; j < length; j++) {
                bool bit_is_set = (i >> (length - j - 1)) & 1;
                sequence += bit_is_set ? "+" : "*";
            }

            long long total = rhs[0];
            for (int i = 1; i < rhs.size(); i++) {
                char op = sequence[i - 1];
                if (op == '*') {
                    total *= rhs[i];
                } else {
                    total += rhs[i];
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
