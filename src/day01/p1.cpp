#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::cin, std::cout, std::string, std::vector;
int main() {
    vector<int> list1, list2;
    int lines = 0;

    string line;
    while (std::getline(std::cin, line)) {
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

    return 0;
}