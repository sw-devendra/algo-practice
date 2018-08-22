// https://www.hackerrank.com/challenges/array-left-rotation/problem
#include <iostream>

using namespace std;

#define MAX 100000

int arr[MAX];
int N;

void print() {
	for (int i = 0; i < N; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}
int main() {
	int M;
	cin >> N >> M;
	for (int i = 0; i<N; i++) {
		cin>>arr[i];
	}
//	print();
	int rotations = 0;
	int start = 0;
	int i = 0;
	int temp = arr[M];
	while (rotations < N) {
		swap(temp, arr[i]);
		rotations++;
		i = (i - M + N)%N;
		if (i == start) {
			start = (start -1 + N)%N;
			i = start;
			temp = arr[(i + M) % N];
		}
	}
	print();
	return 0;
}
