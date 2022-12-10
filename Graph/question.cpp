#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
    vector<vector<int>> graph;
    string color;
    set<string> paths;
    vector<bool> vis;
    Graph(vector<vector<int>> &edges, string &col, int N) {
        graph.resize(N);
        for (vector<int> e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }
        color = col;
        vis.resize(N, 0);
    }
};

class Solution {
public:
    void dfs(Graph &g, set<char> st, queue<char> q, int node) {
        g.vis[node] = true;
        if (!st.count(g.color[node])) {
            q.push(g.color[node]);
            st.insert(g.color[node]);
            string t = "";
            for (auto i : st)
                t += i;
            if (q.size() == 3) {
                g.paths.insert(t);
                st.erase(q.front());
                q.pop();
            }
        }
        for (auto a : g.graph[node]) {
            if (!g.vis[a]) {
                dfs(g, st, q, a);
            }
        }
    }

    vector<string> solve(int N, int M, int Q, string col, vector<vector<int>> &edges, vector<string> &query) {
        Graph g(edges, col, N);
        set<char> st;
        queue<char> q;
        for (int i = 0; i < N; i++) {
            if (!g.vis[i]) {
                dfs(g, st, q, i);
            }
        }
        for (string s : g.paths) {
            cout << s << endl;
        }
        vector<string> res(Q);
        string y = "YES", n = "NO";
        for (int i = 0; i < Q; i++) {
            sort(query[i].begin(), query[i].end());
            cout << query[i] << endl;
            if (g.paths.count(query[i])) {
                res[i] = y;
            } else {
                res[i] = n;
            }
        }
        return res;
    }
};

int main() {
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {1, 2}, {2, 4}, {4, 5}};
    vector<string> query = {"abc", "aec", "azc"};
    string col = "abdebc";
    Solution s;
    vector<string> ans = s.solve(6, 7, 3, col, edges, query);
}