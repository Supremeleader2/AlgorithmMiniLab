// Problem B: Minimum Meeting Rooms (Greedy)
//
// Idea: Sort meetings by start time. Walk through them in order,
// keeping a min-heap of the end times of meetings currently "in
// progress" (i.e., occupying a room). For each new meeting:
//   - If the room that frees up earliest (heap top) ends at or
//     before this meeting's start, reuse that room (pop, then push
//     the new end time).
//   - Otherwise, no existing room is free yet, so open a new room
//     (just push; don't pop).
// The running count of rooms opened (`rooms`) never decreases, and
// it only increases exactly when the heap size grows past its prior
// maximum, so at the end `rooms` equals the peak number of
// simultaneously active meetings, which is the answer.
//
// Greedy-choice justification: reusing the room that frees soonest
// is always at least as good as reusing any other free room or
// opening a new one, because it keeps the largest possible set of
// rooms free for future meetings (standard interval partitioning
// argument, exchange-argument provable).
//
// Time:  O(m log m)  -- sorting + m heap operations at O(log m) each
// Space: O(m)         -- heap holds at most m end times

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    if (!(cin >> m)) return 0;
    vector<pair<ll, ll>> meetings(m);
    for (int i = 0; i < m; i++) {
        cin >> meetings[i].first >> meetings[i].second;
    }

    sort(meetings.begin(), meetings.end()); // sort by start time

    priority_queue<ll, vector<ll>, greater<ll>> endTimes; // min-heap
    int rooms = 0;

    for (auto &mt : meetings) {
        ll s = mt.first, e = mt.second;
        if (!endTimes.empty() && endTimes.top() <= s) {
            // earliest-freeing room is free by time s: reuse it
            endTimes.pop();
        } else {
            // no room free yet: need a new one
            rooms++;
        }
        endTimes.push(e);
    }

    cout << rooms << "\n";
    return 0;
}
