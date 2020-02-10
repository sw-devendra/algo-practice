#include <iostream>
#include <stack>

// for testing
#include <vector>

using namespace std;

void sortStack(stack<int> &st) {
    if (st.size() <= 1)
        return ;

    while(1) {
        stack<int> temp;
        int t;
        temp.push(st.top());
        st.pop();
        while (!st.empty() && st.top() < temp.top()) {
            temp.push(st.top());
            st.pop();
        }
        if (st.empty()) { // Last iteration
            while(!temp.empty()) {
                st.push(temp.top());
                temp.pop();
            }
            break; // done
        }
        t = st.top(); // store bigger element in t for pushing later
        st.pop();
        while(!temp.empty() && temp.top() < t) {
            st.push(temp.top());
            temp.pop();
        }
        st.push(t);
        while(!temp.empty()) {
            st.push(temp.top());
            temp.pop();
        }
    }
}

void printStack(stack<int> &st) {
    stack<int> t;
    while(!st.empty()) {
        cout<<st.top()<<" ";
        t.push(st.top());
        st.pop();
    }
    while (!t.empty()) {
        st.push(t.top());
        t.pop();
    }
}
int main() {
    vector<vector<int>> v = {
        {4, 6, 8, 9, 11, 5},
        {1, 4, 6, 8, 9, 11, 5, 25},
        {1,2,3,4,5,6,7,8},
        {9,8,7,6,5,4,3,2}
    };

    for (auto vv: v) {
        stack<int> st;
        for (int n: vv) {
            st.push(n);
        }
        cout<<"Original Stack : ";
        printStack(st);
        cout<<endl;
        sortStack(st);
        cout<<"After Sorting : ";
        printStack(st);
        cout<<endl;
    }

    return 0;
}
