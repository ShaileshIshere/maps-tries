#include<bits/stdc++.h>

using namespace std;

// replace words
struct TrieNode{
    char data;
    bool isTerminal;
    TrieNode* child[26];
    int freq; // top [k] frequent words
    TrieNode(char val) : data(val), isTerminal(0), freq(0) {
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

// top [k] frequent words 
struct comp {
    bool operator()(const pair<int, string> &a, const pair<int, string> &b) {
        return a.first == b.first ? a < b : a.first > b.first;
    }
};
class trie {
    TrieNode* root;

    void inserting(TrieNode* node, string &word, int it) {
        if(it == word.length()) {
            node->isTerminal = 1;
            ++node->freq;
            return;
        }
        int index = word[it] - 'a';
        if(!node->child[index])
            node->child[index] = new TrieNode(word[it]);

        inserting(node->child[index], word, it+1);
    }
    
    void traverseUtil(TrieNode* root, priority_queue<pair<int, string>, vector<pair<int, string>>, comp> &pq, string &s, int k) {
        // base case
        if(!root)
            return;
        // if we reached at the terminal point of a word present in trie
        if(root->isTerminal) {
            /*when the size of [pq] is less than [k] we're inserting every
            word in queue unaware of their respected frequencies*/
            if(pq.size() < k)
                pq.push({root->freq, s});
            /*when the size of queue matches with [k] that means we've to
            insert only those words which has highest frequency in the 
            given vector, and deleting the previous top most element in queue*/
            else if(pq.size() == k && root->freq > pq.top().first) {
                pq.pop();
                pq.push({root->freq, s});
            }
        }
        /*inserting every word in [s] string from trie*/
        for(int i=0; i<26; ++i) {
            if(root->child[i]) {
                // creating string character by character
                s.push_back(i + 'a');
                traverseUtil(root->child[i], pq, s, k);
                // backtracking step to process other words
                s.pop_back();
            }
        }
    }
    
public:
    trie() {
        root = new TrieNode('$');
    }
    
    void insert(string word) {
        inserting(root, word, 0);
    }
    
    void traverse(priority_queue<pair<int, string>, vector<pair<int, string>>, comp> &pq, int k) {
        string s;
        traverseUtil(root, pq, s, k);
    }
};
vector<string> topKFrequent(vector<string>& words, int k) {
    vector<string> ans;
    trie node;
    // inserting all words in tries
    for (auto word : words)
        node.insert(word);
    // creating a min heap for further progress
    priority_queue<pair<int, string>, vector<pair<int, string>>, comp> pq;
    // inserting only those words in queue that has high frequency
    node.traverse(pq, k);
    // inserting those high frequency words in [ans] vector
    while (!pq.empty()) {
        ans.push_back(pq.top().second);
        pq.pop();
    }
    // reversing the [ans] as we need it in descending order
    reverse(ans.begin(), ans.end());
    return ans;
}

// camel-case matching
struct TrieNode{
    char data;
    bool isTerminal;
    /*the reason to take [58] so that both the lower
    and upper case alphabets can be inserted into tries*/
    TrieNode* child[58];
    TrieNode(char val) : data(val), isTerminal(0) {
        for(int i=0; i<58; ++i)
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
        
        // [A] coz there's uppercase in every aspect of upcomming tries
        int index = word[it] - 'A';

        if(!node->child[index])
            node->child[index] = new TrieNode(word[it]);

        inserting(node->child[index], word, it+1);
    }

    bool searching(TrieNode* node, string &word, int it) {
        if(it == word.size())
            return node->isTerminal;

        int index = word[it] - 'A';

        if(node->child[index])
            return searching(node->child[index], word, it+1);
        /*this is the extra condition here we're making sure
        that the next char in [query] is a lower case so that
        we can simply ignore it and increment our iterator*/
        else if(islower(word[it]))
            return searching(node, word, it+1);

        return false;
    }
    
public:
    Trie() {
        root = new TrieNode('$');
    }
    
    void insert(string &word) {
        inserting(root, word, 0);
    }
    
    int search(string &word) {
        return searching(root, word, 0);
    }
};
vector<bool> camelMatch(vector<string> &queries, string pattern) {
    vector<bool> ans;
    Trie trie;
    trie.insert(pattern);
    for (string query : queries)
        ans.push_back(trie.search(query));
    return ans;
}

int main() {

    int n;
    cout << "how many words you want to add in your dictionary : ";
    cin >> n;
    vector<string> dictionary(n);
    for(int i=0; i<n; ++i)
        cin >> dictionary[i]; 
    string sentence;
    cout << "enter your sentence : ";
    cin.ignore();
    getline(cin, sentence);
    cout << "here is your sentence after replacing words :" << endl << replaceWords(dictionary, sentence) << endl;

    int n, k;
    cout << "no. of words : ";
    cin >> n;
    vector<string> words(n);
    for(int i=0; i<n; ++i)
        cin >> words[i];
    cout << "no. of frequent words : ";
    cin >> k;
    vector<string> result = topKFrequent(words, k);
    cout << "here are your top " << k << " frequent words :-" << endl;
    for(auto r:result)
        cout << "[ " << r << " ]" << " " << endl;

    int n;
    cout << "no. of words : ";
    cin >> n;
    vector<string> queries(n);
    for(int i=0; i<n; ++i)
        cin >> queries[i];
    string pattern;
    cin >> pattern;
    vector<bool> result = camelMatch(queries, pattern);
    cout << "here is your desired output :-" << endl << "[ ";
    for(auto r : result)
        cout << r << " ";
    cout << "]" << endl;

    return 0;
}