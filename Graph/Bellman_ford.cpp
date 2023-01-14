#include <bits/stdc++.h>
using namespace std;

/***
 * Bellman ford algo is useful when we have negative weight cycle 
 * as dijkstra will fail if there is cycle.
 * 
 * single source shortest path algorithm.
 * 
 * **********work for negative weight cycles***************
 * 
 * approach: perform relaxation n-1 times (n is no of nodes in graph) to all edges sequentially
 * why n-1 times? -> as every time there will be a node which is relaxed and
 * after n-1 iterations we will be able to find the shortest path to every node.
 * some good exp for the n-1 times:
 * since in a graph of n nodes in worst case you will take n-1 edges to reach from the first
 * to last node thereby we iterate for n-1 iterations.
 * 
 * perform nth iteration to check for the cycle if there is a node which can be relaxed even 
 * after all n-1 iteration then there is cycle.
 * 
 * tc : E*V
*/

vector<int> bellman_ford(int n, vector<vector<int>> &edges, int src) {
    vector<int> dis(n, 1e9);
    dis[src] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (auto &edge : edges) {
            int u = edge[0], v = edge[1], wt = edge[2];
            if (dis[u] != 1e9 and dis[u] + wt < dis[v]) {
                dis[v] = dis[u] + wt;
            }
        }
    }

    //nth iteration to check for cycle. 
    for (auto &edge : edges) {
        int u = edge[0], v = edge[1], wt = edge[2];
        if (dis[u] != 1e9 and dis[u] + wt < dis[v]) {
            //there exists a cycle.
            return {-1};
        }
    }
    return dis;
}