#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> build_graph(int n, vector<vector<int>> edges, int bi_direction) {
    vector<vector<int>> graph(n);
    for (auto &edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        if (bi_direction) {
            graph[edge[1]].push_back(edge[0]);
        }
    }
    return graph;
}

/*
*Topological sorting is only for directed acyclic graph,
as for acyclic and undirected graph topological sorted order
makes no sense(why?).
and according to it we should have u before v in order if we have
edge from u to v.
*/

/*Topological sort using dfs*/

void dfs(vector<vector<int>> &graph, int node, vector<int> &vis, vector<int> &topo_sort) {
    vis[node] = true;
    for (auto &adj_node : graph[node]) {
        if (!vis[adj_node]) {
            dfs(graph, adj_node, vis, topo_sort);
        }
    }
    topo_sort.push_back(node);
}

void topo_sort_dfs(vector<vector<int>> &graph, int n) {
    vector<int> vis(n, 0);
    vector<int> topo_sort;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(graph, i, vis, topo_sort);
        }
    }
    reverse(begin(topo_sort), end(topo_sort));
    cout << "Topological sorting by dfs" << endl;
    for (int x : topo_sort) {
        cout << x << " ";
    }
    cout << endl;
}

/*Topological sorting using bfs(kahn's algorithm)*/
void topo_sort_bfs(vector<vector<int>> &graph, int n) {
    vector<int> indegree(n, 0);
    // i->j
    for (int i = 0; i < n; i++) {
        for (int j : graph[i]) {
            indegree[j]++;
        }
    }
    queue<int> Q;
    for (int i = 0; i < n; i++) {
        if (!indegree[i]) {
            Q.push(i);
        }
    }
    cout << "Topological sorting by bfs" << endl;

    while (Q.size()) {
        int q = Q.size();
        while (q--) {
            int i = Q.front();
            Q.pop();
            cout << i << " ";
            for (int j : graph[i]) {
                indegree[j]--;
                if (!indegree[j]) {
                    Q.push(j);
                }
            }
        }
    }
}

int main() {
    vector<vector<int>> undir_graph = build_graph(4, {{1, 0}, {1, 2}, {3, 2}, {1, 3}}, 0);
    topo_sort_dfs(undir_graph, 4);
    topo_sort_bfs(undir_graph, 4);
}