#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>

int main()
{
    std::vector<int> myvector(9);
    std::iota(myvector.begin(), myvector.end(), 1); // 1 2 3 4 5 6 7 8 9
    std::random_shuffle(myvector.begin(), myvector.end());
}