// Problem A: Inversion Counter (Divide & Conquer)
//
// Idea: A merge sort naturally counts inversions as a side effect.
// When merging two sorted halves [l, m) and [m, r), every time we
// take an element from the right half BEFORE finishing the left
// half, that element is smaller than all the remaining (m - i)
// elements still sitting in the left half. Each of those forms an
// inversion with it, so we add (m - i) to the running count.
//
// Time:  O(n log n)  -- standard merge sort recurrence T(n) = 2T(n/2) + O(n)
// Space: O(n)         -- one auxiliary buffer reused across merges,
//                         plus O(log n) recursion stack

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Merge [l, m) and [m, r) in-place (within a[]), counting inversions.
static ll mergeCount(vector<ll> &a, vector<ll> &tmp, int l, int r) {
    if (r - l <= 1) return 0; // 0 or 1 element: nothing to do

    int m = l + (r - l) / 2;
    ll inv = mergeCount(a, tmp, l, m) + mergeCount(a, tmp, m, r);

    int i = l, j = m, k = l;
    while (i < m && j < r) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            // a[j] is smaller than a[i..m-1]: that's (m - i) inversions
            inv += (m - i);
            tmp[k++] = a[j++];
        }
    }
    while (i < m) tmp[k++] = a[i++];
    while (j < r) tmp[k++] = a[j++];
    for (int x = l; x < r; x++) a[x] = tmp[x];

    return inv;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<ll> tmp(n);
    ll inv = mergeCount(a, tmp, 0, n);

    cout << inv << "\n";
    return 0;
}
