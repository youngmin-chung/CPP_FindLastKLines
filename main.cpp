#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>
#include <numeric>
#include <cmath>
#include <sstream>
#include <fstream>

using namespace std;

// declare func
string getLastLine(std::string new_filename);
void printLast10Lines(string fileName);
int main()
{
    cout << "*** Find last line ***\n" << endl;
    getLastLine("test.txt");
    //printLast10Lines("test.txt");
    return 0;
}

// func here
string getLastLine(string new_filename){
    string filename = "test.txt";
    string txtFromFile = "";
    ifstream readFromFile;

    readFromFile.open(filename);

    if(readFromFile.is_open()) {
        cout << "Original text: \n";
        while(readFromFile.good()){
            getline(readFromFile, txtFromFile);
            cout << txtFromFile << "\n";
        }
        readFromFile.seekg(-1,ios_base::end);                // go to one spot before the EOF

        bool keepLooping = true;
        while(keepLooping) {
            char ch;
            readFromFile.get(ch);                            // Get current byte's data

            if((int)readFromFile.tellg() <= 1) {             // If the data was at or before the 0th byte
                readFromFile.seekg(0);                       // The first line is the last line
                keepLooping = false;                         // So stop there
            }
            else if(ch == '\n') {                            // If the data was a newline
                keepLooping = false;                         // Stop at the current position.
            }
            else {                                           // If the data was neither a newline nor at the 0 byte
                readFromFile.seekg(-2,ios_base::cur);        // Move to the front of that data, then to the front of the data before it
            }
        }

        string lastLine;
        getline(readFromFile,lastLine);                      // Read the current line
        cout << "\nResult: " << lastLine << '\n';              // Display it

        readFromFile.close();
    }
}

// print last K lines
void printLast10Lines(string fileName){
    const int K = 10;
    ifstream file (fileName);
    string L[K];
    int size = 0;

    // read file line by line into circular array
    // peek() so an EOF following a line ending is not considered a separate line
    while (file.peek() != EOF){
        getline(file, L[size % K]);
        size++;
    }

    // compute start of circular array, and the size of it
    int start = size > K ? (size % K) : 0;
    int count = min(K, size);

    // print elements in the order they were read
    for (int i = 0; i < count; i++){
        cout << L[(start + i) % K] << endl;
    }
}
