#include<bits/stdc++.h>

using namespace std;

// array subset of another array
string isSubset(int a1[], int a2[], int n, int m) {
    unordered_map<int, int> mp;
    for(int i=0; i<n; ++i)
        mp[a1[i]]++;
    for(int i=0; i<m; ++i) {
        if(mp.find(a2[i]) != mp.end() && mp[a2[i]] != 0)
            mp[a2[i]]--;
        else 
            return "No";
    }
    return "Yes";
}

// union of two linked list
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(0) {}
};
void insert_Node(Node* &head, Node* &tail, int data) {
    Node* newNode = new Node(data);
    if(!head)
        head = tail = newNode;
    else {
        tail->next = newNode;
        tail = newNode;
    }
}
void print_Node(Node* head) {
    Node* temp = head;
    while(temp) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}
struct Node *makeUnion(struct Node *head1, struct Node *head2) {
    // creating an ordered_map coz we need ans in ascending order
    map<int, Node *> mp;
    Node *temp = head1;
    // inserting the data from 1st list into map
    while (temp) {
        mp[temp->data] = temp;
        temp = temp->next;
    }
    temp = head2;
    // inserting the data from 2nd list into map
    while (temp) {
        mp[temp->data] = temp;
        temp = temp->next;
    }
    Node *unionList = nullptr;
    temp = 0;
    // creating another list in which we're inserting the elements which are occuring only once
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        if (!unionList)
            unionList = temp = it->second;
        else {
            temp->next = it->second;
            temp = temp->next;
        }
    }
    temp->next = 0;
    return unionList;
}

// intersection of two linked list
Node *findIntersection(Node *head1, Node *head2) {
    unordered_map<int, int> mp;
    Node *temp = head2;
    // here we're inserting the elements form 1st linked list as well as their occurence
    while (temp) {
        mp[temp->data]++;
        temp = temp->next;
    }
    temp = head1;
    Node *result = nullptr, *curr = nullptr;
    /*here we're creating a new linked list in which we're inserting only those
    elements which are common in the given linked lists*/
    while (temp) {
        // to find the occurence of element in map
        if (mp.find(temp->data) != mp.end()) {
            if (!result)
                result = curr = temp;
            else {
                // corner case/condition
                /*it means that if there's an element which occurres only 2 times
                int 2nd linked list and the same element is occurring in the 1st 
                list linked list over 2 times so we've to check whether the same element
                has the occurrence more that 0 to prove that it's also a common element*/
                if (mp[temp->data] > 0) {
                    curr->next = temp;
                    curr = curr->next;
                }
            }
            // deducting the occurence of similar elements, as they're already marked
            mp[temp->data]--;
        }
        temp = temp->next;
    }
    curr->next = nullptr;
    return result;
}

// sum equals to sum
int findPairs(long long a[], long long n) {
    unordered_map<int, bool> mp;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int sum = a[i] + a[j];
            // if there's another pair whose sum is also equals to the sum of prior inserted pair
            if (mp.find(sum) != mp.end())
                return true;
            /*first occurring pair from the array, we're setting it true so that
            if another pair of same sum will occurr, the previous [if] condition will trigger*/
            else
                mp[sum] = true;
        }
    }
    return false;
}

// largest subarray with [0] sum
int maxLen(vector<int> &A, int n) {
    unordered_map<int, int> mp;
    int currSum = 0, ans = 0;
    for (int i = 0; i < n; ++i) {
        currSum += A[i];
        /*edge case if curr sum is [0] then the
        process of finding the lenght would be different*/
        if (currSum == 0)
            ans = max(ans, i + 1);
        // we found the same sum twice
        else if (mp.find(currSum) != mp.end())
            ans = max(ans, i - mp[currSum]);
        // we found a different sum, so we've to update it
        else
            mp[currSum] = i;
    }
    return ans;
}

// largest subarrays of 0's and 1's
int maxLen(vector<int> &A, int n) {
    unordered_map<int, int> mp;
    int currSum = 0, ans = 0;
    for (int i = 0; i < n; ++i) {
        /*here we're converting every [0] in the array
        to [-1] for further processing of this program*/
        int val = A[i] == 0 ? -1 : 1;
        currSum += val;
        /*edge case if curr sum is [0] then the
        process of finding the lenght would be different*/
        if (currSum == 0)
            ans = max(ans, i + 1);
        // we found the same sum twice
        else if (mp.find(currSum) != mp.end())
            ans = max(ans, i - mp[currSum]);
        // we found a different sum, so we've to update it
        else
            mp[currSum] = i;
    }
    return ans;
}

int main() {

    // int n, m;
    // cout << "enter the size of [a1](big) array and [a2](smol) array : ";
    // cin >> n >> m;
    // int a1[n], a2[m];
    // for(int i=0; i<n; ++i)
    //     cin >> a1[i];
    // for(int i=0; i<m; ++i)
    //     cin >> a2[i];
    // cout << isSubset(a1, a2, n, m) << endl;

    // Node *head1 = 0, *tail1 = 0, *head2 = 0, *tail2 = 0;
    // int n, m;
    // cout << "enter the size of [1st] & [2nd] linked list : ";
    // cin >> n >> m;
    // for(int i=0; i<n; ++i) {
    //     int val;
    //     cin >> val;
    //     insert_Node(head1, tail1, val);    
    // }
    // for(int i=0; i<m; ++i) {
    //     int val;
    //     cin >> val;
    //     insert_Node(head2, tail2, val);
    // }
    // cout << "here's your [1st] & [2nd] linked list :-" << endl;
    // print_Node(head1);
    // print_Node(head2);
    // cout << "here's the union of both the given nodes :-" << endl;
    // Node* result = makeUnion(head1, head2);
    // print_Node(result);

    // Node *head1 = 0, *tail1 = 0, *head2 = 0, *tail2 = 0;
    // int n, m;
    // cout << "enter the size of [1st] & [2nd] linked list : ";
    // cin >> n >> m;
    // for(int i=0; i<n; ++i) {
    //     int val;
    //     cin >> val;
    //     insert_Node(head1, tail1, val);    
    // }
    // for(int i=0; i<m; ++i) {
    //     int val;
    //     cin >> val;
    //     insert_Node(head2, tail2, val);
    // }
    // cout << "here's your [1st] & [2nd] linked list :-" << endl;
    // print_Node(head1);
    // print_Node(head2);
    // cout << "intersection of two linked list :-" << endl;
    // Node* result = findIntersection(head1, head2);
    // print_Node(result);

    // long long n;
    // cout << "enter the size of array : ";
    // cin >> n;
    // long long arr[n];
    // for(int i=0; i<n; ++i)
    //     cin >> arr[i];
    // if(findPairs(arr, n))
    //     cout << "the pair exists" << endl;
    // else 
    //     cout << "the pair doesn't exists" << endl;

    // int n;
    // cout << "enter the size of vector : ";
    // cin >> n;
    // vector<int> A(n);
    // for(int i=0; i<n; ++i)
    //     cin >> A[i];
    // cout << "the length of largest subarray with [0] sum : " << maxLen(A, n) << endl;

    // cout << "the maximum length of subarray that contains equal no. of 0's and 1's : " << maxLen(A, n) << endl;

    return 0;
}