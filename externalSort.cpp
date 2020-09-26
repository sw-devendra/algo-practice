#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
typedef int Record;
#define TEST_IP_FILE "mergeSortTestIP.bin"
#define IN_MEMORY_SORT_THRESHOLD 9
using namespace std;

string mergeSort(string filePath) {
	ifstream f(filePath, ios_base::binary);
	f.seekg(0, ifstream::end);
	int totalSize = f.tellg();
	f.seekg(0, ifstream::beg);
	vector<Record> result;
	int level = 0;
	vector<string> tempFiles;
	int fileId = 0;
	int remainingBytes = totalSize - f.tellg();
	while (remainingBytes) {
		int thresholdSizeInBytes = IN_MEMORY_SORT_THRESHOLD * sizeof(Record);
		int bytesToRead = (remainingBytes > thresholdSizeInBytes) ? thresholdSizeInBytes : remainingBytes;
		Record* input = new Record[bytesToRead/sizeof(Record)];
		f.read((char*)input, bytesToRead);
		remainingBytes = totalSize - f.tellg();
		sort(input, input + bytesToRead / sizeof(Record));
		string tempFileName = to_string(fileId++);
		ofstream f(tempFileName, ios_base::binary);
		f.write((char*)input, bytesToRead);
		tempFiles.push_back(tempFileName);
		delete []input;
		f.close();
	}

	while (tempFiles.size() != 1) {
		vector<string> mergedTemp;
		for (int i = 0; i < tempFiles.size(); i = i + 2) {
			if ((i + 1) == tempFiles.size()) {
				mergedTemp.push_back(tempFiles[i]);
				break;
			}
			string output(to_string(fileId++));
			ofstream outFile(output, ios_base::binary);
			if (!outFile.good()) {
				cout << "Error: Cannot open " << output;
				return "";
			}
			Record val1 = -1;
			Record val2 = -1;
			ifstream if1(tempFiles[i], ios_base::binary);
			ifstream if2(tempFiles[i+1], ios_base::binary);
			while (true) {
				if (val1 == -1) {
					if1.read((char*)&val1, sizeof(Record));
					if (if1.eof()) {
						val1 = -1;
					}
				}
				if (val2 == -1) {
					if2.read((char*)&val2, sizeof(Record));
					if (if2.eof()) {
						val2 = -1;
					}
				}
				if (val1 == -1 && val2 == -1) {
					break; // EOF of both the files
				}
				Record outVal = -1;
				if (val1 == -1) {
					outVal = val2; // val2 is being consumed
					val2 = -1;
				}
				else if (val2 == -1) {
					outVal = val1; // val2 is being consumed
					val1 = -1;
				}
				else if (val1 < val2) {
					outVal = val1;
					val1 = -1;
				}
				else {
					outVal = val2;
					val2 = -1;
				}
				outFile.write((char*)&outVal, sizeof(Record));
			}
			mergedTemp.push_back(output);
		}
		tempFiles = mergedTemp;
	}
	return tempFiles[0];
}

void generateTempInput(int n) {
	ofstream f(TEST_IP_FILE, ofstream::binary);
	if (f.good()) {
		srand(time(0));
		while (n--) {
			int v = rand() % 1000000;
			f.write((char*)&v, sizeof(v));
		}
	}
	f.close();
}

void testFile(string filePath) {
	ifstream f(filePath, ifstream::binary);
	if (f.good()) {
		srand(time(0));
		while (!f.eof()) {
			int v;
			f.read((char*)&v, sizeof(v));
			if (f.eof()) {
				break;
			}
			cout << v << '\t';
		}
	}
	cout << endl;
	f.close();
}

int main() {
	vector<int> v = { 12, 34, 2, 6, 7, 34, 9, 12, 76, 22 };
	generateTempInput(123);
	testFile(TEST_IP_FILE);
	string output = mergeSort(TEST_IP_FILE);
	testFile(output);
	//auto result = mergeSort(v);
	//for (auto r : result) {
	//	cout << r << " ";
	//}
	return 0;
}