#include <bits/stdc++.h>
using namespace std;

/**
 * Problem Statement:
There is a directed graph G with N vertices and M edges.
The vertices are numbered 1,2,…,N, and for each i (1≤i≤M),
edge is like x->y. G does not contain directed cycles.
Find the length of the longest directed path in G.
Here, the length of a directed path is the number of edges in it.
*/

/*
Here problem can be modified as if we want maximum path or minimum
path if we are given weight of edges(weighted case) it can be
done with the same approach as below.
*/

vector<vector<int>> graph(100005);
int dp[100005];

int dfs(int node) {
    if (dp[node] != -1) {
        return dp[node];
    }
    int len = 0;
    for (auto &next : graph[node]) {
        len = max(len, 1 + dfs(next));
    }
    return dp[node] = len;
}

int main() {
    int n, m;
    cin >> n >> m;
    memset(dp, -1, sizeof(dp));
    while (m--) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
    }
    int len = 0;
    for (int i = 1; i <= n; i++) {
        len = max(len, dfs(i));
    }

    cout << len;
}