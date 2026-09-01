# Report

## Problem A — Inversion Counter for Quality Control

### Problem summary

Given an array `A` of `n` integers, count the number of pairs
`(i, j)` with `i < j` and `A[i] > A[j]`. A brute-force check of every
pair is `O(n^2)`, which is too slow at `n` up to `2 * 10^5`.

### Algorithm idea

This is a **divide & conquer** problem: split the array in half,
recursively count inversions entirely within the left half and
entirely within the right half, then count the "cross" inversions —
pairs where the smaller index is in the left half and the larger
index is in the right half — during the merge step of merge sort.
The key trick: if the two halves are each already sorted, then when
we take an element from the right half before we've finished the
left half, that element is smaller than **every remaining element**
in the left half, so it forms an inversion with all of them at once —
no need to check them individually.

### Pseudocode

```
function mergeCount(A, l, r):        # counts inversions in A[l..r)
    if r - l <= 1: return 0
    m = l + (r - l) / 2
    inv = mergeCount(A, l, m) + mergeCount(A, m, r)
    i = l, j = m, k = l
    tmp = new array of size (r - l)
    while i < m and j < r:
        if A[i] <= A[j]:
            tmp[k] = A[i]; i += 1
        else:
            inv += (m - i)          # A[j] beats all of A[i..m-1]
            tmp[k] = A[j]; j += 1
        k += 1
    copy any remaining A[i..m) or A[j..r) into tmp
    copy tmp back into A[l..r)
    return inv

function countInversions(A):
    return mergeCount(A, 0, length(A))
```

### Example run

Input: `A = [2, 4, 1, 3, 5]`

- Split into `[2, 4]` and `[1, 3, 5]`.
- `[2, 4]`: no inversions internally (already sorted); merging is trivial.
- `[1, 3, 5]`: split into `[1]` and `[3, 5]`, no inversions, merges cleanly.
- Merge `[2, 4]` with `[1, 3, 5]`:
  - Compare `2` vs `1`: `1` is smaller, and there are 2 elements left
    in the left half (`2, 4`) → add 2 inversions. Take `1`.
  - Compare `2` vs `3`: `2` is smaller and comes from the left → take `2`, no new inversions.
  - Compare `4` vs `3`: `3` is smaller, 1 element left in the left half (`4`) → add 1 inversion. Take `3`.
  - Left half exhausted, append remaining right half `5`.
  - Total cross inversions: `2 + 1 = 3`.
- Grand total: `0 (left) + 0 (right) + 3 (cross) = 3`.

Output: `3` — matches the pairs `(2,1)`, `(4,1)`, `(4,3)`.

### Complexity analysis

- **Time:** Each level of recursion does `O(n)` work total across all
  merges at that level, and there are `O(log n)` levels, giving the
  recurrence `T(n) = 2T(n/2) + O(n)`, which solves to `T(n) = O(n log n)`
  by the Master Theorem (case 2).
- **Space:** `O(n)` for the single reusable auxiliary buffer, plus
  `O(log n)` for the recursion call stack.

---

## Problem B — Minimum Meeting Rooms (Scheduling)

### Problem summary

Given `m` meetings `(s_i, e_i)`, find the minimum number of rooms
needed so no two overlapping meetings share a room. Meetings that
touch at a shared endpoint don't conflict.

### Algorithm idea

This is a **greedy** problem, specifically an interval-partitioning
problem. Sort meetings by start time. Maintain a min-heap of the end
times of meetings currently occupying a room. For each new meeting,
check the room whose meeting ends soonest (heap top): if it has
already ended by the time the new meeting starts, reuse that room;
otherwise, no room is free, so open a new one. The room count only
ever grows when the heap grows past its previous size, so the final
count equals the peak number of simultaneously active meetings.

**Greedy-choice property:** always reusing the earliest-freeing room
is optimal. If some other strategy used a different free room (or
opened a new one) instead of the earliest-freeing one, we could swap
that choice for the earliest-freeing room without ever causing a
future conflict, since the earliest-freeing room is free for at
least as much of the future as any other free room. This exchange
argument shows the greedy choice never does worse.

### Pseudocode

```
function minRooms(meetings):
    sort meetings by start time
    minHeap = empty min-heap of end times
    rooms = 0
    for (s, e) in meetings:
        if minHeap is not empty and minHeap.top() <= s:
            minHeap.pop()            # reuse the earliest-freeing room
        else:
            rooms += 1                # no room free yet, open a new one
        minHeap.push(e)
    return rooms
```

### Example run

Meetings: `(0, 30), (5, 10), (15, 20)` (already sorted by start).

- `(0, 30)`: heap empty → open room 1. Heap: `[30]`. `rooms = 1`.
- `(5, 10)`: heap top `30 > 5`, no room free → open room 2. Heap: `[10, 30]`. `rooms = 2`.
- `(15, 20)`: heap top `10 <= 15`, reuse that room → pop `10`, push `20`. Heap: `[20, 30]`. `rooms` stays `2`.

Output: `2`.

### Complexity analysis

- **Time:** Sorting is `O(m log m)`. Each of the `m` meetings does at
  most one push and one pop on a heap of size `O(m)`, each `O(log m)`,
  for `O(m log m)` total. Overall: `O(m log m)`.
- **Space:** `O(m)` for the heap (and the sorted array of meetings).

---

## Problem C — Budgeted Study Plan (0/1 Knapsack Variant)

### Problem summary

Given `n` modules, each with a time cost `time[i]` and a value
`value[i]`, and a total time budget `T`, choose a subset of modules
(each usable at most once) maximizing total value without exceeding
`T`. A brute-force search over all `2^n` subsets is infeasible for
`n` up to `2000`.

### Algorithm idea

This is the classic **0/1 knapsack**, solved with **dynamic
programming**. Define `dp[i][w]` as the best value achievable using
only the first `i` items with a time budget of `w`. Each item is
either excluded (`dp[i-1][w]`) or included, provided `w >= time[i]`
(`dp[i-1][w - time[i]] + value[i]`); we take the max of the two. Since
row `i` only ever reads from row `i-1`, the 2D table collapses into a
single 1D array of size `T + 1`, as long as each item's inner loop
walks `w` from `T` down to `time[i]` — that ordering guarantees we
read the "previous item's" value at `dp[w - time[i]]` before it gets
overwritten for the current item, which is what enforces the
take-at-most-once ("0/1") constraint.

### Pseudocode

```
function knapsack(items, T):        # items[i] = (time_i, value_i)
    dp = array of size (T + 1), all zeros
    for (time_i, value_i) in items:
        for w from T down to time_i:
            dp[w] = max(dp[w], dp[w - time_i] + value_i)
    return dp[T]
```

### Example run

Modules: `(time=3, value=4)`, `(time=4, value=5)`, `(time=7, value=10)`, `T = 10`.

- Start: `dp = [0, 0, ..., 0]` (indices `0..10`).
- After item `(3, 4)`: every `dp[w]` for `w >= 3` becomes `4`
  (taking just this item).
- After item `(4, 5)`: for each `w` from `10` down to `4`, compare
  taking this item (`dp[w-4] + 5`) against not taking it. Notably
  `dp[7] = max(4, dp[3] + 5) = max(4, 9) = 9` (items 1+2 together).
  Similarly `dp[8..10]` become `9`.
- After item `(7, 10)`: for `w = 10`, compare `dp[10] = 9` against
  `dp[3] + 10 = 4 + 10 = 14` (item 1 + item 3). `14` wins.
  Final `dp[10] = 14`.

Output: `14` — matches taking modules 1 and 3 (time `3+7=10`, value `4+10=14`).

### Complexity analysis

- **Time:** `O(n * T)` — `n` items, each with an inner loop of length
  up to `T`.
- **Space:** `O(T)` — a single 1D `dp` array of size `T + 1`, reused
  across items instead of a full `O(n * T)` 2D table.

### Final Thoughts
# Design Choices: Why These Approaches
 
## Problem A — Merge Sort over Fenwick Tree
 
A Binary Indexed Tree (Fenwick Tree) can also count inversions in
`O(n log n)` by scanning left-to-right and querying "how many larger
elements have I already seen." Both approaches have identical
asymptotic complexity, so the choice came down to implementation
risk: a Fenwick Tree needs a separate data structure with its own
indexing logic, while merge sort's inversion count falls out
naturally from a merge step most implementations already need to get
right. We chose the simpler, less error-prone option since it
doesn't cost any speed.
 
## Problem B — Heap-based greedy over Timeline Sweep
 
An alternative is to sort all start times and end times separately
and sweep through them as `+1`/`-1` events, tracking the running
maximum. This is equally fast (`O(m log m)`) and avoids a priority
queue. We chose the heap approach because it models the problem more
directly — it assigns and reuses actual rooms one meeting at a time,
which made the greedy-choice argument (always reuse the
earliest-freeing room) easier to state and prove correct.
 
## Problem C — 1D DP array over 2D DP table
 
The standard textbook formulation of 0/1 knapsack uses a 2D table
`dp[i][w]`, which is easier to visualize but uses `O(n·T)` memory —
at `n = T = 2000`, that's 4 million entries. Since each row of the
table only depends on the row before it, we collapsed it into a
single 1D array of size `T + 1`, cutting memory to `O(T)` without
changing the `O(n·T)` time complexity. The only added subtlety is
iterating the budget dimension backwards per item, which is what
preserves the "take-at-most-once" constraint.
 
## General principle
 
In all three cases, a valid, often simpler alternative existed with
the *same* time complexity. We favored the option that was easiest
to implement correctly and/or used the least memory, rather than the
one that was conceptually simplest to first understand — a common
trade-off in competitive and production code alike.
