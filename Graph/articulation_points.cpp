#include<bits/stdc++.h>
using namespace std;

int timer = 0;
vector<int> vis, tim, low, flag;
vector<vector<int>> g;

// fc : dfs(0, -1);

void dfs(int u, int p) {
    vis[u] = 1;
    tim[u] = low[u] = ++timer;
    int child = 0;
    for (int v: g[u]) {
        if (v == p) continue;
        if (!vis[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= tim[u] && p != -1) {
                flag[u] = 1;
            }
            child++;
        }
        else {
            low[u] = min(low[u], tim[v]);
        }
        if (child > 1 and p == -1) {
            flag[u] = 1;
        }
    }
}
