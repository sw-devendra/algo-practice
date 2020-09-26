#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdio.h>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
typedef int Record;
#define TEST_IP_FILE "mergeSortTestIP.bin"
#define TEST_OP_FILE "mergeSortTestIP-out.bin"
#define IN_MEMORY_SORT_THRESHOLD 1000
using namespace std;

string mergeSort(string filePath, string outputFilePath) {
	// Divide the original file in multiple, in memory sortable files
	ifstream file(filePath, ios_base::binary);
	if (!file.is_open()) {
		cout << "Error: Failed to open file " << filePath <<endl;
		return "";
	}
	int inMemorySortableRecordCnt = IN_MEMORY_SORT_THRESHOLD / sizeof(Record);
	int memorySizeToRead = inMemorySortableRecordCnt * sizeof(Record);
	file.seekg(0, ios_base::end);
	int totalSize = file.tellg();
	file.seekg(0, ios_base::beg);
	int remainingBytes = totalSize;
	vector<string> tempFiles;
	int tempFileId = 0;
	while (remainingBytes > 0) {
		if (memorySizeToRead > remainingBytes) {
			memorySizeToRead = remainingBytes;
		}
		Record* records = new Record[memorySizeToRead / sizeof(Record)];
		file.read((char*)records, memorySizeToRead);
		remainingBytes -= memorySizeToRead;
		// ToTo: check read was successful
		sort(records, records + memorySizeToRead / sizeof(Record));
		string tempFileName = to_string(tempFileId++);
		ofstream of(tempFileName, ios_base::binary);
		if (!of.is_open()) {
			cout << "Error: Cannot open temp file " << tempFileName << endl;
			return "";
		}
		of.write((char*)records, memorySizeToRead);
		
		delete []records;
		tempFiles.push_back(tempFileName);
	}

	// Merge temp files N=> N/2 => N=>4--- =>1
	while (tempFiles.size() != 1) {
		vector<string> mergedFiles;
		for (int i = 0; i < tempFiles.size(); i = i + 2) {
			if ((i + 1) == tempFiles.size()) {
				mergedFiles.push_back(tempFiles[i]);
				break;
			}
			ifstream if1(tempFiles[i], ios_base::binary);
			ifstream if2(tempFiles[i + 1], ios_base::binary);
			if (!if1.is_open() || !if2.is_open()) {
				// ToDo: remove all temp files
				cout << "Error: Cannot open temp files " << tempFiles[i] <<" or " << tempFiles[i+1] << endl;
				return "";
			}
			Record val1 = -1;
			Record val2 = -1;
			// If size of tempfiles vector is 2, this merge will be the final merge
			string tempFileName = (tempFiles.size() == 2)?outputFilePath: to_string(tempFileId++);
			ofstream of(tempFileName, ios_base::binary);
			if (!of.is_open()) {
				cout << "Error: Cannot open temp files " << tempFileName << endl;
				return "";
			}
			while (!if1.eof() || !if2.eof()) {
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
					break;
				}
				Record val = -1;
				// consumed variable is set to -1
				if (val1 == -1) {
					val = val2;
					val2 = -1;
				}
				else if (val2 == -1) {
					val = val1;
					val1 = -1;
				}
				else if (val1 < val2) {
					val = val1;
					val1 = -1;
				}
				else {
					val = val2;
					val2 = -1;
				}
				of.write((char*)&val, sizeof(Record));
			}
			// Removed both of the merged input files
			if1.close();
			if2.close();
			remove(tempFiles[i].c_str()); 
			remove(tempFiles[i+1].c_str());
			mergedFiles.push_back(tempFileName);
		}
		tempFiles = mergedFiles;
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
	cout << "File: " << filePath << endl;
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
	cout << endl << endl;
	f.close();
}

int main() {
	generateTempInput(50000);
	testFile(TEST_IP_FILE);
	string output = mergeSort(TEST_IP_FILE, TEST_OP_FILE);
	testFile(output);
	return 0;
}