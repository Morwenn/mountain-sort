[![License](http://img.shields.io/:license-mit-blue.svg)](http://doge.mit-license.org)

**Mountain sort** is an in-place, unstable comparison sort. It is originally inspired
by [cycle sort][1] and [Exact-Sort][2] but has a slightly different goal: while the
former two aim at minimizing the number of writes to the original collection, this
new algorithm's goal is to minimize the number of times the elements of the original
collection are moved around, even though it generally means using more memory. In
the end, **Moutain sort** moves every element between 0 and 2 times.

The name comes from the fact that it's probably the best sorting algorithm if you need
to sort actual mountains by height. Not only will you have to put every mountain back
into the moutain range at most once, but only a few of them should be moved to a
temporary location (while every moutain would be moved to a temporary location before
being put back in the mountain range with a typical cycle sort).

### The algorithm

**Moutain sort** is a two-phase sorting algorithm: first it copies every iterator
into a vector and sorts this vector with `std::sort` using the values the iterators
point to to sort them. Then it performs a derivative from cycle sort to actually
move the values, with the following differences:
* It can find the final position of any element by a simple lookup into the sorted
iterators arrays.
* Instead of swapping every element ever with a temporary, it stores only the first
element of each cycle into a temporary then moves the other ones directly to their
final place before relocating the first element of the cycle to its final position
in the original collection.
* Just like Exact-Sort, it also maintains a boolean array to tell which elements have
already been moved to their final location and which ones are still to be moved.

To sum up: O(n log n) comparisons, O(n) memory, but only for iterators, not for
actual values. The current version is unstable because it uses `std::sort` to sort
the iterators, but it could easily be made stable by using `std::stable_sort` or
any other stable sorting algorithm instead.

### Using this project

This project requires C++14 or a more recent version of C++. The only C++ file of
the project can be copy-pasted at will and included as is, providing the following
`mountain_sort` function, which acts as a drop-in replacement for `std::sort`:

```cpp
template<
    typename RandomAccessIterator,
    typename Compare = std::less<>
>
void mountain_sort(RandomAccessIterator first, RandomAccessIterator last,
                   Compare compare={});
```


  [1]: https://en.wikipedia.org/wiki/Cycle_sort
  [2]: http://www.geocities.ws/p356spt/
