//Name: Yves Chen
//Due Date: 3/13/19
//Assignment: Proj 1 Tries
//Description: This is the implementation file that manages and outputs data
//structure contents, stores, deletes, and searches. public functions are
//called by SeqMatch.cpp
//Uses: functions, variables, conditionals, loops, pointers, recursion, file IO,
//structs, tries, data abstraction

#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <stdio.h> 
#include <stdlib.h>
#include <cmath> 

#include "Trie.h"

using namespace std;

//default constructor -- sets root to a valid Node with all pointers NULL
// counter, filename, match, and matchdone are all initialized here
Trie::Trie(){
	root = newNode();
	counter = 0;
	filename = "";
	match = "";
	matchDone = true;
}

//default destructor -- deletes everything from root and frees memory
Trie::~Trie(){
	deleteAll(root);
}

// returns a Node that has everything initialized to NULL and bool as false
Node *Trie::newNode(){
	Node *temp = new Node;
	temp->IsEnd = false;
	for (int i = 0; i < 4; i++){
		temp->next[i] = NULL;  //initializes array of pointers as NULL
	}
	return temp;
}

// first reopens outfile and calls private insert function with root as param
// and then outputs depending on return value from private insert function
void Trie::insert(string sequence){
	ofstream outfile;
	outfile.open(filename, ofstream::app);
	if (!outfile.is_open()){
		cerr << "ERROR: File cannot be opened" << endl;
		exit(1);
	}
	 if (insert(sequence, root))
	 	outfile << sequence << " inserted" << endl;
	 else
	 	outfile << sequence << " was previously inserted" << endl;
	 outfile.close(); //closes outfile to prevent memory leaks
}


bool Trie::insert(string sequence, Node* curr){
	if (sequence == ""){ //once sequence is fully eaten
		if (curr->IsEnd)
			return false;
		curr->IsEnd = true;
		return true;
	}
	int path = indexChar(sequence.at(0)); //finds path of next Node
	if (curr->next[path] == NULL){
		curr->next[path] = newNode(); //creates new node if NULL path
	}
	return insert(sequence.erase(0,1), curr->next[path]); //recurses
}

//simple switch function that takes char and returns int (alphapetic heirarchy)
int Trie::indexChar(char type){
	switch (type){
	case 'A':
		return 0;
	case 'C':
		return 1;
	case 'G':
		return 2;
	case 'T':
		return 3;
	}
	return -1; //error in this case
}

//simple function that takes int and returns char (opposite of indexChar)
char Trie::charIndex(int index){
	if (index == 0)
		return 'A';
	if (index == 1)
		return 'C';
	if (index == 2)
		return 'G';
	if (index == 3)
		return 'T';
	return 'X'; //error in this case
}

//public print function that opens outfile (to write output)
//and calls private print function
void Trie::print(){
	ofstream outfile;
	outfile.open(filename, ofstream::app);
	if (!outfile.is_open()){
		cerr << "ERROR: File cannot be opened" << endl;
		exit(1);
	}
	print(root, NULL, "", outfile);
	outfile.close();
}

//saves the char by comparing parent and curr nodes' paths and when the end of
//word is found, funtion outfiles the string, only returning when no more 
//children
void Trie::print(Node * curr, Node*parent, string str, ofstream &outfile){
	if (curr == NULL)
		return; //when pointer not valid while recursing and error case	
	if (curr != NULL and parent != NULL){
		for (int i = 0; i < 4; i++){
			if (parent->next[i] == curr){ //finds the index of pointer
				str +=charIndex(i); //concatonates the char to string
			}
		}
	}
	if (curr->IsEnd == true){ //sequence to print found case
		outfile << str;
		outfile << endl;
		if (hasNoChildren(curr)){ //returns if no more children, else continue
			return;
		}
	}
	for (int i = 0; i < 4; i++){
		print (curr->next[i], curr, str, outfile); //recursive case
	}
}

//public remove function that opens outfile to write to and calls private
//remove function and then remove helper function the length of string times
void Trie::remove(string sequence){
	ofstream outfile;
	outfile.open(filename, ofstream::app);
	if (!outfile.is_open()){
		cerr << "ERROR: File cannot be opened" << endl;
		exit(1);
	}
	if (remove(sequence, root)) //calls private function and outputs
		outfile << sequence << " removed" << endl;
	else 
		outfile << sequence << ": No match found" << endl;
	int counter = sequence.length(); //iterate the length of string
	for (int i = 0; i < counter; i++){
		removeUnneeded(root, NULL, sequence, 0); //deletes useless nodes
		sequence.erase(sequence.cend()-1, sequence.cend()); //cuts one from end
	}
	outfile.close();
}

//private remove function that returns a bool. recurses until sequence is over
//and sets the bool of node to false to delete word
bool Trie::remove(string sequence, Node *curr){
    if (sequence == ""){ //end case
        if (curr->IsEnd){
            curr->IsEnd = false;
            return true;
        }
        return false; //if there is no end of sequence at that node
    }
    int path = indexChar(sequence.at(0)); //obtain path int
    if (curr->next[path] != NULL)
            return remove(sequence.erase(0,1), curr->next[path]); //recurses
    else
    	return false;
}

//called by public remove function length of sequence times and removes 
// unneeded nodes (frees) and sets parent pointer to null too
void Trie::removeUnneeded(Node *curr, Node *parent, string sequence, int ind){
	if (isEmpty(curr) and curr != root){ //frees not thats empty
			delete curr;
			curr = NULL;
			parent->next[ind] = NULL; //parent points to null
			return;
		}
	if (sequence == "") //means there was no empty nodes
		return;	
	int path = indexChar(sequence.at(0));
		if (curr->next[path] != NULL)
			removeUnneeded(curr->next[path], curr, sequence.erase(0,1), path);
	       //recursive case
}

//simple function that returns a bool depending on if the node parameter has no
//children and if it is not the end of a DNA sequence
bool Trie::isEmpty(Node *curr){
    if (curr == NULL)
    	return false;
    for (int i = 0; i < 4; i++){
        if (curr->next[i] != NULL or curr->IsEnd == true)
            return false;
    }
    return true;
}

//simple function that returns a bool depending on if the node parameter has no
//children but not if it is not the end of a DNA sequence
bool Trie::hasNoChildren(Node *curr){
    for (int i = 0; i < 4; i++){
        if (curr->next[i] != NULL)
            return false;
    }
    return true;

}

//simple function that returns a bool depending on if the node parameter has 
//more than one children but not if it is not the end of a DNA sequence
bool Trie::hasOnePlusChildren(Node *curr){
	int counter = 0;
	for (int i = 0; i < 4; i++){
        if (curr->next[i] != NULL)
            counter++;
    }
    if (counter > 1)
	    return true;
	return false;
}

//public function that calls delete all from root. reinitializes root after
//calling private delete function and then calls numnodes function
void Trie::deleteAll(){
    deleteAll(root);
    root = newNode();
    numNodes();
}

//private delete all function that takes a node, usually root and deletes all
//children
void Trie::deleteAll(Node *curr){
    if (curr == NULL) //empty case, just returns to recursive case
        return;
    for (int i = 0; i < 4; i++){
            deleteAll(curr->next[i]); //recursive case
    }
            delete curr; //frees memory
            curr = NULL;
}

//public node count function that calls private node function and outfiles
//counter
void Trie::numNodes(){
	ofstream outfile;
	outfile.open(filename, ofstream::app); // opens outfile
	if (!outfile.is_open()){
		cerr << "ERROR: File cannot be opened" << endl;
		exit(1);
	}
	numNodes(root); //calls private function with root
	outfile << "There are " << counter - 1 << " nodes in the database" << endl;
	counter = 0; //resets counter since returning numNodes recursively was too
                 //difficult so I set a variable in class ot be updated
	outfile.close();
}

//private node count that takes a root node and increments private var counter
//every time the function recurses and finds a node
void Trie::numNodes(Node *curr){
	if (curr == NULL){
		return;
	}
	if (curr != NULL){
		counter++; //iterates
	}
	for (int i = 0; i < 4; i++){
		numNodes(curr->next[i]); //recursive case
	}
}

//public function that takes in string and calls private function after opening
//outfile and passing it to private functuon as param
void Trie::prefixQuery(string sequence){
	ofstream outfile;
	outfile.open(filename, ofstream::app);
	if (!outfile.is_open()){
		cerr << "ERROR: File cannot be opened" << endl;
		exit(1);
	}
	string temp = ""; //temporary placeholder paramenter
	prefixQuery(root, sequence, temp, outfile, sequence);
	outfile.close();
}

// takes a current node, the sequence that loses the first letter every 
//recursive case, a fullSeq param that adds the first letter lost, an ostream
//paramenter and the original sequence string that does not change for
//recursive cases. The function recurses and then calls print if the sequence
//is at least somewhere fully in the database
void Trie::prefixQuery(Node *curr, string sequence, string fullSeq, ofstream 
                       &outfile, string original){
	if (curr == NULL) //error case
		return;
	if (sequence == ""){ //sequence successfully taken in
		print(curr, NULL, fullSeq, outfile); //gives param of lost letters so 
		return;                              //print works properly
	}

	int path = indexChar(sequence.at(0)); //finds index based on char
		if (curr->next[path] != NULL){
			string temp = sequence.substr(0,1); //makes string with 1st letter
			prefixQuery(curr->next[path], sequence.substr(1,sequence.length()),
                        fullSeq.append(temp), outfile, original);
		    //recursive call that passes curr next, the seq without first 
            //letter, the seq with letter lost, outfile, and original string
        }
		else{ //case where we can not find sequence in database matching
		outfile << original << ": No match found" << endl;
			return;
		}

}

//function that sets filename, a private string var in the class as the name of
//the file to outfile too (param)
void Trie::SetFileName(string output){
	bool firstOpen = false;
	if (filename != ""){ //if filename is first opened firstopen stays false
		firstOpen = true;
	}
	filename = output; //sets filename to output
	ofstream outfile;
	outfile.open(filename, ofstream::app);
	if (!outfile.is_open()){
		cerr << "ERROR: File cannot be opened" << endl;
		exit(1);
	}
	if (firstOpen) // when output has been changed by client
		outfile << "Output file has been changed to " << output << endl;
	outfile.close();
}

//public queryRequest that takes in the sequence from user and calls private
//query request, calculates the percentage and outfiles the result
void Trie::queryRequest(string sequence){
	ofstream outfile; //opens outfile
	outfile.open(filename, ofstream::app);
	if (!outfile.is_open()){
		cerr << "ERROR: File cannot be opened" << endl;
		exit(1);
	}
	
    queryRequest(root, sequence, ""); //calls private function

	float i; 
	int length = min(sequence.length(), match.length());
	for (i = 0; i < length; i++) //iterate to find the length of matchin prefix
		if (sequence.at(i) != match.at(i)) 
			break;
	float denominator = max(match.length(), sequence.length());
	float hunni = 100;
	float percent = (i* hunni / denominator) ; //calculates percent
	if (i == 0) //case where no match
		outfile << sequence << ": No match found" << endl;
	else
		outfile << "Match found: " << match << " " << round(percent) << "%" 
        << endl;

	match = ""; //resets match and matchdone since the functions called do not
	matchDone = true; //actually return, just change the value of private var
	outfile.close();
}

//private queryRequest function that recurses
void Trie::queryRequest(Node* curr, string sequence, string prefix){
	if (curr == NULL) //error case
		return;
	if (sequence == ""){ //case where sequence is fully eaten  and matchfinder
		if (prefix != "")//gets called
		matchFinder(curr, NULL, prefix);
		return;
    }

	int path = indexChar(sequence.at(0)); //finds path based on char
		if (curr->next[path] != NULL){
			string temp = sequence.substr(0,1); //string of lost character
			queryRequest(curr->next[path], sequence.substr(1,sequence.length())
                         , prefix.append(temp));
		      // recursive case where there is a path and the params are the
              // next node, sequence w/o first letter and string with first
              // letter appened
        }
		else{
			if (prefix != "")
		 	matchFinder(curr, NULL, prefix); //sequence not fully eaten but
		 	return;                       //matchfinder gets called with prefix
        }
		
}

// helper function called by queryRequest to set private var match to the DNA
// sequence that most closely resembles the sequence in mind
void Trie::matchFinder(Node * curr, Node * parent, string str){
	if (curr == NULL) //parent pointer was NULL or error case
		return;	
	if (curr != NULL and parent != NULL){
		for (int i = 0; i < 4; i++){
			if (parent->next[i] == curr) //find index of parent pointer to curr
				str +=charIndex(i); //str gets new char appended
		}
	}
	if (curr->IsEnd == true){
		if(matchDone or str.length() < match.length()) //once string is found
		match = str;          //NOTE: if a new string is shorter, it overwrites
		matchDone = false; //now new strings can not overwrite
		return;
		}
	for (int i = 0; i < 4; i++){
		matchFinder(curr->next[i], curr, str); //recursive case
	}
}