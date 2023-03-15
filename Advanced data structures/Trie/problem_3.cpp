#include <bits/stdc++.h>
using namespace std;

/**
 * Problem statement:
 * we are given 2 arrays arr1, arr2
 * we need to find max(arr1[i]^arr2[j]) i.e
 * take 1 element from arr1 and 1 element from arr2, such that
 * xor of the 2 elements is maximum.
 */

/**
 * approach 1:
 * apply brute force.
 * for every element in arr1, try out all elements from arr2 such
 * that doing xor of both is maximum as u doing it for every element
 * find out maximum of all.
 * but time complexity in this case O(n^2)
 *
 * we could do better than this time complexity.
 *
 * approch 2:
 * for understanding the approach better
 * we need to understand the intution behind it.
 * intution....
 * suppose we have binary number : 0 1 0 1
 * we should xor with a number such that xor is max
 * if we set the leftmost bit then it is larger than changing
 * a 0 to 1 on the right hand side. As we know val is calculated
 * such it depends upon index cur_i_val = 2^i + pre_i_val,
 * and 2^i is always greater than pre_i_val(i is 0 indexed from the left
 * of binary form)
 * so now we need to figure out a way of setting out right values
 * to 1 as many as possible
 *
 * here we use trie for storing binary form of number.
 *
 */

struct TrieNode {
    TrieNode *links[2];

    TrieNode *next_node(int bit) {
        return links[bit];
    }

    void create_new_link(int bit, TrieNode *node) {
        links[bit] = node;
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

    int num(int n) {
        TrieNode *node = root;
        int mx = 0;
        for (int i = 31; i >= 0; i--) {
            int bit = (n >> i) & 1;
            if (node->next_node(!bit) == NULL) {
                node = node->next_node(bit);
            } else {
                mx += pow(2, i);
                node = node->next_node(!bit);
            }
        }
        return mx;
    }
};

class solution {
public:
    int max_xor(int arr1[], int arr2[], int m, int n) {
        Trie t;
        for (int i = 0; i < m; i++) {
            t.insert(arr1[i]);
        }
        int mx = 0;
        for (int j = 0; j < n; j++) {
            mx = max(mx, t.num(arr2[j]));
        }
        return mx;
    }
};

int main() {
    int arr1[] = {6, 6, 0, 6, 8, 5, 6}, arr2[] = {1, 7, 1, 7, 8, 0, 2};
    solution s;
    cout << s.max_xor(arr1, arr2, 7, 7);
}