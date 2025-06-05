/*
 * mountain_sort.hpp - The best algorithm to sort mountains
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2015-2025 Morwenn <morwenn29@hotmail.fr>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <random>
#include <vector>
#include "mountain_sort.hpp"

int main()
{
    std::minstd_rand engine(std::random_device{}());

    for (std::size_t i = 0 ; i < 1'000 ; ++i)
    {
        // Create a shuffled vector
        std::vector<int> vec(5'000);
        std::iota(vec.begin(), vec.end(), 0);
        std::shuffle(vec.begin(), vec.end(), engine);

        // Mountain sort the vector
        mountain_sort(vec.begin(), vec.end(), std::greater<>{});
        assert(std::is_sorted(vec.begin(), vec.end(), std::greater<>{}));
    }
}
