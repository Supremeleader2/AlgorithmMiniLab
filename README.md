# Algorithm Design Mini-Lab

Three problems, each solved with the algorithm design technique that
fits its structure best:

| Problem | Technique | File | Complexity |
|---|---|---|---|
| A — Inversion Counter | Divide & Conquer (merge sort) | `problemA_inversions/main.cpp` | `O(n log n)` time, `O(n)` space |
| B — Minimum Meeting Rooms | Greedy (sweep line + min-heap) | `problemB_rooms/main.cpp` | `O(m log m)` time, `O(m)` space |
| C — Budgeted Study Plan | Dynamic Programming (0/1 knapsack) | `problemC_knapsack/main.cpp` | `O(nT)` time, `O(T)` space |

See `report.md` for the full write-up (algorithm idea, pseudocode,
worked examples, and complexity justification for each problem).

## Build everything

Each problem is a standalone `main.cpp`, compiled the same way:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
```

## Run everything

```bash
./problemA_inversions/main < problemA_inversions/tests/test1_input.txt
./problemB_rooms/main       < problemB_rooms/tests/test1_input.txt
./problemC_knapsack/main    < problemC_knapsack/tests/test1_input.txt
```

All programs read from stdin and write a single value to stdout —
no interactive input.

## Run all tests at once

```bash
./run_tests.sh
```

This compiles all three problems and checks every file under each
`tests/` folder (`*_input.txt` against `*_expected.txt`), printing
PASS/FAIL per case.

## Repository layout

```
problemA_inversions/
  main.cpp
  README.md
  tests/            (4 cases: mixed, sorted, reverse-sorted, duplicates)
problemB_rooms/
  main.cpp
  README.md
  tests/            (4 cases: example, back-to-back, all-overlap, identical starts)
problemC_knapsack/
  main.cpp
  README.md
  tests/            (4 cases: example, nothing fits, multiple choices, tight budget)
report.md
run_tests.sh
README.md           (this file)
```

## Assumptions

- All inputs are well-formed and within the stated constraints (no
  malformed-input handling is implemented).
- Meetings that touch at a shared endpoint (`e_i == s_j`) do **not**
  count as overlapping, per the spec's clarification.
- All potentially large results (inversion count, knapsack value) use
  `long long` to avoid 32-bit overflow.
