#include <iostream>

using namespace std;
#define MAX_N 11

// https://www.youtube.com/watch?v=CWDQJGaN1gY
int arr[MAX_N] = { 3,2,-1,6,5,4,-3,3,7,2,3 };
int bit[MAX_N + 1];

#define parent(x) (x - (x & (-x)))
#define next(x) (x + (x & (-x)))

void init() {
	for (int i = 0; i <= MAX_N; i++) {
		bit[i] = 0;
	}

	for (int i = 0; i < MAX_N; i++) {
		int x = i + 1;
		do {
			bit[x] = bit[x] + arr[i];
			x = next(x);
		} while (x <= MAX_N);
	}
}

int getSum(int x) {
	if (x) {
		return bit[x] + getSum(parent(x));
	}
	else
		return 0;
}

int getSum(int x, int y)
{
	return getSum(y) - getSum(x-1);
}
int main() {
	init();
	for (int i = 0; i < MAX_N; i++) {
		cout<< getSum(i+1, MAX_N)<<endl;
	}
	return 0;
}
