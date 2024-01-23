#include<bits/stdc++.h>

using namespace std;

// Node creation in tries
struct Trie {
    char value;
    Trie* child[26];
    bool isTerminal;
    Trie(char val) : value(val), isTerminal(0) {
        for(int i=0; i<26; ++i)
            child[i] = 0;
    }
};
// insertion in trie through recursion
void insertion(Trie* root, string word) {
    // base case
    if(word.length() == 0) {
        root->isTerminal = 1;
        return;
    }
    char ch = word[0];
    int index = ch - 'a';
    Trie* child;
    if(root->child[index]) {
        // present
        child = root->child[index];
    }
    else {
        // absent
        child = new Trie(ch);
        root->child[index] = child;
    }
    // recursion
    insertion(child, word.substr(1));
}
// performing searching in trie
bool search_word(Trie* root, string word) {
    // base case
    if(word.length() == 0)
        return root->isTerminal;
    char ch = word[0];
    int index = ch - 'a';
    Trie* child;
    if(root->child[index])
        child = root->child[index];
    else 
        return false;
    // recursion
    bool final_ans = search_word(child, word.substr(1));
    return final_ans;
}

int main() {

    // creation of root node
    Trie* root = new Trie('$');
    insertion(root, "ichibe hyosube");
    insertion(root, "kenpachi zaraki");
    insertion(root, "unohana retsu");
    insertion(root, "kyoraku shunsui");
    insertion(root, "hirako shinji");
    insertion(root, "kuchiki byakuya");
    insertion(root, "urahara kisuke");
    // searching elements in trie
    string str;
    cout << "enter the name of your character : ";
    getline(cin, str);
    if(search_word(root, str))
        cout << "character found" << endl;
    else 
        cout << "character not found" << endl;

    return 0;
}