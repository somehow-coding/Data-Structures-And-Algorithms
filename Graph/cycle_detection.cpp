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

/***cylce detection in undirected graph***/
/*we need to consider all components so we need to keep track of all nodes
such that we cover all components and for each component we can have par variable
to check for cycle in that component.
the above thing will work for both dfs and bfs
*/

bool undir_bfs(vector<vector<int>> &graph, vector<int> &vis, int node) {
    queue<pair<int, int>> Q;
    Q.push({node, -1});
    //{node , par_node}
    vis[node] = true;
    while (Q.size()) {
        int n = Q.size();
        while (n--) {
            pair<int, int> p = Q.front();
            Q.pop();
            for (auto &adj_node : graph[p.first]) {
                if (vis[adj_node] and adj_node != p.second) {
                    return true; // cycle found...
                } else if (!vis[adj_node]) {
                    vis[adj_node] = true;
                    Q.push({adj_node, p.first});
                }
            }
        }
    }
    return false; // no cycle found.....
}

bool undir_dfs(vector<vector<int>> &graph, vector<int> &vis, int par_node, int node) {
    vis[node] = true;
    for (int &adj_node : graph[node]) {
        if (vis[adj_node] and adj_node != par_node) {
            return false;
        } else if (!vis[adj_node]) {
            if (undir_dfs(graph, vis, node, adj_node)) {
                return true;
            }
        }
    }
    return false;
}

bool cycle_detection_undirected(int n, vector<vector<int>> &graph) {
    vector<int> vis(n, 0);
    bool dfs(false), bfs(false);
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            if (undir_dfs(graph, vis, -1, i)) {
                dfs = true;
                vis[i] = 0;
                break;
            }
        }
        vis[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            if (undir_bfs(graph, vis, i)) {
                bfs = true;
                break;
            }
        }
    }
    return (bfs & dfs);
}

/***cylce detection in directed graph***/

/*dfs
we need to have to_vis array for keeping track of all nodes of whole graph so that
we can ensure we are visiting every component for cycle detection.
for each component we need one vis array for detecting cycle in that component.
*/

bool dir_dfs(vector<vector<int>> &graph, int node, vector<int> &vis, vector<int> &to_vis) {
    vis[node] = 1;
    to_vis[node] = 1;
    // if(to_vis[node]) return;*******will we important in cyclic cases to avoid tle!!**********
    for (auto &adj_node : graph[node]) {
        if (vis[adj_node]) {
            return true;
        } else {
            if (dir_dfs(graph, adj_node, vis, to_vis)) {
                return true;
            }
        }
    }
    vis[node] = 0;
    return false;
}

/*bfs
we use here kahn's algorithm which is nothing but topological sorting by bfs.
*/
bool dir_bfs(vector<vector<int>> &graph, int n) {
    int indegree[n];
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
    /*
    every time we are pushing 0 indegree node to queue Q...
    in cyclic case for eg: a->b->c->a there indegree will never be zero
    and hence never pushed in queue(never visited) and if after doing bfs
    if still there are nodes which are unvisited we say there is some cycle.
    */
    int nodes_vis = 0;
    while (Q.size()) {
        int n = Q.size();
        while (n--) {
            int i = Q.front();
            Q.pop();
            nodes_vis++;
            for (int j : graph[i]) {
                indegree[j]--;
                if (!indegree[j]) {
                    Q.push(j);
                }
            }
        }
    }
    if (nodes_vis == n) {
        // there is no cycle in graph
        return false;
    }
    return true;
}

bool cycle_detection_directed(int n, vector<vector<int>> &graph) {
    vector<int> vis(n, 0), to_vis(n, 0);
    bool dfs(false), bfs(false);
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            if (dir_dfs(graph, i, vis, to_vis)) {
                dfs = true;
                vis[i] = 0;
                break;
            }
        }
        vis[i] = 0;
    }
    bfs = dir_bfs(graph, n);
    return (bfs | dfs);
}

int main() {
    vector<vector<int>> undir_graph = build_graph(6, {{0, 1}, {1, 2}, {3, 4}, {4, 5}, {3, 5}}, 1);
    vector<vector<int>> dir_graph = build_graph(6, {{1, 0}, {5, 1}, {2, 3}, {3, 4}, {4, 2}}, 0);

    bool yes = cycle_detection_undirected(6, undir_graph);
    cout << "UNDIRECTED GRAPH" << endl;
    if (yes)
        cout << "yes cycle exists" << endl;
    else
        cout << "no cycle do not exists" << endl;

    cout << "DIRECTED GRAPH" << endl;
    yes = cycle_detection_directed(6, dir_graph);
    if (yes)
        cout << "yes cycle exists" << endl;
    else
        cout << "no cycle do not exists" << endl;
}