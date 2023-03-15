#include <bits/stdc++.h>
using namespace std;

/**
 * problem statement:
 * You are given an array of strings products and a string searchWord.
 * Design a system that suggests at most three product names from products
 * after each character of searchWord is typed. Suggested products should have
 * common prefix with searchWord. If there are more than three products with
 * a common prefix return the three lexicographically minimums products.
 * Return a list of lists of the suggested products after each character of searchWord is typed.
 */

/**
 * basic appraoch is simple:
 * maintaining a substring s storing every character of searchWord during traversal.
 * and then checking products which matches with s finding out at most three
 * lexicographically minimums products.
 * but this is not time efficient.
 */

// code for above approach
// class Solution {
// public:
//     bool matchesPrefix(string &p, string &s) {
//         if (size(s) < size(p))
//             return false;
//         int i = 0, j = 0;
//         while (i < size(s) and j < size(p)) {
//             if (s[i] != p[j]) {
//                 return false;
//             }
//             i++, j++;
//         }
//         return true;
//     }

//     vector<vector<string>> suggestedProducts(vector<string> &products, string searchWord) {
//         string pre = "";
//         vector<vector<string>> ret(searchWord.size());
//         for (int i = 0; i < size(searchWord); i++) {
//             pre += searchWord[i];
//             set<string> st;
//             for (int j = 0; j < size(products); j++) {
//                 if (matchesPrefix(pre, products[j])) {
//                     st.insert(products[j]);
//                     if (st.size() > 3)
//                         st.erase(--st.end());
//                 }
//             }
//             for (auto &s : st) {
//                 ret[i].push_back(s);
//             }
//         }
//         return ret;
//     }
// };

// using tries for more time efficient solution

struct TrieNode {
    TrieNode *links[26];
    bool flag = false;

    void create_new_link(char c, TrieNode *node) {
        links[c - 'a'] = node;
    }

    TrieNode *next_node(char c) {
        return links[c - 'a'];
    }
};

class Trie {
public:
    TrieNode *root;
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode *node = root;
        for (char c : word) {
            if (node->next_node(c) == NULL) {
                // create link
                node->create_new_link(c, new TrieNode());
            }
            node = node->next_node(c);
        }
        node->flag = true;
    }

    void complete_list(TrieNode *node, vector<string> &str, string &s) {
        if (node->flag == true) {
            str.push_back(s);
        }
        for (char c = 'a'; c <= 'z'; c++) {
            if (str.size() == 3) {
                return;
            }

            if (node->next_node(c) != NULL) {
                s.push_back(c);
                complete_list(node->next_node(c), str, s);
                s.pop_back();
            }
        }
    }

    vector<string> list_of_products(string &word) {
        vector<string> str;
        TrieNode *node = root;
        for (int i = 0; i < word.size(); i++) {
            char c = word[i];
            if (node->next_node(c) == NULL) {
                return str;
            }
            if (i == word.size() and node->flag == true) {
                str.push_back(word);
            }
            node = node->next_node(c);
        }
        complete_list(node, str, word);
        return str;
    }
};

class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string> &products, string searchWord) {
        Trie T;
        for (string &pro : products) {
            T.insert(pro);
        }
        string pre = "";
        vector<vector<string>> ret;
        for (int i = 0; i < searchWord.size(); i++) {
            pre += searchWord[i];
            ret.push_back(T.list_of_products(pre));
        }
        return ret;
    }
};