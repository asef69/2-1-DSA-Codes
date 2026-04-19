#include<bits/stdc++.h>
using namespace std;

int main() {
    list<string> d_list;
    string op;

    while (cin >> op && op != "end") {
        d_list.push_back(op);
    }

    int n;
    cin >> n;

    auto cur = d_list.begin(); 

    while (n--) {
        string operation;
        cin >> operation;

        if (operation == "prev") {
            if (cur == d_list.begin()) {
                cout << "Not Available" << endl;
            } else {
                --cur;
                cout << *cur << endl;
            }
        }
        else if (operation == "next") {
            auto temp = cur;
            ++temp;
            if (temp == d_list.end()) {
                cout << "Not Available" << endl;
            } else {
                ++cur;
                cout << *cur << endl;
            }
        }
        else { 
            string address;
            cin >> address;

            auto it = find(d_list.begin(), d_list.end(), address);
            if (it != d_list.end()) {
                cur = it;
                cout << *cur << endl;
            } else {
                cout << "Not Available" << endl;
            }
        }
    }
}