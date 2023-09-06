#include <bits/stdc++.h>
using namespace std;

#define ll long long

/**
 * Where it can be applied:
 *
 * We need to jump k places from u to v and we need data of those nodes in b/w.
 * We need to process nodes/edges in between from u to v.
 *
 * It works where there is one parent for each node.
 * Only one outgoing edge from every node.
 * Even a cycle can be there but they should adhere to above condition.
 *
 * Intution somewherebehind binary lifting:
 * Jump k places
 * * * K can be represent as sum of 2^i where i = [0, log2(k)] * * *
 * so we will jump in power of 2(i.e every jump step has length as pow(2, i)).
 *
 *
 * Req:
 * Need to create binary lifting table (BLT) and additional data structures
 * depending upon the problem.
 *
 * n is no of nodes and k is the place we need to reach.
 * TC = O(nlogk)
 *
 * **/

/**
 * Example Question:
 *
 * You are given a 0-indexed integer array receiver of length n and an integer k.
 * There are n players having a unique id in the range [0, n - 1] who will play a ball passing game,
 * and receiver[i] is the id of the player who receives passes from the player with id i.
 * Players can pass to themselves, i.e. receiver[i] may be equal to i.
 * You must choose one of the n players as the starting player for the game, and the
 * ball will be passed exactly k times starting from the chosen player.
 * For a chosen starting player having id x, we define a function f(x) that denotes the sum of x and
 * the ids of all players who receive the ball during the k passes, including repetitions.
 * In other words, f(x) = x + receiver[x] + receiver[receiver[x]] + ... + receiver(k)[x].
 * Your task is to choose a starting player having id x that maximizes the value of f(x).
 *
 * Return an integer denoting the maximum value of the function.
 *
 * constraints :
 * 1 <= receiver.length == n <= 10^5
 * 0 <= receiver[i] <= n - 1
 * 1 <= k <= 10^10

*/

// we need to jump at most k and process all the jumps (binary lifting can be used to optimised jumps).
// process jump means u to v jump means all the nodes sum that are in it including u and v.
// have to deal with parent repeating twice u -> v -> w (v will be included twice, have to take care of it).
long long sol(vector<int> &rec, long long k) {
    int n = rec.size();
    vector<vector<ll>> blt(n, vector<ll>(35, -1)), sum(n, vector<ll>(35, 0));
    for (int i = 0; i < n; ++i) {
        blt[i][0] = rec[i];
        sum[i][0] += (i + rec[i]);
    }
    for (int j = 1; j < 35; ++j) {
        for (int i = 0; i < n; ++i) {
            if (blt[i][j - 1] > 0) {
                blt[i][j] = blt[blt[i][j - 1]][j - 1];
                sum[i][j] = sum[blt[i][j - 1]][j - 1] + sum[i][j - 1] - blt[i][j - 1];
            }
        }
    }

    ll res = 0, cur = 0, x = 0, i = 0;
    for (int u = 0; u < n; ++u) {
        cur = 0, i = u, x = 0;
        for (int j = 0; j < 35; ++j) {
            if (k & ((ll)1 << k)) {
                cur += sum[i][j] - x;
                x = i = blt[i][j];
            }
        }
        res = max(res, cur);
    }
    return res;
}

int main() {
}
