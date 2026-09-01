# Problem C — Budgeted Study Plan (0/1 Knapsack, Dynamic Programming)

Computes the maximum total value achievable by picking a subset of
modules (each usable at most once) whose total time does not exceed
budget `T`.

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
n T
t1 v1
t2 v2
...
tn vn
```

Output: a single 64-bit integer, the maximum achievable value.

## Complexity

- Time: `O(n * T)`
- Space: `O(T)` — 1D DP array reused across items (rolled from the
  conceptual 2D `dp[i][w]` table)

## Tests

Three test cases in `tests/`: the spec's worked example (answer 14),
a case where every item is too big to fit (answer 0), and a case with
multiple valid combinations where the DP must pick the best one
(answer 11).
