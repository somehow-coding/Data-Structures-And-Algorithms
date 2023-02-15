#include <bits/stdc++.h>
using namespace std;

/**
 * Bridges in Graph.
 *
 * bridge : any edge after removing graph will be broken into
 * two or more components.
 *
 * algo is tarzan's algorithm.
 * approach 
 * time[] -> dfs timer at node i
 * low[] -> min of time insertion of all adjacent nodes of
 * the node except for the parent.
 * low[u] = min(low[v] for every v except for parent)
 *
 * bridge: u -> v
 * if (time[u] < low[v]) then we can't reach u via v by another
 * route in graph.
 *
 * sc = O(2E + V + 3N)
 * tc = O(v + 2E)
 */
int timer = 0;
vector<int> tim, low, vis;
vector<vector<int>> bridges;
void dfs(vector<vector<int>> &g, int u, int p) {
    vis[u] = 1;
    tim[u] = low[u] = ++timer;

    for (int v : g[u]) {
        if (vis[v]) {
            if (v != p)
                low[u] = min(low[u], low[v]);
            continue;
        }
        dfs(g, v, u);
        if (tim[u] < low[v]) {
            bridges.push_back({u, v});
        }
        low[u] = min(low[u], low[v]);
    }
}

vector<vector<int>> findBridges(vector<vector<int>> &g, int n) {
    tim.resize(n, 0), low.resize(n, 0), vis.resize(n, 0);
    dfs(g, 0, -1);
    return bridges;
}
