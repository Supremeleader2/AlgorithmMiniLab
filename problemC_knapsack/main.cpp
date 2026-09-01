// Problem C: Budgeted Study Plan — 0/1 Knapsack (Dynamic Programming)
//
// Idea: Let dp[w] = maximum value achievable using time budget w,
// considering items processed so far. For each item i (time t_i,
// value v_i) we can either skip it (dp[w] unchanged) or take it
// (dp[w] = dp[w - t_i] + v_i), provided w >= t_i. Taking the better
// of the two gives the recurrence:
//
//     dp_i[w] = max(dp_{i-1}[w], dp_{i-1}[w - t_i] + v_i)
//
// A 2D table dp[i][w] is the direct translation of this recurrence,
// but since row i only depends on row i-1, we can collapse it into
// a single 1D array as long as we iterate w from T down to t_i for
// each item -- that guarantees dp[w - t_i] still holds the *previous
// item's* value (i.e., the "0/1" / take-at-most-once property),
// rather than a value already updated by the current item (which
// would allow reuse, turning this into an unbounded knapsack).
//
// Correctness argument (why the recurrence is right): dp[w] considers
// every subset of the first i items with total time <= w and keeps
// the best value; this is exactly optimal-substructure -- the best
// solution either includes item i or it doesn't, and in both cases
// the remaining choice must be optimal for the corresponding
// sub-budget.
//
// Time:  O(n * T)  -- n items, each doing an O(T) inner loop
// Space: O(T)       -- one 1D array of size T + 1 (rolling rows)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, T;
    if (!(cin >> n >> T)) return 0;
    vector<int> t(n);
    vector<ll> v(n);
    for (int i = 0; i < n; i++) cin >> t[i] >> v[i];

    vector<ll> dp(T + 1, 0);
    for (int i = 0; i < n; i++) {
        // Iterate downward so each item is only used once per pass.
        for (int w = T; w >= t[i]; w--) {
            dp[w] = max(dp[w], dp[w - t[i]] + v[i]);
        }
    }

    cout << dp[T] << "\n";
    return 0;
}
