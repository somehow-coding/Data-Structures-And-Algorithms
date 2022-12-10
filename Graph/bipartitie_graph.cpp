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

int change_color(int color) {
    if (color == 1) {
        return 2;
    }
    return 1;
}
/*
doing bfs dfs for one component but can be extended to all components of the graph.
*/

bool dfs(vector<vector<int>> &graph, int node, int color, vector<int> &color_nodes) {
    color_nodes[node] = color;
    for (auto &adj_node : graph[node]) {
        if (color_nodes[adj_node]) {
            if (color_nodes[adj_node] == color) {
                return false;
            }
        } else {
            if (dfs(graph, adj_node, change_color(color), color_nodes)) {
                return false;
            }
        }
    }
    return true;
}

bool bfs(vector<vector<int>> &graph, int node, int color, vector<int> &color_nodes) {
    queue<int> Q;
    Q.push(node);
    color_nodes[color] = color;
    while (Q.size()) {
        int q = Q.size();
        while (q--) {
            node = Q.front();
            Q.pop();
            color = color_nodes[node];
            for (auto &adj_node : graph[node]) {
                if (color_nodes[adj_node]) {
                    if (color_nodes[adj_node] == color) {
                        return false;
                    }
                } else {
                    color_nodes[adj_node] = change_color(color);
                    Q.push(adj_node);
                }
            }
        }
    }
    return true;
}

int main() {
    vector<vector<int>> undir_graph = build_graph(6, {{0, 1}, {1, 2}, {0, 2}, {1, 3}}, 1);
    vector<int> color1(6, 0), color2(6, 0);
    bool d = dfs(undir_graph, 0, 1, color1);
    bool b = bfs(undir_graph, 0, 1, color2);
    cout << "dfs se pata chala hai ki bipartite hai graph " << d << endl;
    cout << "bfs se pata chala hai ki bipartite hai graph " << b << endl;
}