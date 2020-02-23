#include <iostream>

#define MAX_STACK 3
#define END -1
using namespace std;

class StackPool{
public:
    StackPool(int size):arraySize(size) {
        array = new StackEntry[arraySize];
        init();
    }
    ~StackPool() {
        delete [] array;
    }
    void push(int v, int stackId) {
        if (stackId >= MAX_STACK) {
            cout<<"Error: Max allowed stack id is "<<(MAX_STACK -1)<<endl;
            return;
        }
        int n = getAvailable();
        if (n == -1) {
            cout<< "Error: StackPool overflow" << endl;
            return;
        }
        
        array[n].val = v;
        array[n].next = stackHeads[stackId];
        stackHeads[stackId] = n;
    }

    int top(int stackId) {
        if (stackId >= MAX_STACK) {
            cout<<"Error: Max allowed stack id is "<<(MAX_STACK -1)<<endl;
            return -1;
        }
        if (stackHeads[stackId] == -1) {
            cout <<"Error: Stack is Empty"<<endl;
            return -1;
        }
        return array[stackHeads[stackId]].val;
    }

    void pop(int stackId) {
        if (stackId >= MAX_STACK) {
            cout<<"Error: Max allowed stack id is "<<(MAX_STACK -1)<<endl;
            return;
        }
        if (stackHeads[stackId] == -1) {
            cout <<"Error: Stack is Empty"<<endl;
            return;
        }
        int n = stackHeads[stackId];
        stackHeads[stackId] = array[n].next;
        returnAvailable(n);
    }
private:
    void init() {
        availStart = 0;
        for (int i = 0 ; i<(arraySize - 1); i++) {
            array[i].next = i+1;
        }
        array[arraySize-1].next = END;
        for (int i=0; i<MAX_STACK; i++)
            stackHeads[i] = END;
    }
    int getAvailable() {
        if (availStart == END) {
            return -1;
        }
        int ret = availStart;
        availStart = array[availStart].next;

        return ret;
    }
    void returnAvailable(int n) {
        array[n].next = availStart;
        availStart = n;
    }

private:
    struct StackEntry {
        int val;
        int next;
    } *array;
    int arraySize;
    int availStart;
    int stackHeads[MAX_STACK];
    
};

int main() {
    StackPool sp(10);
    // Using just one stack at a time
    for (int sti=0; sti<3; sti++) {
        for (int i=1; i<=11; i++) {
            cout<<"Pushing in "<<sti<<"th stack: "<<i*10<<endl;
            sp.push(10*i,0); // last push will show error
        }
        for (int i=1; i<=11; i++) {
            cout<<"Top in "<<sti<<"th stack: "<<sp.top(0)<<endl;
            cout<<"Poping from "<<sti<<"th stack: "<<endl;
        }    
    }
    return 0;
}