#include<bits/stdc++.h>

using namespace std;

struct Trie {
    char value;
    Trie* child[26];
    bool isTerminal;
    Trie(char data) : value(data), isTerminal(0) {
        for(int i=0; i<26; ++i)
            child[i] = 0;
    }
};
void insertion(Trie* root, string word) {
    if(word.length() == 0) {
        root->isTerminal = 1;
        return;
    }
    char ch = word[0];
    int index = ch - 'a';
    Trie* child;
    if(root->child[index]) {
        child = root->child[index];
    }
    else {
        child = new Trie(ch);
        root->child[index] = child;
    }
    insertion(child, word.substr(1));
}

// method 1:
// void store_string(Trie* root, vector<string> &ans, string &word, string prefix) {
//     // base case
//     if(root->isTerminal) {
//         /*if the word we're traversring through is marked at
//         terminal so we're storing that word along with our
//         given prefix so that it forms a complete word*/
//         ans.push_back(prefix + word);
//     }
//     /*here we're traversing through each alphabet to identify
//     the character that is stored in the next node we're traveling to*/
//     for(char ch='a'; ch<='z'; ++ch) {
//         int index = ch - 'a';
//         Trie* next = root->child[index];
//         if(next) {
//             // it means that the child exist in the trie
//             word.push_back(ch);
//             // recursive call
//             store_string(next, ans, word, prefix);
//             // backtracking
//             word.pop_back();
//         }
//     }
// }
// void print_prefix(Trie* root, string word, vector<string> &ans, string prefix) {
//     if(word.length() == 0) {
//         Trie* lastChar = root;
//         /*after finding the last word in prefix string we're
//         calling a function that will give the remaining
//         string that occurs after the prefix string in trie*/
//         store_string(lastChar, ans, word, prefix);
//         return;
//     }
//     char ch = word[0];
//     int index = ch - 'a';
//     Trie* child;
//     if(root->child[index])
//         child = root->child[index];
//     else 
//         return;
//     print_prefix(child, word.substr(1), ans, prefix);
// }

// method 2:
void store_string(Trie* root, vector<string> &ans, string prefix) {
    // base case
    if(root->isTerminal)
        ans.push_back(prefix);
    for(char ch='a'; ch<='z'; ++ch) {
        int index = ch - 'a';
        Trie* next = root->child[index];
        if(next) {
            prefix.push_back(ch);
            store_string(next, ans, prefix);
            prefix.pop_back();
        }
    }
}
// void print_prefix(Trie* root, int index, vector<string> &ans, string prefix) {
//     if(index == prefix.length()) {
//         Trie* lastChar = root;
//         store_string(lastChar, ans, prefix);
//         return;
//     }
//     char ch = prefix[index];
//     int childIndex = ch - 'a';
//     Trie* child;
//     if(root->child[childIndex])
//         child = root->child[childIndex];
//     else 
//         return;
//     print_prefix(child, index+1, ans, prefix);
// }

vector<vector<string>> get_suggestions(Trie* root, string word) {
    vector<vector<string>> result;
    Trie* prev = root;
    string wordHelper = "";
    for(int i=0; i<word.length(); ++i) {
        char lastChar = word[i];
        int index = lastChar - 'a';
        Trie* curr = prev->child[index];
        if(curr) {
            vector<string> upcommingAns;
            wordHelper.push_back(lastChar);
            store_string(curr, upcommingAns, wordHelper);
            result.push_back(upcommingAns);
            // important
            prev = curr;
        }
        else    
            break;
    }
    return result;
}

int main() {

    Trie* root = new Trie('$');
    int N;
    cout << "how many words you want to insert : ";
    cin >> N;
    string str;
    for(int i=0; i<N; ++i) {
        cin >> str;
        insertion(root, str);
    }

    /*executed by taking a second string equal to prefix*/
    // vector<string> ans;
    // string prefix;
    // cout << "enter the prefix : ";
    // getline(cin, prefix);
    // string word = prefix;
    // print_prefix(root, word, ans, prefix);
    // cout << "printing all the words that are prefix to given word : " << "[ ";
    // for(auto a:ans)
    //     cout << a << " ";
    // cout << "]" << endl;

    /*executed the same question without second string, but by the use of [index]*/
    // vector<string> ans;
    // string prefix;
    // cout << "enter the prefix : ";
    // getline(cin, prefix);
    // int index = 0;
    // print_prefix(root, index, ans, prefix);
    // cout << "printing all the words that are prefix to given word : " << "[ ";
    // for(auto a:ans)
    //     cout << a << " ";
    // cout << "]" << endl;

    string input;
    cout << "mention prefix : ";
    cin >> input;
    vector<vector<string>> ans = get_suggestions(root, input);
    int it=0;
    for(auto row:ans) {
        for(int i=0; i<=it; ++i)
            cout << input[i];
        cout << " -> " << "[ ";
        for(auto r:row) 
            cout << r << " ";
        cout << "]" << endl;
        ++it;
    }

    return 0;
}