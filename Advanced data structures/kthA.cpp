#include <bits/stdc++.h>
using namespace std;

/** Below implementation is for 0-based node indexing. */

class TreeAnscestor {
    int MAX_BIT = 17;

public:
    vector<vector<int>> blt;
    TreeAnscestor(int n) {
        blt = vector<vector<int>>(n + 1, vector<int>(MAX_BIT, -1));
    }
    // building(initialising) blt(table).
    void build(vector<int> par) {
        // assume par[0] = -1
        int n = par.size();
        for (int i = 0; i < n; ++i) {
            blt[i][0] = par[i];
        }
        for (int j = 1; j < MAX_BIT; ++j) {
            for (int i = 0; i < n; ++i) {
                if (blt[i][j - 1] > 0) {
                    blt[i][j] = blt[blt[i][j - 1]][j - 1];
                }
            }
        }
    }
    // kth parent of node u.
    int query(int u, int k) {
        for (int i = 0; i < MAX_BIT; ++i) {
            if (u < 0) {
                return -1;
            }
            if (k & (1 << i)) {
                u = blt[u][i];
            }
        }
        return u;
    }
};
