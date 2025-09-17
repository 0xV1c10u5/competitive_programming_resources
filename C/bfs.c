// BFS — shortest path in an unweighted graph (adjacency list + path reconstruction)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005       // max number of nodes
#define MAXM 200005       // max number of directed edges (use 2*m for undirected)

int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;

// 1) Initialize adjacency list
// 2) add_edge(u,v): push v into adjacency[u]
void init_graph() {
    edge_cnt = 0;
    memset(head, -1, sizeof(head));
}
void add_edge(int u, int v) {
    // step 1: add entry index = ++edge_cnt
    // step 2: to[idx] = v; nxt[idx] = head[u]; head[u] = idx
    to[++edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

/* BFS: shortest path from s in unweighted graph
   - dist[] holds distances (or -1 if unreachable)
   - parent[] for path reconstruction
   - complexity O(n + m)
*/
int dist[MAXN], parent[MAXN], q[MAXN];

void bfs(int s, int n) {
    // 1) init: mark all nodes unvisited (-1)
    for (int i = 1; i <= n; ++i) { dist[i] = -1; parent[i] = -1; }
    // 2) queue push s
    int headq = 0, tailq = 0;
    q[tailq++] = s; dist[s] = 0; parent[s] = -1;
    // 3) process until queue empty
    while (headq < tailq) {
        int u = q[headq++];               // pop front
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (dist[v] == -1) {
                // 4) visit neighbor, set distance and parent, push to queue
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q[tailq++] = v;
            }
        }
    }
}

// Reconstruct path from s to t using parent[]
// returns length in path[], path[0]..path[len-1]
int reconstruct_path(int t, int path[]) {
    int len = 0;
    if (dist[t] == -1) return 0; // no path
    for (int v = t; v != -1; v = parent[v]) path[len++] = v;
    // reverse path in place
    for (int i = 0, j = len-1; i < j; ++i, --j) {
        int tmp = path[i]; path[i] = path[j]; path[j] = tmp;
    }
    return len;
}

/* Example usage (commented):
int main() {
    int n = 6, m = 7;
    init_graph();
    add_edge(1,2); add_edge(2,1); // undirected: add both directions
    add_edge(1,3); add_edge(3,1);
    add_edge(2,4); add_edge(4,2);
    add_edge(3,5); add_edge(5,3);
    add_edge(5,6); add_edge(6,5);
    bfs(1, n);
    int path[MAXN];
    int len = reconstruct_path(6, path);
    if (len==0) printf("No path\n");
    else {
        printf("Distance = %d\nPath:", dist[6]);
        for (int i=0;i<len;i++) printf(" %d", path[i]);
        printf("\n");
    }
    return 0;
}
*/

