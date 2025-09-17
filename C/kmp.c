// KMP (Knuth–Morris–Pratt) — pattern search in O(n + m)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* compute_pi:
   - builds the prefix-function (pi) for pattern p of length m
   - pi[i] = length of longest proper prefix of p[0..i] which is also suffix
   Steps:
   1) pi[0] = 0
   2) for i=1..m-1: fallback via j = pi[i-1] while mismatch
   3) if match, ++j; pi[i] = j
*/
void compute_pi(const char *p, int m, int *pi) {
    pi[0] = 0;
    int j = 0;
    for (int i = 1; i < m; ++i) {
        // fallback until we can extend
        while (j > 0 && p[i] != p[j]) j = pi[j-1];
        if (p[i] == p[j]) ++j;
        pi[i] = j;
    }
}

/* kmp_search:
   - finds all occurrences of pattern p (length m) in text s (length n)
   - writes starting indices into out[]; returns number of matches
   Steps:
   1) prepare pi for pattern
   2) scan text with pointer j for matched prefix len
   3) when j==m, record occurrence i-m+1 and fallback j = pi[j-1]
*/
int kmp_search(const char *s, const char *p, int *out) {
    int n = strlen(s), m = strlen(p);
    if (m == 0) return 0;
    int *pi = (int*)malloc(sizeof(int) * m);
    compute_pi(p, m, pi);
    int j = 0, cnt = 0;
    for (int i = 0; i < n; ++i) {
        while (j > 0 && s[i] != p[j]) j = pi[j-1];
        if (s[i] == p[j]) ++j;
        if (j == m) {
            out[cnt++] = i - m + 1; // match starting index (0-based)
            j = pi[j-1];           // continue searching
        }
    }
    free(pi);
    return cnt;
}

/* Example usage (commented):
int main() {
    const char *text = "ababcababcab";
    const char *pat = "ababc";
    int out[100];
    int found = kmp_search(text, pat, out);
    printf("Found %d occurrences at indices:", found);
    for (int i=0;i<found;i++) printf(" %d", out[i]);
    printf("\n");
    return 0;
}
*/

