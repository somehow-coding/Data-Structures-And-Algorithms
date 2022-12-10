#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
    vector<vector<int>> graph;
    Graph(int num_of_nodes, vector<vector<int>> edges, bool bi_directional) {
        graph.resize(num_of_nodes);
        if (bi_directional) {
            for (vector<int> &edge : edges) {
                graph[edge[0]].push_back(edge[1]);
                graph[edge[1]].push_back(edge[0]);
            }
        } else {
            for (vector<int> &edge : edges) {
                graph[edge[0]].push_back(edge[1]);
            }
        }
    }
    vector<int> dfs_trav;
    vector<int> bfs_trav;
};

/*here code is for one component which all connected*/
/*but code can be extended for all components*/

/*in bfs and dfs we need visited array so to avoid again visit
whether it is directed or undirected graph*/

void bfs(Graph &my_graph, int node, vector<int> &vis) {
    queue<int> Q;
    Q.push(node);
    vis[node] = 1;
    while (Q.size()) {
        int n = Q.size();
        while (n--) {
            node = Q.front();
            Q.pop();
            my_graph.bfs_trav.push_back(node);
            for (int adj_node : my_graph.graph[node]) {
                if (!vis[adj_node]) {
                    vis[adj_node] = 1;
                    Q.push(adj_node);
                }
            }
        }
    }
}

void dfs(Graph &my_graph, int node, vector<int> &vis) {
    vis[node] = 1;
    my_graph.dfs_trav.push_back(node);
    for (auto &adj_node : my_graph.graph[node]) {
        if (!vis[adj_node]) {
            dfs(my_graph, adj_node, vis);
        }
    }
}

int main() {
    Graph my_graph(5, {{0, 1}, {0, 2}, {4, 2}, {1, 3}, {3, 4}}, true);
    int start_node = 0;
    vector<int> vis(5, 0);
    bfs(my_graph, start_node, vis);
    cout << "BFS: ";
    for (int node : my_graph.bfs_trav) {
        cout << node << " ";
    }
    cout << "\n";
    cout << "DFS: ";
    vector<int> v(5, 0);
    dfs(my_graph, 0, v);
    for (int node : my_graph.dfs_trav) {
        cout << node << " ";
    }
}