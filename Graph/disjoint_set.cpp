#include <bits/stdc++.h>
using namespace std;

int par[1000];
int rnk[1000];

void setDSU(int N) {
    for (int i = 0; i <= N; i++) {
        par[i] = i;
        rnk[i] = 0;
    }
}

int findPar(int u) {
    if (par[u] == u) {
        return u;
    }
    return par[u] = findPar(par[u]);
}

void doUnion(int u, int v) {
    if (rnk[u] > rnk[v]) {
        par[v] = u;
    } else if (rnk[v] > rnk[u]) {
        par[u] = v;
    } else {
        par[u] = v;
        rnk[v]++;
    }
}