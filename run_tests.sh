#!/usr/bin/env bash
# Builds each problem and runs its tests/*_input.txt against
# tests/*_expected.txt. Exits non-zero if any test fails.
set -u
FAIL=0

for d in problemA_inversions problemB_rooms problemC_knapsack; do
    echo "=== $d ==="
    g++ -std=c++17 -O2 -Wall -Wextra -pedantic "$d/main.cpp" -o "$d/main"
    if [ $? -ne 0 ]; then
        echo "  COMPILE FAILED"
        FAIL=1
        continue
    fi
    for infile in "$d"/tests/*_input.txt; do
        [ -e "$infile" ] || continue
        base=$(basename "$infile" _input.txt)
        expfile="$d/tests/${base}_expected.txt"
        got=$("./$d/main" < "$infile")
        exp=$(cat "$expfile")
        if [ "$got" = "$exp" ]; then
            echo "  $base: PASS"
        else
            echo "  $base: FAIL (got '$got', expected '$exp')"
            FAIL=1
        fi
    done
done

if [ $FAIL -eq 0 ]; then
    echo "All tests passed."
else
    echo "Some tests FAILED."
fi
exit $FAIL
