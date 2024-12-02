#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../utils/utils.h"

using std::cin, std::cout, std::string, std::vector;

void solve(const vector<string>& input) {
    vector<int> list1, list2;
    int lines = 0;

    for (const string& line : input) {
        int n1, n2;
        std::istringstream stream(line);

        stream >> n1 >> n2;
        list1.push_back(n1);
        list2.push_back(n2);
        lines++;
    }

    std::sort(list1.begin(), list1.end(), [](int a, int b) { return a < b; });
    std::sort(list2.begin(), list2.end(), [](int a, int b) { return a < b; });

    int dist = 0;
    for (int i = 0; i < lines; i++) {
        int n1, n2;
        n1 = list1[i];
        n2 = list2[i];

        dist += abs(n1 - n2);
    }

    cout << dist << "\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: Please provide the input file as an argument!"
                  << std::endl;
        return 1;
    }

    string inputFileName = argv[1];

    try {
        vector<string> input = readInputFile(inputFileName);
        solve(input);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
