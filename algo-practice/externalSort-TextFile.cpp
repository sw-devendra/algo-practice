#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <time.h>
#include <stdlib.h>

#define TEMP_IP "temp.txt"
#define TEMP_OP "temp-out.txt"

using namespace std;

#define ISL 10 // INMEMORY_SORT_LIMIT
// To Do: Convert to a template based class
template<class T>
class FileSorter {
private:
	int fileId;

private:
	bool sortAndStore(vector<T>& v,vector<string> &fileList) {
		std::sort(v.begin(), v.end());
		string fileName = to_string(fileId++);
		ofstream ofile(fileName);
		if (!ofile.is_open()) {
			cout << "Failed to open file " << fileName << endl;
			// ToDo: clear collected files
			return false;
		}
		for (auto a : v) {
			ofile << a << " ";
		}
		fileList.push_back(fileName);
		return true;
	}
	vector<string> breakFile(ifstream& infile) {
		T temp;
		vector<T> currentData;
		vector<string> brokenFiles;
		fileId = 0;
		while (infile >> temp) {
			currentData.push_back(temp);
			if (currentData.size() == ISL) {
				if (!sortAndStore(currentData, brokenFiles)) {
					return vector<string>();
				}
				currentData.clear();
			}
		}
		if (!currentData.empty()) {
			if (!sortAndStore(currentData, brokenFiles)) {
				return vector<string>();
			}
			currentData.clear();
		}

		return brokenFiles;
	}

	vector<string> mergeFiles(vector<string>& sortedFiles) {
		vector<string> outputFiles;
		for (int i = 0; (i+1) < sortedFiles.size(); i += 2) {
			ifstream if1(sortedFiles[i]);
			ifstream if2(sortedFiles[i+1]);

			if (!if1.is_open() || !if2.is_open()) {
				cout << "Error: Cannot open intermediate files for reading " << sortedFiles[i] <<" or "<< sortedFiles[i+1] <<endl;
				// ToDo: remove files collected by now;
				return vector<string>();
			}
			string outfile = to_string(fileId++);
			ofstream ofile(outfile);
			if (!ofile.is_open()) {
				cout << "Error: Cannot open intermediate files for reading " << outfile << endl;
				// ToDo: remove files collected by now;
				return vector<string>();
			}
			T temp1 = -1, temp2 = -1;
			while (1) {
				if (temp1 == -1) {
					if (!(if1 >> temp1)) {
						temp1 = -1;
					};
				}
				if (temp2 == -1) {
					if (!(if2 >> temp2)) {
						temp2 = -1;
					};
				}
				if (temp1 == -1 && temp2 == -1) {
					break;
				}
				if (temp1 == -1 || (temp2 != -1 && temp2 <= temp1)) {
					ofile << temp2 <<endl;
					temp2 = -1;
					continue;
				}
				if (temp2 == -1 || (temp1 != -1 && temp1 <= temp2)) {
					ofile << temp1 <<endl;
					temp1 = -1;
					continue;
				}
			}
			outputFiles.push_back(outfile);
			if1.close();
			if2.close();
			remove(sortedFiles[i].c_str());
			remove(sortedFiles[i+1].c_str());
		}
		if (sortedFiles.size() % 2) {
			outputFiles.push_back(sortedFiles.back());
		}

		return outputFiles;
	}
public:
	void sort(ifstream& infile, ofstream &outfile) {
		vector<string> sortedFiles = breakFile(infile);
		while(sortedFiles.size() >1) 
			sortedFiles = mergeFiles(sortedFiles);

		if (sortedFiles.empty()) {
			return;
		}
		ifstream finalSorted(sortedFiles[0]);
		if (!finalSorted.is_open()) {
			cout << " Error: Reading " << sortedFiles[0] << endl;
			return;
		}
		int temp;
		while (finalSorted >> temp)
			outfile << temp << endl;
		finalSorted.close();
		remove(sortedFiles[0].c_str());
		return;
	}
};

void generateTextInput(int n) {
	ofstream f("temp.txt");
	if (f.good()) {
		srand(time(0));
		while (n--) {
			int v = rand() % 1000000;
			f << v << endl;
		}
	}
	f.close();
}

int main() {
	generateTextInput(50);
	ifstream tempIp(TEMP_IP);
	ofstream tempOp(TEMP_OP);

	FileSorter<int> fs;
	fs.sort(tempIp, tempOp);

	return 0;
}