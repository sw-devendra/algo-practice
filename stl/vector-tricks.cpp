#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void testUpLower(vector<int> v, int val) {
	auto upIt = upper_bound(v.begin(), v.end(), val);
	auto lowIt = lower_bound(v.begin(), v.end(), val);

	if (lowIt != v.end()) 
		cout << "Lower of " << val << ": Index " << (lowIt - v.begin()) << " Val: " << *lowIt << endl;
	else
		cout << "Lower of " << val << " does not exist" << endl;

	if (upIt != v.end())
		cout << "Upper of " << val << ": Index " << (upIt - v.begin()) << " Val: " << *upIt << endl;
	else
		cout << "Upper of " << val << " does not exist" << endl;

}

void printVector(vector<int>& v) {
	for (auto n : v) {
		cout << n << " ";
	}
	cout << endl;
}

int main() {
	// Lower/Upper bound

	vector<int> v = { 1,1,1,2,2,2,4,4,4,5,5 };
	printVector(v);
	// // Not existing number
	testUpLower(v, 3);

	// Existing
	testUpLower(v, 1);
	testUpLower(v, 5);
	testUpLower(v, 0);
	testUpLower(v, 10);

	return 0;
}