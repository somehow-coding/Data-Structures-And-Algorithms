#include "trie.h"
#include <bits/stdc++.h>
using namespace std;

/**
 * problem statement:
 * we are given a array of string we need to find longest complete string which obeys given conditions.
 * conditions:
 * array should contain all prefixes of string.
 * string should be as much as longest possible.
 * for equal length return lexographically smallest.
 */

/**
 * initial approach:
 * store all strings in map or set
 * and then check for every string that it is complete or not
 * time complexity for the approach
 * n*log(n) + n * l * log(n)
 * space complexity:
 * n * l
 */

/**
 * We can more optimise the code using trie.
 * we can reduce both the complexities.
 */

class solution {
public:
    string complete_string(string arr[], int n) {
        Trie t;
        for (int i = 0; i < n; i++) {
            t.insert(arr[i]);
        }
        string res = "";
        for (int i = 0; i < n; i++) {
            string s = "";
            for (int j = 0; j < arr[i].size(); j++) {
                if (j == arr[i].size() - 1) {
                    if (res.size() == arr[i].size() and arr[i] < res) {
                        res = arr[i];
                    } else if (res.size() < arr[i].size()) {
                        res = arr[i];
                    }
                }
                s += arr[i][j];
                if (t.word_is_present(s) == false) {
                    break;
                }
            }
        }
        return res.size() ? res : "no such string found";
    }
};

int main() {
    string arr1[] = {"ni", "n", "nin", "a", "ab", "abc"};
    solution sol1;
    cout << sol1.complete_string(arr1, 6) << endl;
    string arr2[] = {"abc", "ab"};
    solution sol2;
    cout << sol2.complete_string(arr2, 2) << endl;
}