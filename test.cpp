#include <algorithm>
#include <cassert>
#include <cstddef>
#include <ctime>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
#include "mountain_sort.h"

int main()
{
    std::mt19937_64 engine(std::time(nullptr));

    for (std::size_t i = 0 ; i < 1'000 ; ++i)
    {
        // Create a shuffled vector
        std::vector<int> vec(5'000);
        std::iota(std::begin(vec), std::end(vec), 0);
        std::shuffle(std::begin(vec), std::end(vec), engine);

        // Mountain sort the vector
        mountain_sort(std::begin(vec), std::end(vec), std::greater<>{});
        assert(std::is_sorted(std::begin(vec), std::end(vec), std::greater<>{}));
    }
}
