#include <bits/stdc++.h>
using namespace std;

/**
 * problem statement:
 * we are given an array we need to find maximum xor of 2 elements from the array.
 * 0<=i<=j<n(i and j are indices of the 2 elements).
 * i==j is also valid.
 *
 * brute force approach is simple
 * for each element find the other element(linear traversal) resulting maximum xor.
 *
 * intution for other approach:
 * if num represented in binary form it is all zeroes and ones
 * and value is calculated as cur_bit*(2^i + pre_val)
 * and every time 2^i > pre_cal
 * so if we set left most bit, it is always greater than setting up right bits.
 * so for every element we try to find an element which sets the left bits giving
 * max xor, but it will also take quadratic time so to improve it we will use tries
 * to implement this approach.
 **/

/**
 * to check ith bit is set or not....
 * bit = (n>>i) & 1;
 **/
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
    int findMaximumXOR(vector<int> &nums) {
        Trie t;
        for (int n : nums) {
            t.insert(n);
        }
        int max_xor = 0;
        for (int n : nums) {
            int x = t.max_xor_possible(n);
            max_xor = max(max_xor, x);
        }
        return max_xor;
    }
};