#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using std::cin, std::cout, std::string, std::vector, std::map;
int main() {
    vector<int> list1;
    map<int, int> list2;

    string line;
    while (std::getline(std::cin, line)) {
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

    return 0;
}