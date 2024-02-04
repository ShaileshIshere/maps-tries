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
// method 1: trie
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
// method 2: string matching
vector<bool> camelMatch(vector<string>& queries, string pattern) {
    vector<bool> result;
    for(int i = 0; i < queries.size(); ++i) {
        int p = 0;
        int j;
        for(j = 0; j < queries[i].size(); ++j) {
            if(isupper(queries[i][j])) {
                if(p < pattern.size() && pattern[p] == queries[i][j])
                    ++p;
                else 
                    break;
            } else {
                if(p < pattern.size() && islower(pattern[p]) && pattern[p] == queries[i][j])
                    ++p;
                else if(isupper(pattern[p]) || p == pattern.size())
                    continue;
            }
        }
        if(j != queries[i].size() || p < pattern.size())
            result.push_back(false);
        else
            result.push_back(true);
    }
    return result;
}

// palindrome pairs
struct TrieNode{
    char data;
    /*this thing marks all the chars in trie as (-1)
    ans the char that are at last node in trie to 
    their respected index values*/
    int stringIndex;
    TrieNode* child[26];
    TrieNode(char val) : data(val), stringIndex(-1) {
        for(int i=0; i<26; ++i)
            child[i] = 0;
    }
};
class Trie {
    TrieNode* root;

    void inserting(TrieNode* node, string &word, int it, int &stringIndex) {
        if(it == word.length()) {
            /*here's some modification
            we've given the index value to the last node in trie of a particular word*/
            node->stringIndex = stringIndex;
            return;
        }
        int index = word[it] - 'a';
        if(!node->child[index])
            node->child[index] = new TrieNode(word[it]);

        inserting(node->child[index], word, it+1, stringIndex);
    }

    bool isPalindrome(string &str, int left, int right) {
        while(left <= right) {
            if(str[left] != str[right])
                return false;
            ++left, --right;
        }
        return true;
    }

    void searchCase2(TrieNode* node, vector<int> &v, string ans) {
        // base case
        if(node->stringIndex != -1) {
            if(isPalindrome(ans, 0, ans.size()-1))
                v.push_back(node->stringIndex);
        }
        for(int i=0; i<26; ++i) {
            if(node->child[i]) {
                // inserting the next char in trie
                ans.push_back(i + 'a');
                // recursion hora bhot bhayankar
                searchCase2(node->child[i], v, ans);
                // backtracking hori bhot bhayankar
                ans.pop_back();
            }
        }
    }
    
public:
    Trie() {
        root = new TrieNode('$');
    }
    
    void insert(string &word, int &stringIndex) {
        inserting(root, word, 0, stringIndex);
    }
    
    void search(string &word, vector<int> &myPalindrome) {
        TrieNode* curr = root;

        // case 1: when [prefix] matches the word that is in trie
        for(int i=0; i<word.size(); ++i) {
            int index = word[i] - 'a';
            // check if the rest of the word(that is being searched) is palindrome?
            if(curr->stringIndex != -1) {
                if(isPalindrome(word, i, word.size()-1))
                    myPalindrome.push_back(curr->stringIndex);
            }
            if(curr->child[index])
                curr = curr->child[index];
            else 
                return;  
        }

        // case 2: when the word we're searching is a [prefix] of a word that is presented in trie
        searchCase2(curr, myPalindrome, "");
    }
};
vector<vector<int>> palindromePairs(vector<string>& words) {
    vector<vector<int>> ans;
    Trie trie;

    // reverse inserting
    for(int i=0; i<words.size(); ++i) {
        auto reverseWord = words[i];
        // reversing the word before inserting it into the trie
        reverse(reverseWord.begin(), reverseWord.end());
        trie.insert(reverseWord, i);
    }

    // find palindromic pairs of each word
    for(int i=0; i<words.size(); ++i) {
        // it stores palindromic pairs as index values
        vector<int> myPalindrome; 
        trie.search(words[i], myPalindrome);
        // here we insert all the possible palindromic pairs in [ans]
        for(auto it : myPalindrome) {
            if(it != i)
                ans.push_back({i, it});
        }
    }
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

    int n;
    cout << "no. of words : ";
    cin >> n;
    vector<string> words(n);
    for(int i=0; i<n; ++i)
        cin >> words[i];
    vector<vector<int>> result = palindromePairs(words);
    cout << "here are all the possible palindromic pairs :-" << endl << "[ ";
    for(auto row : result) {
        cout << "[ ";
        for(int col : row)
            cout << col << " ";
        cout << "]";
    }
    cout << " ]" << endl;

    return 0;
}