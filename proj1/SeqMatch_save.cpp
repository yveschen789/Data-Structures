#include <iostream>
#include <fstream>
#include <string>
#include "Trie.h"
using namespace std;

Trie trieClass;

void SwitchCmd(string input1, ifstream &infile);

int main(int argc, char* argv[]){

argc = 3;
trieClass.SetFileName(argv[2]);
ifstream infile;
infile.open(argv[1]);
if (!infile.is_open()){
	cerr << "ERROR: File cannot be opened1" << endl;
	return -1;
}
string first;
while (true){
	infile >> first;
	if (infile.eof())
		break;
	SwitchCmd(first, infile);
}

infile.close();




	return 0;
}

void SwitchCmd(string input1, ifstream &infile){
	string input2;
		if(input1 == "i"){
			infile >> input2;
			trieClass.insert(input2);
		}
		if(input1 == "q"){
			infile >> input2;
			trieClass.queryRequest(input2);
		}
		if(input1 == "pq"){
			infile >> input2;
			trieClass.prefixQuery(input2);
		}
		if(input1 == "r"){
			infile >> input2;
			trieClass.remove(input2);
		}
		if(input1 == "n"){
			trieClass.numNodes();
		}
		if (input1 == "p"){
			trieClass.print();
		}
		if (input1 == "d"){
			trieClass.deleteAll();
		}
		if(input1 == "f"){
			infile >> input2;
			trieClass.SetFileName(input2);
		}
	
}