#include <bits/stdc++.h>
using namespace std;

/**
 * we are given the given in form of matrix
 * if(mat[i][j]==-1) there is no edge from i to j
 * else mat[i][j] = weight of the edge from i to j
 * considering no self edge
 * can handle the negative weight edge cycle.
 * tc = O(n^3)
 */

void all_shortest_distance(vector<vector<int>> &matrix) {
    int n(matrix.size());

    for (int i(0); i < n; i++) {
        for (int j(0); j < n; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            }
            if (matrix[i][j] == -1) {
                matrix[i][j] = 1e9 + 7;
            }
        }
    }
    for (int k(0); k < n; k++) {
        for (int i(0); i < n; i++) {
            for (int j(0); j < n; j++) {
                matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }
    }
    // to check if there is a negative weight edge cycle
    for (int i(0); i<n;i++) {
        if (matrix[i][i] < 0) {
            //there is neg wt cycle
        }
    }
}