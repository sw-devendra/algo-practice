#include <iostream> 

#define MAX 10000000

int minheap[MAX + 1];
int cnt = 0;

void swap(int a, int b) {
	int t = minheap[a];
	minheap[a] = minheap[b];
	minheap[b] = t;
}

void insert(int a) {
	cnt++;
	minheap[cnt] = a;
	int p = cnt / 2;
	int ch = cnt;
	while (p && minheap[p] > minheap[ch]) {
		swap(p, ch);
		ch = p;
		p = ch / 2;
	}
}

int getMin() {
	return minheap[1];
}

void remove() {
	swap(1, cnt);
	cnt--;
	int p = 1;

	while (1) {
		int ch1 = 2 * p;
		int ch2 = 2 * p + 1;
		int smallerChild;

		if (ch1 > cnt) {
			break;
		}

		if (ch2 > cnt) {
			smallerChild = ch1;
		}
		else {
			smallerChild = ((minheap[ch1] < minheap[ch2]) ? ch1 : ch2);
		}
		if (minheap[p] < minheap[smallerChild])
			break;

		swap(p, smallerChild);
		p = smallerChild;
	}
}


// test 

#include <cstdlib>
#include <iostream>

using namespace std;
int nums[MAX + 1];
int main() {
	srand(MAX);

	int end = MAX;
	for (int i = 1; i<=end; i++) {
		nums[i] = i;
	}
	for (int i = 1; i <= end; i++) {
		int a = rand() % end + 1;
		int b = rand() % end + 1;
		int t = nums[a];
		nums[a] = nums[b];
		nums[b] = t;
	}
	for (int i = 1; i <= end; i++) {
		insert(nums[i]);
	}
	int lastMin = -1;
	while (cnt) {
		int min = getMin();
		
		if (min < lastMin) {
			cout << "Error!!!!!!!!!!!" << endl;
			break;
		}
	//	cout << min << "\t";
		remove();
		lastMin = min;
	}
	cout << "done" << endl;
	char ch;
	cin >> ch;
	return 0;
}
