#include<bits/stdc++.h>

using namespace std;

// replace words
struct TrieNode{
    char data;
    bool isTerminal;
    TrieNode* child[26];
    TrieNode(char val) : data(val), isTerminal(0) {
        for(int i=0; i<26; ++i)
            child[i] = 0;
    }
};
class Trie {
    TrieNode* root;

    void inserting(TrieNode* node, string &word, int it) {
        if(it == word.length()) {
            node->isTerminal = 1;
            return;
        }
        int index = word[it] - 'a';
        if(!node->child[index])
            node->child[index] = new TrieNode(word[it]);

        inserting(node->child[index], word, it+1);
    }

    bool searching(TrieNode* node, string &word, int &it) {
        if(node->isTerminal)
            return true;
        if(it == word.size())
            return node->isTerminal;

        int index = word[it++] - 'a';
        if(node->child[index])
            return searching(node->child[index], word, it);

        return false;
    }
    
public:
    Trie() {
        root = new TrieNode('$');
    }
    
    void insert(string word) {
        inserting(root, word, 0);
    }
    
    int search(string word) {
        int i=0;
        bool gotIt = searching(root, word, i);
        return gotIt ? i : -1;
    }
};
string replaceWords(vector<string>& dictionary, string sentence) {
    string ans;
    Trie node;
    for (auto root : dictionary)
        node.insert(root);

    int start = 0, end = 0;
    while (end < sentence.size()) {
        if (sentence[end] == ' ' || end == sentence.size() - 1) {
            int len = end == sentence.size() - 1 ? sentence.size() : end - start;
            string word = sentence.substr(start, len);
            int trieMatchIndex = node.search(word);
            ans += trieMatchIndex != -1 ? word.substr(0, trieMatchIndex) : word;
            if (sentence[end] == ' ')
                ans += " ";
            start = end + 1;
        }
        ++end;
    }
    return ans;
}

int main() {

    int n;
    cout << "how many words you want to add in your dictionary : ";
    cin >> n;
    vector<string> dictionary(n);
    string words;
    for(int i=0; i<n; ++i)
        cin >> dictionary[i]; 
    string sentence;
    cout << "enter your sentence : ";
    cin.ignore();
    getline(cin, sentence);
    cout << "here is your sentence after replacing words :" << endl << replaceWords(dictionary, sentence) << endl;

    return 0;
}