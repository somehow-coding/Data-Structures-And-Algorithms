#include <bits/stdc++.h>
using namespace std;

/**
 * problem statement:
 * You are given an array nums consisting of non-negative integers.
 * You are also given a queries array, where queries[i] = [xi, mi].
 * The answer to the ith query is the maximum bitwise XOR value of xi
 * and any element of nums that does not exceed mi. In other words,
 * the answer is max(nums[j] XOR xi) for all j such that nums[j] <= mi.
 * If all elements in nums are larger than mi, then the answer is -1.
 * Return an integer array answer where answer.length == queries.length
 * and answer[i] is the answer to the ith query.
 */

struct TrieNode {
    TrieNode *links[2];

    void create_new_link(int bit, TrieNode *node) {
        links[bit] = node;
    }

    TrieNode *next_node(int bit) {
        return links[bit];
    }
};

class Trie {
public:
    TrieNode *root;

    Trie() {
        root = new TrieNode();
    }

    void insert(int n) {
        TrieNode *node = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (n >> i) & 1;
            if (node->next_node(bit) == NULL) {
                node->create_new_link(bit, new TrieNode());
            }
            node = node->next_node(bit);
        }
    }

    int max_xor_possible(int n) {
        TrieNode *node = root;
        int maxx = 0;
        for (int i = 31; i >= 0; i--) {
            int bit = (n >> i) & 1;
            if (node->next_node(!bit) == NULL) {
                // we can't do anything here
                node = node->next_node(bit);
            } else {
                maxx += pow(2, i);
                node = node->next_node(!bit);
            }
        }
        return maxx;
    }
};

class Solution {
public:
    int bs(vector<int> &nums, int x) {
        int i(0), j(nums.size() - 1), m(0), r(-1);
        while (i <= j) {
            m = (i + j) >> 1;
            if (nums[m] <= x) {
                r = m;
                i = m + 1;
            } else {
                j = m - 1;
            }
        }
        return r;
    }

    static bool cmp(vector<int> &a, vector<int> &b) {
        if (a[2] == -1) {
            return false;
        }
        if (b[2] == -1) {
            return true;
        }
        return a[2] < b[2];
    }

    vector<int> maximizeXor(vector<int> &nums, vector<vector<int>> &queries) {
        sort(begin(nums), end(nums));

        for (int i = 0; i < queries.size(); i++) {
            queries[i].push_back(bs(nums, queries[i][1]));
            queries[i].push_back(i);
        }

        sort(begin(queries), end(queries), cmp);
        int idx = 0;
        Trie t;
        vector<int> ret(queries.size());
        for (int i = 0; i < queries.size(); i++) {
            int n = queries[i][0], j = queries[i][2];
            if (j == -1) {
                ret[queries[i][3]] = -1;
                continue;
            }
            if (j >= idx) {
                for (int k = idx; k <= j; k++) {
                    t.insert(nums[k]);
                }
                idx = j + 1;
            }
            ret[queries[i][3]] = t.max_xor_possible(n);
        }
        return ret;
    }
};