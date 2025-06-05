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
#ifndef MOUNTAIN_SORT_H_
#define MOUNTAIN_SORT_H_

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

namespace mountain_sort_detail
{
    ////////////////////////////////////////////////////////////
    // Indirect comparator

    template<typename Compare>
    class indirect_compare
    {
        public:

            explicit indirect_compare(Compare compare):
                compare(std::move(compare))
            {}

            template<typename Iterator>
            auto operator()(Iterator lhs, Iterator rhs)
                -> bool
            {
                return compare(*lhs, *rhs);
            }

            template<typename Iterator>
            auto operator()(Iterator lhs, Iterator rhs) const
                -> bool
            {
                return compare(*lhs, *rhs);
            }

        private:

            Compare compare;
    };
}

template<
    typename RandomAccessIterator,
    typename Compare = std::less<>
>
auto mountain_sort(RandomAccessIterator first, RandomAccessIterator last,
                   Compare compare={})
    -> void
{
    ////////////////////////////////////////////////////////////
    // Indirectly sort the iterators

    // Copy the iterators in a vector
    std::vector<RandomAccessIterator> iterators;
    iterators.reserve(last - first);
    for (auto it = first ; it != last ; ++it)
    {
        iterators.push_back(it);
    }
    // Sort the iterators on pointed values
    std::sort(iterators.begin(), iterators.end(),
              mountain_sort_detail::indirect_compare<Compare>(std::move(compare)));

    ////////////////////////////////////////////////////////////
    // Move the values according the iterator's positions

    if (first == last) return;

    // Element where the current cycle starts
    auto start = first;

    while (start != last)
    {
        // Find the element to put in current's place
        auto current = start;
        auto next_pos = current - first;
        // We replace all "sorted" iterators with last to make it
        // possible to find unsorted iterators between cycles
        auto next = std::exchange(iterators[next_pos], last);

        // Process the current cycle
        if (next != current)
        {
            auto tmp = std::move(*current);
            while (next != start)
            {
                *current = std::move(*next);
                current = next;
                auto next_pos = next - first;
                next = std::exchange(iterators[next_pos], last);
            }
            *current = std::move(tmp);
        }

        // Find the next cycle
        do
        {
            ++start;
        }
        while (start != last && iterators[start - first] == last);
    }
}

#endif // MOUNTAIN_SORT_H_
