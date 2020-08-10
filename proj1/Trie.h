//Name: Yves Chen
//Due Date: 3/13/2019
//Assignment: Proj 1 Tries
//Description: This is the header file for the Tries class that includes all
//implementations for storing DNA sequences in a data structure and all sorts
//of requests and removals
//Uses: classes, function declarations, struct, pointers, bools, public/private
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#ifndef _Trie_H_
#define _Trie_H_

//the data type of each node
struct Node{
	Node *next[4]; //points to four nodes
	bool IsEnd; //bool to show if end of sequence
};

class Trie{
	public:
		Trie(); //default constructor
		~Trie(); //default destructor
		//called by main to insert DNA sequence and return if insert worked
		void insert(string sequence); 
		//called by main to print to outfile
		void print();
		//called by main to remove the string paramenter
		void remove(string sequence);
		//called by main and destructor to free all nodes
		void deleteAll();
		//called by main to outfil number of nodes
		void numNodes();
		// public function that outfiles all names of sequences that match
		void prefixQuery(string sequence);
		// called by main first and then upon request to set outfile location
		void SetFileName(string output);
		// public function that oufiles a sequence most matching param w/ %
		void queryRequest(string sequence);


	private:
		Node* root; //root of trie
		int counter; //counter that stores nodecount
		string filename; //string that is set to the name of outfile
		string match; //string that stores the matched seq in query requests
		bool matchDone = true; //bool to manage the final seq matched in query
		bool insert(string sequence, Node *curr);
		bool remove(string sequence, Node *curr);
		int indexChar(char type);
		char charIndex(int index);
		Node* newNode(); // newnode function
		void print(Node *curr, Node* parent, string str, ofstream &outfile);
		bool isEmpty(Node *curr);
		void removeUnneeded(Node *curr, Node *parent, string sequence, int ind);
		void deleteAll(Node *curr);
		bool hasNoChildren(Node *curr);
		void numNodes(Node *curr);
		bool hasOnePlusChildren(Node *curr);
		void prefixQuery(Node *curr, string sequence, string fullSeq, 
						 ofstream &outfile, string original);
		void queryRequest(Node *curr, string sequence, string prefix);
		void matchFinder (Node *curr, Node *parent, string str);



};

#endif