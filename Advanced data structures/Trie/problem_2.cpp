#include "trie.h"
#include <bits/stdc++.h>
using namespace std;

/**
 * Problem statement:
 * we are given a string we need to count no of distinct substrings in it
 *
 * intial approach:
 * we insert every substring in set and return set size
 * as set will only store unique substring.
 * time complexity:
 * o(n^2 * log(m)) n is size of string and m is no of distinct substrings
 * worst case possible m = close to n^2
 * space complexity:
 * O(m * len) len is avg length of substring
 * sc close to O(n^3){m -> n^2, len -> n/2}
 *
 * trie approach:
 * tc : O(n^2 * avg len of substring)
 * sc : O(m * avg len of substring) but it is certainly more optimal than use of set.
 */

class solution {
public:
    int count_distinct_substrings(string str) {
        int n = str.size();
        int cnt = 1; // if empty substring to be counted.

        Trie t;
        for (int i = 0; i < n; i++) {
            string s = "";
            for (int j = i; j < n; j++) {
                s += str[j];
                if (t.word_is_present(s) == false) {
                    t.insert(s);
                    cnt++;
                }
            }
        }
        return cnt;
    }
};

int main() {
    solution s1;
    cout << s1.count_distinct_substrings("abab") << endl;
}