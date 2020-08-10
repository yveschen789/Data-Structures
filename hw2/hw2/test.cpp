#include "LinkedList.h"
#include <iostream>
#include <string>

using namespace std;

// Input and output files
const string STATIONS_FILE = "glx.txt";
const string OUTPUT_ONE = "test.txt";
const string OUTPUT_TWO = "remove_some.txt";


//Constants
const int FAIL = -1;
const int NUM_REMOVE = 10;

int main () {
 //testing functions
    Station s1("yves", true);
    Station s2("Li Hui", false);
    Station s3("Russell", true);
    Station s4;

    LinkedList stations;
        stations.insertStation(s1);
        stations.insertStation(s2);

        stations.insertStation(s3);
        cout << "im here 3\n";
        stations.removeStation(s2);
    ofstream outfile;
    outfile.open(OUTPUT_ONE.c_str());
    cout << "Im here 2\n";
    stations.print(outfile);
    stations.makeEmpty();




	return 0;
}