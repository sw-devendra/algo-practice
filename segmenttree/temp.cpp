#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 200000
#include TREE_SIZE 524288

struct city {
    long long dist,
    int p;
    bool operator < (city &other) {
        return (p < other.p);
    }
} cities[MAX + 1];

long long distArray[MAX + 1]

struct {
    int start;
    int end;
    long long distSum;
    int count;
}segTree[TREE_SIZE]; 
int idToSegTreeId[MAX + 1];

void constructSegTree(int start, int end, int id) {
    segTree[id].start = start;
    segTree[id].end = end;
    if (start == end) {
        segTree[id].count = 1;
        segTree[id].distSum = distArray[start];
        idToSegTreeId[start] = id;
        return;
    }
    int m = (start + end)/2;
    constructSegTree(start, m, 2*id);
    constructSegTree(m+1, end, 2*id + 1);
    segTree[id].count = segTree[2*id].count + segTree[2*id + 1].count;
    segTree[id].distSum = segTree[2*id].distSum + segTree[2*id + 1].distSum;
}

void removeId(int id) {
    int sid = idToSegTreeId[id];
    segTree[sid].distSum = 0;
    segTree[sid].count = 0;
    int p = sid/2;
    while (p) {
        segTree[p].distSum = segTree[2*p].distSum + segTree[2*p + 1].distSum;
        segTree[p].count = segTree[2*p].count + segTree[2*p + 1].count;
        p = p/2;
    }
}

int getCount(int start, int end, int id) {
    if (end < segTree[id].start || start > segTree[id].end) {
        return 0;
    }
    if (start <= segTree[id].start && end>=segTree[id].end)
        return segTree[id].count;
    
   return getCount(start, end, 2*id) + getCount(start, end, 2*id + 1);
}

int getDistSum(int start, int end, int id) {
    if (end < segTree[id].start || start > segTree[id].end) {
        return 0;
    }
    if (start <= segTree[id].start && end>=segTree[id].end)
        return segTree[id].distSum;
    
   return getDistSum(start, end, 2*id) + getDistSum(start, end, 2*id + 1);
}

int findDistId(long long dist) {
    int start = 1; int end = N;

    while(start <= end) {
        int m = (start + end)/2;
        if (distArray[m] == dist)
            return m;
        if (distArray[m] > dist) {
            end = m - 1;
        }
        else {
            start = m + 1;
        }
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int T;
    cin>> T;
    while(T--) {
        int N;
        for (int i=1; i<=N; i++) {
            cin>>city[i].dist;
            distArray[i] = city[i].dist;
        }
        for (int i=1; i<=N; i++) {
            cin>>city[i].p;
        }
        sort(city +1, city + N +1);
        sort(distArray + 1, distArray + N + 1);
        constructSegTree(1,N,1);
    }
    return 0;
}
