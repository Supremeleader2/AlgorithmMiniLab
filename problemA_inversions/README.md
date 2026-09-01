# Problem A — Inversion Counter (Divide & Conquer)

Counts the number of inversions in an array: pairs `(i, j)` with `i < j` and `A[i] > A[j]`.

## Build

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
```

## Run

```bash
./main < tests/test1_input.txt
```

Input format:
```
n
a1 a2 ... an
```

Output: a single 64-bit integer, the inversion count.

## Complexity

- Time: `O(n log n)`
- Space: `O(n)` auxiliary buffer + `O(log n)` recursion stack

## Tests

Three test cases live in `tests/`: a mixed example, an already-sorted
array (0 inversions), and a reverse-sorted array (worst case, `n(n-1)/2`
inversions).
