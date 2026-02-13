#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int q;
    cin >> q;
    
    long long max_element = 1;
    long long min_element = 1;
    long long sum = 1;
    
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        
        long long new_element;
        if (x > 0) {
            new_element = max_element * x;
        } else if (x < 0) {
            new_element = min_element * x;
        } else {
            new_element = 0;
        }
        
        sum += new_element;
        max_element = max(max_element, new_element);
        min_element = min(min_element, new_element);
    }
    
    cout << sum << endl;
    
    return 0;
}