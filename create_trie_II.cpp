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

    bool search(string word) {
        return searchHelper(root, word, 0);
    }
};

class wordMaker {
    Trie* root;

    void inserting(Trie* node, string &word, int it) {
        if(it == word.length()) {
            node->isTerminal = 1;
            return;
        }
        int index = word[it] - 'a';
        if(!node->child[index])
            node->child[index] = new Trie(word[it]);

        inserting(node->child[index], word, it+1);
    }

    bool searching(Trie* node, string &word, int it) {
        if(it == word.size())
            return node->isTerminal;

        int index = word[it] - 'a';
        if(node->child[index])
            return searching(node->child[index], word, it+1);

        return false;
    }

    bool utilityFun(Trie* node, string &prefix, int it) {
        if(it == prefix.size())
            return true;
        int index = prefix[it] - 'a';
        if(node->child[index])
            return utilityFun(node->child[index], prefix, it+1);
        return false;
    }
    
public:
    wordMaker() {
        root = new Trie('$');
    }
    
    void insert(string word) {
        inserting(root, word, 0);
    }
    
    bool search(string word) {
        return searching(root, word, 0);
    }
    
    bool startsWith(string prefix) {
        return utilityFun(root, prefix, 0);
    }
};

int main() {

    // method 1:
    WordDictionary obj;
    obj.addWord("ichigo");
    if(obj.search("ichigo"))
        cout << "true" << endl;
    else
        cout << "false" << endl;

    // method 2:
    wordMaker inst;
    string str_I, str_II;
    cout << "give a name : ";
    cin >> str_I;
    cout << "give a name you want to check : ";
    cin >> str_II;
    inst.insert(str_I);
    if(inst.search(str_II))
        cout << "this name exists" << endl;
    else 
        cout << "this is the first time I've seen this name" << endl;
    string prefix;
    cout << "provide prefix related to your given name : ";
    cin >> prefix;
    if(inst.startsWith(prefix))
        cout << "yes the instance of this prefix exists" << endl;
    else 
        cout << "no there is no such instance of this prefix" << endl;

    return 0;
}