#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "../utils/utils.h"

typedef long long ll;
using namespace std;

struct pair_hash {
    template <typename T1, typename T2>
    size_t operator()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

ll blink(ll stone, int times, unordered_map<pair<ll, int>, ll, pair_hash>& cache) {
    if (cache.find({stone, times}) != cache.end()) {
        return cache[{stone, times}];
    }

    if (times == 0) {
        return 1;
    }

    int times_left = times - 1;

    if (stone == 0) {
        return blink(1, times_left, cache);
    }

    string s = to_string(stone);
    if (!(s.length() & 1)) {
        ll half = stoll(s.substr(0, s.length() / 2));
        ll other_half = stoll(s.substr(s.length() / 2));

        ll result = blink(half, times_left, cache) +
                    blink(other_half, times_left, cache);
        cache[{stone, times}] = result;
        return result;
    }

    ll result = blink(stone * 2024, times_left, cache);
    cache[{stone, times}] = result;
    return result;
}

void solve(const vector<string>& input) {
    const string& line = input[0];
    istringstream stream(line);

    vector<ll> stones;

    string str;
    while (getline(stream, str, ' ')) {
        stones.push_back(stoll(str));
    }

    ll total = 0;
    unordered_map<pair<ll, int>, ll, pair_hash> cache;

    for (auto stone : stones) {
        total += blink(stone, 75, cache);
    }

    cout << total << "\n";
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
