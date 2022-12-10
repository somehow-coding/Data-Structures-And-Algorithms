#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
    vector<vector<int>> graph;
    vector<int> visNodes;
    vector<int> vis;
    vector<int> arr;
    vector<int> indegree;
    Graph(vector<vector<int>> &edges, int N) {
        graph.resize(N);
        vis.resize(N, 0);
        indegree.resize(N, 0);
        visNodes.resize(N, 0);
        for (vector<int> edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            indegree[edge[1]]++;
        }
    }
};

vector<int> topoLogicalSort(Graph &g, int N) {
    queue<int> q;
    for (int i = 0; i < N; i++) {
        if (!g.indegree[i]) {
            q.push(i);
        }
    }

    while (q.size()) {
        int t = q.size();
        while (t--) {
            int i = q.front();
            q.pop();
            for (int j : g.graph[i]) {
                g.indegree[j]--;
                if (!g.indegree[j]) {
                    q.push(j);
                }
            }
        }
    }
    reverse(begin(g.arr), end(g.arr));
    if (g.arr.size() == N) {
        return g.arr;
    }
    return {};
}

class Solution {
public:
    bool dfs(Graph &g, int i) {
        if (g.vis[i]) {
            return true;
        }
        if (g.visNodes[i]) {
            return false;
        }
        g.vis[i] = 1;
        g.visNodes[i] = 1;
        for (int j : g.graph[i]) {
            if (dfs(g, j)) {
                return true;
            }
        }
        g.arr.push_back(i);
        g.vis[i] = 0;
        return false;
    }

    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
        Graph g(prerequisites, numCourses);

        // dfs
        //  for(int i=0; i<numCourses; i++){
        //      if(!g.visNodes[i]){
        //          if(dfs(g,i)){
        //              return {};
        //          }
        //      }
        //  }

        // bfs
        return topoLogicalSort(g, numCourses);
    }
};