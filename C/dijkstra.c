// Dijkstra — shortest path on a non-negative weighted graph (min-heap, adjacency list)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 100005
#define MAXM 200005   // for undirected graphs use 2*m

int head[MAXN], to[MAXM], nxt[MAXM];
long long w[MAXM];
int edge_cnt;

// adjacency list helpers (weighted)
void init_graph() {
    edge_cnt = 0;
    memset(head, -1, sizeof(head));
}
void add_edge(int u, int v, long long weight) {
    to[++edge_cnt] = v;
    w[edge_cnt] = weight;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

/* Simple binary min-heap for pairs (dist, vertex)
   - push duplicates allowed; we skip stale entries when popped (common simple approach)
*/
typedef struct { long long d; int v; } HeapNode;
HeapNode heap[MAXM];
int hsz = 0;

void heap_swap(int i, int j) {
    HeapNode tmp = heap[i]; heap[i] = heap[j]; heap[j] = tmp;
}
void heap_push(long long d, int v) {
    int i = ++hsz;
    heap[i].d = d; heap[i].v = v;
    while (i > 1) {
        int p = i/2;
        if (heap[p].d <= heap[i].d) break;
        heap_swap(p, i); i = p;
    }
}
HeapNode heap_pop() {
    HeapNode ret = heap[1];
    heap[1] = heap[hsz--];
    int i = 1;
    while (1) {
        int l = 2*i, r = l+1, smallest = i;
        if (l <= hsz && heap[l].d < heap[smallest].d) smallest = l;
        if (r <= hsz && heap[r].d < heap[smallest].d) smallest = r;
        if (smallest == i) break;
        heap_swap(i, smallest); i = smallest;
    }
    return ret;
}

/* Dijkstra:
   - n: number of nodes, s: source
   - dist[] initialized to INF, parent[] for path
   - complexity O((n + m) log m) with heap duplicates approach
*/
long long dist[MAXN];
int parent[MAXN];
const long long INF = (1LL<<60);

void dijkstra(int s, int n) {
    // 1) init distances
    for (int i = 1; i <= n; ++i) { dist[i] = INF; parent[i] = -1; }
    hsz = 0;
    // 2) push source
    dist[s] = 0;
    heap_push(0, s);
    // 3) process heap until empty
    while (hsz) {
        HeapNode cur = heap_pop();
        long long d = cur.d; int u = cur.v;
        // 4) skip stale (we previously pushed better dist)
        if (d != dist[u]) continue;
        // 5) relax neighbors
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            long long nd = d + w[e];
            if (nd < dist[v]) {
                dist[v] = nd;
                parent[v] = u;
                heap_push(nd, v);
            }
        }
    }
}

/* Reconstruct path from s to t (same as BFS reconstruction style) */
int reconstruct_path(int t, int path[]) {
    int len = 0;
    if (dist[t] == INF) return 0;
    for (int v = t; v != -1; v = parent[v]) path[len++] = v;
    for (int i=0,j=len-1;i<j;i++,j--) { int tmp = path[i]; path[i]=path[j]; path[j]=tmp; }
    return len;
}

/* Example usage (commented):
int main() {
    int n = 5;
    init_graph();
    add_edge(1,2, 4); add_edge(2,1, 4);
    add_edge(1,3, 1); add_edge(3,1, 1);
    add_edge(3,2, 2); add_edge(2,3, 2);
    add_edge(2,4, 1); add_edge(4,2, 1);
    add_edge(3,5, 5); add_edge(5,3, 5);
    dijkstra(1, n);
    int path[MAXN];
    int len = reconstruct_path(4, path);
    if (!len) printf("unreachable\n");
    else {
        printf("dist to 4 = %lld\npath:", dist[4]);
        for (int i=0;i<len;i++) printf(" %d", path[i]);
        printf("\n");
    }
    return 0;
}
*/

