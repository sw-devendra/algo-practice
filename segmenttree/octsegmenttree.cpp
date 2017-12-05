// https://www.hackerrank.com/challenges/cube-summation/problem

#include <iostream>

using namespace std;

#define MAX_N 100
//#define MAX_TREE 1000
int cube[MAX_N + 1][MAX_N + 1][MAX_N + 1];
struct Node {
    char x1;
    char y1;
    char z1;
    char x2;
    char y2;
    char z2;
    long long sum;
} *tree;

int id2segId[MAX_N + 1][MAX_N + 1][MAX_N + 1];

int getTreeSize(int N) {
    int lastLevelSize = 8;
    int totSize = 8;
    int minSpacerequired = (N+1)*(N+1)*(N+1) + 1;
    while(lastLevelSize <=minSpacerequired ) {
        lastLevelSize = lastLevelSize*8;
        totSize = totSize + lastLevelSize;
    }

    return totSize + lastLevelSize*8; 
}

// Construct tree
void construct(char x1, char y1, char z1, char x2, char y2, char z2, int id) {
    tree[id].sum = 0;
    if (x1 > x2 || y1 > y2 || z1 > z2)
        return;

    tree[id].x1 = x1;
    tree[id].y1 = y1;
    tree[id].z1 = z1;

    tree[id].x2 = x2;
    tree[id].y2 = y2;
    tree[id].z2 = z2;

    if (x1 == x2 && y1 == y2 && z1 == z2) {
        id2segId[x1][y1][z1] = id;
        tree[id].sum = cube[x1][y1][z1];
        return;
    }

    char mx = (x1 + x2)/2;
    char my = (y1 + y2)/2;
    char mz = (z1 + z2)/2;

    construct(x1,y1,z1, mx, my, mz,id*8);
    construct(mx+1,y1,z1, x2, my, mz,id*8 +1);
    construct(x1,my+1,z1, mx, y2, mz,id*8 +2);
    construct(mx+1,my + 1,z1, x2, y2, mz,id*8 + 3);

    construct(x1,y1,mz+1, mx, my, z2,id*8+4);
    construct(mx+1,y1,mz +1,x2 , my, z2,id*8+5);
    construct(x1,my+1,mz+1, mx, y2, z2,id*8+6);
    construct(mx+1,my+1,mz+1, x2,y2,z2,id*8+7);

    tree[id].sum = 0;
    for (int i=0; i<8; i++) {
            tree[id].sum = tree[id].sum + tree[id*8 + i].sum;
    }
}

void update(char x, char y, char z, int val) {
    int oldVal = cube[x][y][z];
    cube[x][y][z] = val;
    int treeId = id2segId[x][y][z];
    tree[treeId].sum = val;
    treeId = treeId/8;
    while(treeId) {
        tree[treeId].sum = tree[treeId].sum - oldVal + val;
        treeId = treeId/8;
    }
}

long long getSum(char x1, char y1, char z1, char x2, char y2, char z2, int id) {
    if (tree[id].x1 > x2 || tree[id].x2 < x1
        || tree[id].y1 > y2 || tree[id].y2 < y1
        || tree[id].z1 > z2 || tree[id].z2 < z1)
    return 0;

    if (tree[id].x1 >= x1 && tree[id].x2 <= x2
         && tree[id].y1 >= y1 && tree[id].y2 <= y2
        && tree[id].z1 >= z1 && tree[id].z2 <= z2)
        return tree[id].sum;

    long long sum = 0;
    for (int i=0; i<8; i++) {
        sum = sum + getSum( x1,  y1,  z1,  x2, y2, z2, 8*id + i);
    }

    return sum;
}

int main() {
    int T;
    cin>>T;
    while(T--) {
        int N;
        int M;
        cin>>N;
        cin>>M;
        for (int x=1; x<=N; x++) {
            for (int y=1; y<=N; y++) {
                for (int z=1; z<=N; z++) {
                    cube[x][y][z] = 0;
                }
            }            
        }
         
        int treeSize = getTreeSize(N);
        tree = new Node[treeSize]; 
        construct(1,1,1,N,N,N,1);
        for (int i=0; i<M;i++) {
            char com[20];
            cin>>com;
            if (com[0] == 'U') {
                int x,y,z,val;
                cin>>x>>y>>z>>val;
                update(x,y,z,val);
            }
            else {
                 int x1,y1,z1,x2,y2,z2;
                 cin>>x1>>y1>>z1>>x2>>y2>>z2;
                 cout<<getSum(x1,y1,z1,x2,y2,z2,1)<<endl;               
            }
        }
        if (tree) {
            delete []tree;
            tree = 0;
        }
    }

    return 0;
}
