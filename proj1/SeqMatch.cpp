//Name: Yves Chen
//Due Date: 3/13/2019
//Assignment: Proj 1 Tries
//Description: This is the main driver that takes inputs from an infile and
//turns them into commands to call functions in the Trie class
//Uses: file IO, functions, conditionals, loops

#include <iostream>
#include <fstream>
#include <string>
#include "Trie.h"
using namespace std;

//class declaration
Trie trieClass;

//function that takes first input and infile to find what second (paired)
//command asks and executes the class function call
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
while (true){ //where the commands are inputted and processed
	infile >> first; //first command
	if (infile.eof()) //when out of commands, loop ends
		break;
	SwitchCmd(first, infile); //called with first command and infile as params
}

infile.close(); //closes infile to prevent memory leaks

return 0;
}

//takes in the first command and infile and then depending on input, infiles
//second input and calls function with that second input as param unless it is
//a numnode or delete all function
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