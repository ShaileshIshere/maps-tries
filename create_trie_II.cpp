#include <bits/stdc++.h>

using namespace std;

struct Trie {
    char value;
    Trie* child[26];
    bool isTerminal;
    Trie(char data) : value(data), isTerminal(false) {
        for (int i = 0; i < 26; ++i)
            child[i] = nullptr;
    }
};

class WordDictionary {
    Trie* root;

public:
    WordDictionary() {
        root = new Trie('$');
    }

    void addWord(string word) {
        Trie* node = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (!node->child[index]) 
                node->child[index] = new Trie(ch);
            node = node->child[index];
        }
        node->isTerminal = true;
    }

    bool searchHelper(Trie* root, string word, int index) {
        if (index == word.length()) 
            return root->isTerminal;
        char ch = word[index];
        int childIndex = ch - 'a';
        if (root->child[childIndex])
            return searchHelper(root->child[childIndex], word, index+1);
        else
            return false;
    }

    bool search(string word) {
        return searchHelper(root, word, 0);
    }
};

int main() {
    WordDictionary obj;
    obj.addWord("ichigo");
    if(obj.search("ichigo"))
        cout << "true" << endl;
    else
        cout << "false" << endl;

    return 0;
}