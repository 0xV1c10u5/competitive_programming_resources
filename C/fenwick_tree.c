// Fenwick Tree (Binary Indexed Tree) — point update, prefix sum (1-indexed)

#include <stdio.h>

#define MAXN 100005
int N;                 // current array size (1-indexed)
long long bit[MAXN];   // BIT array

// 1) point add: add value 'delta' at index idx
// 2) propagate upward using idx += idx & -idx
void bit_add(int idx, long long delta) {
    while (idx <= N) {
        bit[idx] += delta;
        idx += idx & -idx;
    }
}

// prefix sum [1..idx]
long long bit_sum(int idx) {
    long long res = 0;
    while (idx > 0) {
        res += bit[idx];
        idx -= idx & -idx;
    }
    return res;
}

// sum over [l..r] = bit_sum(r) - bit_sum(l-1)

/* Example usage (commented):
int main() {
    N = 8;
    // initialize with zeros
    for (int i=0;i<=N;i++) bit[i] = 0;
    // build from initial array a[1..N] by doing bit_add(i, a[i]) for each i
    int a[9] = {0, 5, 3, 7, 1, 2, 0, 4, 6}; // a[1]..a[8]
    for (int i=1; i<=N; ++i) bit_add(i, a[i]);
    printf("sum 1..4 = %lld\n", bit_sum(4));
    bit_add(3, 5); // a[3] += 5
    printf("sum 2..5 = %lld\n", bit_sum(5) - bit_sum(1));
    return 0;
}
*/

