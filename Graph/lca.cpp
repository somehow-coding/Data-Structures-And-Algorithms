#include <bits/stdc++.h>
using namespace std;

/** code is 1-based indexing **/

class LCA {
    int MAX = 11;
    vector<vector<int>> blt, T;
    vector<int> level;
    int n;

public:
    void setBLT() {
        for (int j = 1; j < MAX; ++j) {
            for (int i = 1; i <= n; ++i) {
                if (blt[i][j - 1] > 0) {
                    blt[i][j] = blt[blt[i][j - 1]][j - 1];
                }
            }
        }
    }

    void dfs(int u, int l) {
        level[u] = l;
        for (int v : T[u]) {
            blt[v][0] = u;
            dfs(v, l + 1);
        }
    }

    LCA(vector<vector<int>> &T) {
        n = T.size();
        this->T = T;
        level = vector<int>(n + 1);
        blt = vector<vector<int>>(n + 1, vector<int>(MAX + 1, -1));
        dfs(1, 0);
        setBLT();
    }

    int findLCA(int u, int v) {
        if (level[u] < level[v]) {
            swap(u, v);
        }
        int k = level[u] - level[v];
        for (int i = 0; i < MAX; ++i) {
            if (k & (1 << i)) {
                u = blt[u][i];
            }
        }
        if (u == v) {
            return u;
        }
        for (int i = MAX - 1; i >= 0; --i) {
            if (blt[u][i] != blt[v][i]) {
                u = blt[u][i], v = blt[v][i];
            }
        }
        return blt[u][0];
    }
};
