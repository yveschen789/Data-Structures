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

Trie::Trie(){
	root = newNode();
	counter = 0;
	filename = "";
	match = "";
	matchDone = true;
}

Trie::~Trie(){
	deleteAll(root);
}

Node *Trie::newNode(){
	Node *temp = new Node;
	temp->IsEnd = false;
	for (int i = 0; i < 4; i++){
		temp->next[i] = NULL; 
	}
	return temp;
}

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

}

bool Trie::insert(string sequence, Node* curr){
	if (sequence == ""){
		if (curr->IsEnd)
			return false;
		curr->IsEnd = true;
		return true;
	}
	int path = indexChar(sequence.at(0));
	if (curr->next[path] == NULL){
		curr->next[path] = newNode(); 
	}
	return insert(sequence.erase(0,1), curr->next[path]);

}

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

}

char Trie::charIndex(int index){
	if (index == 0)
		return 'A';
	if (index == 1)
		return 'C';
	if (index == 2)
		return 'G';
	if (index == 3)
		return 'T';
}



void Trie::print(){
	ofstream outfile;
	outfile.open(filename, ofstream::app);
	if (!outfile.is_open()){
		cerr << "ERROR: File cannot be opened" << endl;
		exit(1);
	}
	print(root, NULL, "", outfile);
}

void Trie::print(Node * curr, Node*parent, string str, ofstream &outfile){
	if (curr == NULL)
		return;
	
	if (curr != NULL and parent != NULL){
		for (int i = 0; i < 4; i++){
			if (parent->next[i] == curr){
				str +=charIndex(i); 
			}
		}
	}
	if (curr->IsEnd == true){
		outfile << str;
		outfile << endl;
		if (hasNoChildren(curr)){
			return;
		}
	}
	for (int i = 0; i < 4; i++){
		print (curr->next[i], curr, str, outfile);
	}
}

void Trie::remove(string sequence){
	ofstream outfile;
	outfile.open(filename, ofstream::app);
	if (!outfile.is_open()){
		cerr << "ERROR: File cannot be opened" << endl;
		exit(1);
	}
	if (remove(sequence, root))
		outfile << sequence << " removed" << endl;
	else 
		outfile << sequence << ": No match found" << endl;
	int counter = sequence.length();
	for (int i = 0; i < counter; i++){
		removeUnneeded(root, NULL, sequence, 0);
		//cout << sequence.length() << endl;
		sequence.erase(sequence.cend()-1, sequence.cend());
		//cout << sequence.length() << endl;
		//cout << sequence << endl;
	}
}

bool Trie::remove(string sequence, Node *curr){
    if (sequence == ""){
        if (curr->IsEnd){
            curr->IsEnd = false;
            return true;
        }
        return false;
    }
    int path = indexChar(sequence.at(0));    	
    if (curr->next[path] != NULL)
            return remove(sequence.erase(0,1), curr->next[path]);
    else
    	return false;
}

void Trie::removeUnneeded(Node *curr, Node *parent, string sequence, int ind){
	if (isEmpty(curr) and curr != root){
			delete curr;
			curr = NULL;
			parent->next[ind] = NULL;
			return;
		}
	if (sequence == "")
		return;	
	int path = indexChar(sequence.at(0));
		if (curr->next[path] != NULL)
			removeUnneeded(curr->next[path], curr, sequence.erase(0,1), path);
	
}

bool Trie::isEmpty(Node *curr){
    if (curr == NULL)
    	return false;
    for (int i = 0; i < 4; i++){
        if (curr->next[i] != NULL or curr->IsEnd == true)
            return false;
    }
    return true;

}

bool Trie::hasNoChildren(Node *curr){
    for (int i = 0; i < 4; i++){
        if (curr->next[i] != NULL)
            return false;
    }
    return true;

}

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


void Trie::deleteAll(){
    deleteAll(root);
    root = newNode();
    numNodes();
}

void Trie::deleteAll(Node *curr){
    if (curr == NULL)
        return;
    for (int i = 0; i < 4; i++){
            deleteAll(curr->next[i]);

    }
            delete curr;
            curr = NULL;
    
}

void Trie::numNodes(){
	ofstream outfile;
	outfile.open(filename, ofstream::app);
	if (!outfile.is_open()){
		cerr << "ERROR: File cannot be opened" << endl;
		exit(1);
	}
	numNodes(root);
	outfile << "There are " << counter - 1 << " nodes in the database" << endl;
	counter = 0;
}

void Trie::numNodes(Node *curr){
	if (curr == NULL){
		return;
	}
	if (curr != NULL){
		counter++;
	}
	for (int i = 0; i < 4; i++){
		numNodes(curr->next[i]);
	}
}

void Trie::prefixQuery(string sequence){
	ofstream outfile;
	outfile.open(filename, ofstream::app);
	if (!outfile.is_open()){
		cerr << "ERROR: File cannot be opened" << endl;
		exit(1);
	}

	int path = indexChar(sequence.at(0));
	string temp = "";
	prefixQuery(root, sequence, temp, outfile, sequence);
		
}

void Trie::prefixQuery(Node *curr, string sequence, string fullSeq, ofstream &outfile, string original){
	if (curr == NULL)
		return;
	if (sequence == ""){
		print(curr, NULL, fullSeq, outfile);
		return;
	}

	int path = indexChar(sequence.at(0));
		if (curr->next[path] != NULL){
			string temp = sequence.substr(0,1);
			prefixQuery(curr->next[path], sequence.substr(1,sequence.length()), fullSeq.append(temp), outfile, original);
		}
		else{
		outfile << original << ": No match found" << endl;
			return;
		}

}

void Trie::SetFileName(string output){
	bool firstOpen = false;
	if (filename != ""){
		firstOpen = true;
	}
	filename = output;
	ofstream outfile;
	outfile.open(filename, ofstream::app);
	if (!outfile.is_open()){
		cerr << "ERROR: File cannot be opened" << endl;
		exit(1);
	}
	if (firstOpen)
		outfile << "Output file has been changed to " << output << endl;
}

void Trie::queryRequest(string sequence){
	ofstream outfile;
	outfile.open(filename, ofstream::app);
	if (!outfile.is_open()){
		cerr << "ERROR: File cannot be opened" << endl;
		exit(1);
	}
	queryRequest(root, sequence, "");

	float i;
	int length = min(sequence.length(), match.length());
	for (i = 0; i < length; i++)
		if (sequence.at(i) != match.at(i))
			break;
	float denominator = max(match.length(), sequence.length());
	float hunni = 100;
	float percent = (i* hunni / denominator) ;
	if (i == 0)
		outfile << sequence << ": No match found" << endl;
	else
		outfile << "Match found: " << match << " " << round(percent) << "%" << endl;

	match = "";
	matchDone = true;

}

void Trie::queryRequest(Node* curr, string sequence, string prefix){
	if (curr == NULL)
		return;
	if (sequence == ""){
		if (prefix != "")
		matchFinder(curr, NULL, prefix);
		return;
	}

	int path = indexChar(sequence.at(0));
		if (curr->next[path] != NULL){
			string temp = sequence.substr(0,1);
			queryRequest(curr->next[path], sequence.substr(1,sequence.length()), prefix.append(temp));
		}
		else{
			if (prefix != "")
		 	matchFinder(curr, NULL, prefix);
		 	return;
		}
		
}

void Trie::matchFinder(Node * curr, Node * parent, string str){
	if (curr == NULL)
		return;
	
	if (curr != NULL and parent != NULL){
		for (int i = 0; i < 4; i++){
			if (parent->next[i] == curr){
				str +=charIndex(i); 
			}
		}
	}
	if (curr->IsEnd == true){
		if(matchDone or str.length() < match.length())
		match = str;
		matchDone = false;
		return;
		}
	for (int i = 0; i < 4; i++){
		matchFinder(curr->next[i], curr, str);
	}
}