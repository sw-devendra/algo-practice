// simple segTree to find Min
#include <iostream>

using namespace std;
#define MAX 100
#define MIN(a,b) (((a)<(b))?(a):(b))
// Assuming all numbers are smaller than 2 billion
#define INF 2000000000

struct {
    int val;
    int s;
    int e;
} segTree[MAX*4]; // To Do: Find best size based on MAX
int ip[MAX+1];
int N;

void construct(int id, int s, int e) {
    segTree[id].s = s;
    segTree[id].e = e;
    if (s == e) {
        segTree[id].val = ip[s];
        return;
    }

    int m = (s+e)/2;
    construct(2*id,s, m);
    construct(2*id +1, m+1, e);
    segTree[id].val = MIN(segTree[2*id].val, segTree[2*id +1].val);
}

int getMin(int id, int s, int e) {
    if (segTree[id].s > e || segTree[id].e < s)
        return INF;
    
    if (segTree[id].s >= s && segTree[id].e<=e) // id range is contained in queried range
        return segTree[id].val;

    int m1 = getMin(2*id, s, e);
    int m2 = getMin(2*id +1, s, e);

    return MIN(m1,m2);

}
int main() {

    cin>>N;
    for(int i=0; i<N; i++) {
        cin>>ip[i];
    }
    construct(1, 0,N-1);
    cout<<"Query count?";
    int q;

    cin>>q;

    for (int i=0; i<q; i++) {
        int s, e;
        cin>>s>>e;
        cout<<getMin(1,s,e);
    }

    return 0;
}