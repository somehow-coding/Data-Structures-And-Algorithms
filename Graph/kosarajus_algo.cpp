#include <bits/stdc++.h>
using namespace std;

/**
 * strongly connected components -> kosaraju's algorithm 
 * concept of scc_s are there for directed graph only.
 * 
 * so scc is where every node can reach to any other node in scc
 * 
 * How to differentiate b/w any two scc that is we need to stop 
 * one guy going to one scc from another scc
 * 
 * kosaraju's algorithm
 * 
 * 1> sort all the nodes according to finish time, last node
 * which have last finish time comes at top of the stack.
 * 
 * 2> reverse the graph
 * 
 * 3> do dfs on the nodes accordingly, last node(top node of stack) 
 * to be visited first and so on.
*/

void dfs1(vector<vector<int>> &g, int u, stack<int> &st, vector<int> &vis) {
    vis[u] = 1;
    for (int v: g[u]) {
        if (!vis[v]) {
            dfs1(g, v, st, vis);
        }
    }
    st.push(u);
}

void dfs2(vector<vector<int>> &g, int u, vector<int> &vis) {
    vis[u] = 1;
    for (int v: g[u]) {
        if (!vis[v]) {
            dfs2(g, v, vis);
        }
    }
}

int cnt_sccs(int n, vector<vector<int>> &g) {
    int cnt = 0;
    vector<int> vis(n, 0);
    stack<int> st;
    for (int u = 0; u < n; u++) {
        if (!vis[u]) {
            dfs1(g, u, st, vis);
        }
    }
    vector<vector<int>> rg(n);
    for (int u = 0; u < n; u++) {
        for (int v: g[u]) {
            rg[v].push_back(u);
        }
    }

    fill(vis.begin(), vis.end(), 0);
    while (st.size()) {
        int u = st.top(); st.pop();
        if (!vis[u]) {
            //will completely traverse the whole scc in one go
            ++cnt;
            dfs2(rg, u, vis);
        }
    }
    return cnt;
}

int main() {
    vector<vector<int>> g(7);
    g[0] = {1};
    g[1]= {2};
    g[2] = {3,0};
    g[3] = {4};
    g[4] = {5};
    g[5] = {6};
    g[6] = {4};
    cout<<cnt_sccs(7, g);
}
