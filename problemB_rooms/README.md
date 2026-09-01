# Problem B — Minimum Meeting Rooms (Greedy)

Computes the minimum number of rooms needed so that no two overlapping
meetings share a room. Meetings ending at time `t` do not conflict with
meetings starting at time `t`.

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
m
s1 e1
s2 e2
...
sm em
```

Output: a single integer, the minimum number of rooms.

## Complexity

- Time: `O(m log m)` — sort + heap operations
- Space: `O(m)` — heap of end times

## Tests

Three test cases in `tests/`: the example from the spec (needs 2 rooms),
back-to-back non-overlapping meetings (needs 1 room), and four fully
nested/overlapping meetings (needs 4 rooms).
