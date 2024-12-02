#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../utils/utils.h"

using std::cin, std::cout, std::string, std::vector;

bool isSafe(vector<int>& numbers) {
    int first = numbers[0];
    int second = numbers[1];

    bool increasing = first < second;

    for (int i = 1; i < numbers.size(); i++) {
        int prev = numbers[i - 1];
        int curr = numbers[i];
        int diff = abs(prev - curr);

        bool allIncreasingOrDecreasing =
            (prev < curr && increasing) || (prev > curr && !increasing);

        if (!allIncreasingOrDecreasing || (diff > 3)) {
            return false;
        }
    }

    return true;
}

void solve(const vector<string>& input) {
    int safe = 0;
    for (const string& line : input) {
        int number;
        std::stringstream stream(line);

        std::vector<int> numbers;
        while (stream >> number) numbers.push_back(number);

        if (isSafe(numbers)) {
            safe++;
            continue;
        }

        // this goofy solution may not be the fastest, but it works
        for (int i = 0; i < numbers.size(); ++i) {
            std::vector<int> subarray;

            for (int j = 0; j < numbers.size(); ++j) {
                if (j != i) {
                    subarray.push_back(numbers[j]);
                }
            }

            if (isSafe(subarray)) {
                safe++;
                break;
            }
        }
    }

    cout << safe << "\n";
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
