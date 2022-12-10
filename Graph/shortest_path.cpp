#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;

/*
for both directed and undirected graph we use dijkstra's algorithm.
it just don't work for negative weighted cycle..
*/
void apply_dijkstra(vector<vector<pi>> &graph, int src, vector<int> &dis) {
    priority_queue<pi, vector<pi>, greater<pi>> pq;
    pq.push({0, src});
    dis[src] = 0;
    while (pq.size()) {
        pair<int, int> p = pq.top();
        pq.pop();
        if (p.first == INT_MAX) {
            continue;
        }
        for (auto a : graph[p.second]) {
            if (dis[a.first] > dis[p.second] + a.second) {
                dis[a.first] = dis[p.second] + a.second;
                pq.push({dis[a.first], a.first});
            }
        }
    }
}

void shortest_path(vector<vector<pi>> &graph, int n) {
    vector<int> dis(n, INT32_MAX);
    apply_dijkstra(graph, 0, dis);
    return;
}

int main() {
    return 0;
}