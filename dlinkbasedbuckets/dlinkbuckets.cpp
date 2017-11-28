// Doubly linkeed list based buckets

#include <iostream>

using namespace std;
#define MAX 1000000

struct BucketNode {
    int info;
    int bucketID;
    static int bucketNodesCnt;
    BucketNode *next, *prev;
    BucketNode(int i) {
        info = i;
        next = prev = 0;
        bucketID = -1;
        bucketNodesCnt++;
    }
    ~BucketNode() {
        if (next) {
            delete next;
        }
        bucketNodesCnt--;
    }
} *buckets[MAX];
int bucketSize[MAX];
int BucketNode::bucketNodesCnt = 0;

void insertFront(BucketNode *bn, int id) {
    bn->next = buckets[id];
    bn->prev = 0;
    bn->bucketID = id;
    if (buckets[id]) {
        buckets[id]->prev = bn;
    }
    buckets[id] = bn;
    bucketSize[id]++;
}

void remove(BucketNode *bn) {
    int id = bn->bucketID;
    if (bn->prev == 0) { // at front of bucket
        buckets[id] = bn->next;
    }
    else {
        bn->prev->next = bn->next;
    }
    if (bn->next) {
        bn->next->prev = bn->prev;
    }
    bn->prev = bn->next = 0;
    bucketSize[id]--;
}


void destroyBuckets() {
    for (int i=0; i<MAX; i++) {
        delete buckets[i];
        buckets[i] = 0;
        bucketSize[i] = 0;
    }
}

//////////////////// Testing
#include <cstdlib>



void testCreation(int count, int maxID) {
    srand(count);
    for (int i=0; i<count; i++) {
        BucketNode *bn = new BucketNode(i);
        insertFront(bn,rand()%maxID);
    }
}

void testMovements(int count, int maxID) {
    for (int i=0; i<count; i++) {
        int sid = -1;
        do {
            sid = rand() % maxID;
        }while (bucketSize[sid] == 0);
        int bucketNodeId = rand()%bucketSize[sid];
        BucketNode *bn = buckets[sid];
        while(bucketNodeId) {
            bn = bn->next;
            bucketNodeId--;
        }
        int tid = rand()%maxID;
        remove(bn);
        insertFront(bn, tid);
    }
}

void printBuckets(int maxID) {
    for (int i=0; i<maxID; i++) {
        cout << i <<" : Size: "<<bucketSize[i]<< " : ";
        for (BucketNode *bn = buckets[i]; bn; bn = bn->next) {
            cout<<bn->info << " ";
        }
        cout<<endl;
    }
}


void simpleTest() {
    testCreation(20,5);
    cout<< "After Creation--" << endl; 
    printBuckets(5);
    testMovements(10, 5);
    cout<< "After Movement--" << endl; 
    printBuckets(5);
    cout<<"bucketNodesCnt : " << BucketNode::bucketNodesCnt << endl;
    destroyBuckets();
    cout<< "After Destroying--" << endl; 
        
    printBuckets(5);
    cout<<"bucketNodesCnt : " << BucketNode::bucketNodesCnt << endl;
}

void extreamTest() {
    for (int i=10; i<10000000; i = i*10) {
        testCreation(i*10,i);
        cout<< "After Creation--" << endl; 
        cout<<"bucketNodesCnt : " << BucketNode::bucketNodesCnt << endl;
        testMovements(i/10, i);
        cout<< "After Movement--" << endl; 
        cout<<"bucketNodesCnt : " << BucketNode::bucketNodesCnt << endl;
        destroyBuckets();
        cout<< "After Destroying--" << endl; 
        cout<<"bucketNodesCnt : " << BucketNode::bucketNodesCnt << endl;
    }
}

int main() {
    extreamTest();
    return 0;
}