#include <bits/stdc++.h>
using namespace std;

/**
 * We are implementing trie.
 * We will implement many functionalities.
 */

/**
 * TrieNode is a struct which is a node of trie.
 */
struct TrieNode {
    TrieNode *links[26];
    bool flag = false;
    int cnt_word = 0;
    int cnt_prefix = 0;

    // create new link will create a link between current node and next node of character c
    void create_new_link(char c, TrieNode *node) {
        links[c - 'a'] = node;
    }
    // next link will provide next char(link) which is by default null if that
    // char is not there else will give link to the node having that character c.
    TrieNode *next_link(char c) {
        return links[c - 'a'];
    }

    // return whether upto this node we have completed a word or not.
    bool is_word() {
        return flag;
    }
    // this will set flag which means that we have completed a word here.
    // we increase word cnt here.
    bool set_word() {
        flag = true;
        cnt_word++;
    }
    // increase the cnt of prefix.
    bool set_prefix() {
        cnt_prefix++;
    }

    void unset_word() {
        cnt_word--;
    }

    void unset_prefix() {
        cnt_prefix--;
    }
};

/**
 * This is a class Trie.
 */

class Trie {
public:
    // root node
    TrieNode *root;
    Trie() {
        // intialisng root node
        root = new TrieNode();
    }
    /**
     * This is insert function:
     * Here we are given a word which we need to insert into the trie.
     * Node pointing to root node at first.
     * Then we start traversing the given word character by character.
     * In case current node do not have the link to the character(if condition to check),
     * we create a new node and linking them both.
     * After, completion of traversal we set word(flag = true) for current node
     * implicating that we have completed the word, so that if we have to check a word
     * is present or not in the trie we can check later on.
     * for cnt purpose we also increase the word cnt using set function.
     * and also increment the prefix count using set_prefix function.
     */
    void insert(string word) {
        TrieNode *node = root;
        for (char c : word) {
            if (node->next_link(c) == NULL) {
                TrieNode *newNode = new TrieNode();
                node->create_new_link(c, newNode);
            }
            node->set_prefix();
            node = node->next_link(c);
        }
        node->set_word();
    }
    /**
     * This is a search function(searching a word):
     * Here we also traverse the word as we did in insert function
     * the only difference if we did not found the link to char we
     * return false as the word is not present and at the end of traversal
     * we also check if the word is set or not(flag == true)
     */
    bool word_is_present(string word) {
        TrieNode *node = root;
        for (char c : word) {
            if (node->next_link(c) == NULL) {
                return false;
            }
            node = node->next_link(c);
        }
        if (node->is_word()) {
            return true;
        }
        return false;
    }

    /**
     * Same as word_is_present the only thing we need to check whether word is set
     * or not bcz we here are searching for prefix not word.
     */
    bool prefix_is_present(string word) {
        TrieNode *node = root;
        for (char c : word) {
            if (node->next_link(c) == NULL) {
                return false;
            }
            node = node->next_link(c);
        }
        return true;
    }

    int cnt_of_prefix_present(string word) {
        TrieNode *node = root;
        for (char c : word) {
            if (node->next_link(c) == NULL) {
                return 0;
            }
            node = node->next_link(c);
        }
        return node->cnt_prefix;
    }

    int cnt_of_word_present(string word) {
        TrieNode *node = root;
        for (char c : word) {
            if (node->next_link(c) == NULL) {
                return 0;
            }
            node = node->next_link(c);
        }
        return node->cnt_word;
    }
    /**
     * In erase function first we are checking that word is present or not
     * if it is not present it makes no sense to erase it
     * if it is present, although we will not delete the nodes but
     * decrease prefix count while doing traversal and also decrement word
     * count at the end of the traversal.
     */
    void erase(string word) {
        if (word_is_present(word) == false) {
            return;
        }
        TrieNode *node = root;
        for (char c : word) {
            node->unset_prefix();
            node = node->next_link(c);
        }
        node->unset_word();
    }
};

/**Complexities:
 * time complexity for inserting, searching, erase, cnt:
 * O(l) -> l : avg length of keys
 * space complexity
 * O(l * n) -> n : no of key
 */

/*optimising searching of words(strings)->we can use tries*/