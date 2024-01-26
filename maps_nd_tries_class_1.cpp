#include<bits/stdc++.h>

using namespace std;

// counting the frequency of each char that occurs in the string
void count_frequency(unordered_map<char, int> &mp, string &str) {
    for(auto s:str) 
        mp[s]++;
}

// linked list cycle
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(0) {}
};
bool is_cycle(Node* head) {
    /*here we're creating a map where we are storing the values
    in pair of {Node*, bool} so that we make sure that after 
    traversing on each node we should be marking it as a 
    visited so that if we come accross to the same node so we
    can tell that the entire linked list is circular*/
    unordered_map<Node*, bool> cycle;
    Node* temp = head;
    while(temp) {
        // it means that the node isn't found yet
        if(!cycle.count(temp)) {
            cycle[temp] = 1;
            temp = temp->next;
        }
        // it means that the node has been found
        else 
            return true;
    }
    return false;
}

int main() {

    unordered_map<char, int> mp;
    string str;
    cout << "enter any string here : ";
    getline(cin, str);
    count_frequency(mp, str);
    for(auto m:mp) {
        cout << "[ ";
        cout << m.first << " -> " << m.second;
        cout << " ]";
    }
    cout << endl;

    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);
    head->next->next->next = head;
    // 10 -> 20 -> 30 -> 10
    if(is_cycle(head))
        cout << "it's a circular linked list" << endl;
    else 
        cout << "no it's not a circular linked list" << endl;

/*basic wisdom about map STLs*/
    // creation of map
    map<string, int> mp;
    // insertion in map
    mp["yamamoto"] = 1;

    /*as we're insertin values in pairs inside
    the map so here are some of the common 
    methods to inserti values in pairs*/
    // method 1:
    pair<string, int> priest = make_pair("ichibe hyosube", 0);
    // method 2:
    pair<string, int> cherry_blosom("byakuya kuchicki", 10);
    // method 3:
    pair<string, int> she_kenpachi;
    she_kenpachi.first = "retsu unohana";
    she_kenpachi.second = 4;
    // method 4:
    pair<string, int> two_blades({"shunsui kyoraku", 8});

    // insert all these pairs in map => [mp]
    mp.insert(priest);
    mp.insert(cherry_blosom);
    mp.insert(she_kenpachi);
    mp.insert(two_blades);

    // checking the size of the map we created
    cout << "the size of map : " << mp.size() << endl;

    // accessing the member function that are stored in map
    cout << "byakuya kuchicki is the captain of squad : " << mp.at("byakuya kuchicki") << endl;
    cout << "yamamoto is the captain of squad : " << mp["yamamoto"] << endl;

    // searching for values in map
    // method 1:
    /*if the provided value here is present in the map then the
    output would return [1], else if the provided value isn't present
    in the entire map then the output should be [0]*/
    cout << mp.count("ichibe hyosube") << endl;
    // method 2:
    /*here in this method we're checking the value is present or not
    int the map through [iterator] if the value is presented in the 
    map then the iterator is being stucked at the place where the 
    desired value should be situated, otherwise if the provide value
    isn't presented in the map so the iterator is pointing towards the
    end of the entire map, that's why we created a condition where if the
    desired value isn't equals to it's end position then the value is found,
    other wise the value isn't foundable so else case should apply*/
    if(mp.find("kenpachi zaraki") != mp.end())
        cout << "found the lost captain" << endl;
    else 
        cout << "the lost captain isn't found yet" << endl;

    // important note about [] this thing
    /*if we check a value by [] this operator which isn't declared before in the map,
    and then check the size of map we see that there is an increase in the size of the
    map from before this is the power of [] this operator while checking unknown value*/
    cout << mp["kenpachi zaraki"] << endl; // {o/p} => {0}
    cout << "current size after checking the unknown value : " << mp.size() << endl;

    return 0;
}