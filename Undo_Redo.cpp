#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    stack<char> st, redo;

    while (n--)
    {
        string operation;
        cin >> operation;

        if (operation == "TYPE")
        {
            char c;
            cin >> c;
            st.push(c);

            while (!redo.empty())
                redo.pop();
        }
        else if (operation == "UNDO")
        {
            if (!st.empty())
            {
                redo.push(st.top());
                st.pop();
            }
        }
        else if (operation == "REDO")
        {
            if (!redo.empty())
            {
                st.push(redo.top());
                redo.pop();
            }
        }
    }

    string result;
    while (!st.empty())
    {
        result += st.top();
        st.pop();
    }

    reverse(result.begin(), result.end());
    cout << result << '\n';

    return 0;
}