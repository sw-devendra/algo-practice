#include <iostream>
#include <vector>

#define MAX 1000
using namespace std;

int table[MAX][MAX]; // rows will represent the first string and columns second string
// Each cell in the table represents the distance between two prefixes of strings
// The values are filled based on smaller prefixes
// table[i][j] => edit distance between str1 prefix of size i and str2 prefix of size j
// table[i][j] could be calculated based on table[i-1][j-1], table[i][j-1] or table[i-1][j] (whichever is minimum) 
// table[i-1][j-1] => table[i][j] ==> this path represents editing of chars if needed
// table[i-1][j] => table[i][j] ==> This path represents addition of char in second string (or removing a char in first one)
// table[i][j-1] => table[i][j] ==> This path represents addition of char in first string (or removing a char in second one)

int distance(const string &str1, const string &str2) {

    table[0][0] = 0; // 
    for(int i=0; i<=str1.length(); i++) { // ith row in table represents i-1th char in string
        table[i][0] = i; // cost of adding a char in first str (or removing in second string) is 1 (may be different in a problem)
    }
    for(int j=0; j<=str2.length() + 1; j++) { // jth col in table represents j-1th char in string
        table[0][j] = j; // cost of adding a char in second str (or removing in first string) is 1 (may be different in a problem)
    }
    for (int i=1; i<=str1.length(); i++) {
        for (int j=1; j<=str2.length(); j++) {
            table[i][j] = min( min(table[i-1][j-1],table[i-1][j]), table[i][j-1]) + ((str1[i-1] == str2[j-1])?0:1); 
            // ((str1[i-1] == str2[j-1])?0:1) => assuming cost of editing a char is 1, which may be different in another problem
        }
    }

    return table[str1.length()][str2.length()];

}

int main() {
    string tcs[][2] = {
        {"devendra", "dAvendra"}, // 1
        {"evendra", "devendra"}, // 1
        {"devndra", "devendra"}, // 1
        {"devendra", "dAvAndra"}, // 2
        {"devendra", "dddddddd"}, // 6
        {"devendra", ""}, // 8
        {"", "devendra"}, // 8
        {"devendra", "deve"} // 4
    };
    for (auto a: tcs)
        cout << "Distance between \"" <<a[0] << "\" and \"" << a[1] << "\" :" << distance(a[0], a[1]) <<  endl; 

    return 0;
}