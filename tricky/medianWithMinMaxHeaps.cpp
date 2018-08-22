// https://www.hackerrank.com/challenges/find-the-running-median/problem
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

int maxHeap[100001];
int maxCnt;
int minHeap[100001];
int minCnt;

struct greater1 {
	bool operator()(int &a, int &b) const {
		return a > b;
	}
};

double getCurrentMedian() {
	if (maxCnt == minCnt) {
		return 1.0*(minHeap[0] + maxHeap[0]) / 2;
	}
	else if (maxCnt > minCnt) {
		return maxHeap[0];
	}
	else {
		return minHeap[0];
	}
}

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		if (i == 0) {
			cin >> maxHeap[0];
			maxCnt = 1;
		}
		else if (i == 1) {
			cin >> minHeap[0];
			minCnt = 1;
			if (maxHeap[0] > minHeap[0]) {
				int t = minHeap[0];
				minHeap[0] = maxHeap[0];
				maxHeap[0] = t;
			}
		}
		else {
			int t;
			cin >> t;
			if (t <= maxHeap[0]) {
				maxHeap[maxCnt] = t;
				maxCnt++;
				push_heap(maxHeap, maxHeap + maxCnt);
			}
			else {
				minHeap[minCnt] = t;
				minCnt++;
				push_heap(minHeap, minHeap + minCnt, greater1());
			}

			// balance
			if ((minCnt - maxCnt) > 1) {
				maxHeap[maxCnt] = minHeap[0];
				maxCnt++;
				push_heap(maxHeap, maxHeap + maxCnt);
				pop_heap(minHeap, minCnt + minHeap, greater1());
				minCnt--;
			}
			else if ((maxCnt - minCnt) > 1) {
				minHeap[minCnt] = maxHeap[0];
				minCnt++;
				push_heap(minHeap, minHeap + minCnt, greater1());
				pop_heap(maxHeap, maxCnt + maxHeap);
				maxCnt--;
			}
		}
		cout << std::fixed;
		cout << setprecision(1);
		cout << getCurrentMedian() << endl;
	}

	return 0;
}
