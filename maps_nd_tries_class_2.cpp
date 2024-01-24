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

// insertion in trie through recursion (T.C => O(length of string))
void insertion(Trie* root, string word) {
    // base case
    if(word.length() == 0) {
        root->isTerminal = 1;
        return;
    }
    /*here we're capturing each character of given string ans
    insert the character into trie*/
    char ch = word[0];
    int index = ch - 'a';
    Trie* child;
    if(root->child[index]) {
        /*if the character is already presented in the trie
        so we just have to conncect it with current child node*/
        child = root->child[index];
    }
    else {
        /*if the character is new and isn't presented in trie
        so we just have to create a new child node ans 
        assign the character to it and conncect it with current node*/
        child = new Trie(ch);
        root->child[index] = child;
    }
    // recursive call
    insertion(child, word.substr(1));
}

// performing searching in trie (T.C => O(length of string))
bool search_word(Trie* root, string word) {
    // base case
    if(word.length() == 0) {
        /*if the last character of the word/string
        is marked as (true) so it means that the given
        word/string is presented in the trie*/
       return root->isTerminal;
    }   
    char ch = word[0];
    int index = ch - 'a';
    Trie* child;
    if(root->child[index])
        child = root->child[index];
    else 
        return false;
    // recursive call
    bool final_ans = search_word(child, word.substr(1));
    return final_ans;
}

// deletion in trie also with recursion (T.C => O(length of string))
void deletion(Trie* root, string word) {
    // base case
    if(word.length() == 0) {
        /*here we're marking the last char of given 
        string as false, so that the track of the
        whole word/string is lost in trie*/
        root->isTerminal = false;
        return;
    }
    char ch = word[0];
    int index = ch - 'a';
    Trie* child;
    if(root->child[index])
        child = root->child[index];
    else 
        return;
    // recursive call
    deletion(child, word.substr(1));
}

int main() {

    // creation of root node
    Trie* root = new Trie('$');
    insertion(root, "luffy");
    insertion(root, "zoro");
    insertion(root, "sanji");
    insertion(root, "robin");
    insertion(root, "nami");
    insertion(root, "jinbei");

    // searching words/string in trie
    string str;
    cout << "enter the name of your character : ";
    getline(cin, str);
    if(search_word(root, str))
        cout << "character found" << endl;
    else 
        cout << "character not found" << endl;

    // deletion of words/string in trie
    string del;
    cout << "enter the name of character your want to delete : ";
    getline(cin, del);
    deletion(root, del);
    // here we're checking if the word we deleted above is actually deleted form trie
    string str_II;
    cout << "enter the name of your character : ";
    getline(cin, str_II);
    if(search_word(root, str_II))
        cout << "character found" << endl;
    else 
        cout << "character not found" << endl;

    return 0;
}