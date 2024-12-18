#ifndef UTILS_H
#define UTILS_H

#include <iterator>
#include <string>
#include <vector>
#include <iostream>

std::vector<std::string> readInputFile(const std::string& filename);

template <typename Container>
void print_arr(const Container& array, std::string sep = " ") {
    auto it = array.begin();
    while (it != array.end()) {
        std::cout << *it;
        ++it;
        if (it != array.end()) {
            std::cout << sep;
        }
    }
    std::cout << std::endl;
}

#endif
