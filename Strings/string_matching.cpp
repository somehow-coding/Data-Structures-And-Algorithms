#include <bits/stdc++.h>
using namespace std;

#define ll long long

/**
 * KMP String Matching Algorithm.
 *
 * Building lps
 */

vector<int> constructLPS(string &s) {
    int n(s.size());

    vector<int> lps(n, 0);

    for (int i = 1, len = 0; i < n;) {
        if (s[i] == s[len]) {
            lps[i++] = ++len;
        } else if (len) {
            len = lps[len - 1];
        } else {
            lps[i++] = 0;
        }
    }

    return lps;
}

int findFirstMatch(string &text, string &pat) {
    vector<int> lps = constructLPS(pat);

    int i(0), j(0), m(text.size()), n(pat.size());

    while (i < m) {
        if (text[i] == pat[j]) {
            i++, j++;
        }
        else {
            if (j) j = lps[j - 1];
            else i++;
        }
        if (j == n) {
            return i - n;
        }
    }
    return -1;

}

/***
 * Rabin Karp Algorithm (concept of rolling hash)
 *
 * chance of collision with probability of mod\
 *
 * s is text and t is pattern
 *
 * p is some prime number close to equal of no of characters.
 */

vector<int> rabinKarp(string &str, string &text) {
    // consider only if m >= n

    ll prime = 31, mod = 1e9 + 9, m = str.size(), n = text.size();

    // precomputation of power

    vector<ll> p_pow(n, 1);
    for (int i = 1; i < n; i++) {
        p_pow[i] = (p_pow[i - 1] * prime) % mod;
    }

    vector<ll> hash(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        hash[i] = (hash[i - 1] + (text[i - 1] - 'a') * p_pow[i - 1]) % mod;
    }

    ll h_s = 0;
    for (int i = 0; i < m; i++) {
        h_s = (h_s + (str[i] - 'a') * p_pow[i]) % mod;
    }

    vector<int> match;
    for (int i = 0; i + m - 1 < n; i++) {
        ll h_t = (hash[i + m] + mod - hash[i]) % mod;
        if (h_t == (h_s * p_pow[i]) % mod) {
            match.push_back(i);
        }
    }

    return match;
}
