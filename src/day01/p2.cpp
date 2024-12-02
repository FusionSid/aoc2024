#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../utils/utils.h"

using std::cin, std::cout, std::string, std::vector, std::map;

void solve(const vector<string>& input) {
    vector<int> list1;
    map<int, int> list2;

    string line;
    for (const string& line : input) {
        int n1, n2;
        std::istringstream stream(line);

        stream >> n1 >> n2;
        list1.push_back(n1);

        if (list2.find(n2) == list2.end()) {
            list2[n2] = 0;
        }
        list2[n2]++;
        cout << list2[n2] << "\n";
    }

    int sim = 0;
    for (auto n1 : list1) {
        int n2 = list2[n1];

        if (list2.find(n1) == list2.end()) {
            n2 = 0;
        }
        sim += n1 * n2;
    }
    cout << sim << "\n";
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
