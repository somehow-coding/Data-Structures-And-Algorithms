#include "trie.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    Trie t;
    string s[] = {"abacus", "mine", "my", "awake", "my"};
    for (int i = 0; i < 5; i++) {
        t.insert(s[i]);
    }
    string w[] = {"aba", "m", "mine", "my", "awake"};
    // prefix count and word count.
    for (int i = 0; i < 5; i++) {
        cout << t.cnt_of_prefix_present(w[i]) << " " << t.cnt_of_word_present(w[i]) << endl;
    }
    // erase.
    t.erase("m");
    t.erase("awake");
    for (int i = 0; i < 5; i++) {
        cout << t.cnt_of_prefix_present(w[i]) << " " << t.cnt_of_word_present(w[i]) << endl;
    }
}