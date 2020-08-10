//Name: Yves Chen
//Due Date: 3/13/19
//Assignment: Proj 1 Tries
//Description: test driver that uses public functions of the Trie class to
//insert/remove/deleteall/setfiles/numnodes, queryRequest, and prefixquery
//Uses: classes, cout, argc, functions, comments

#include <iostream>
#include <fstream>
#include <string>
#include "Trie.h"
using namespace std;



int main(int argc, char* argv[]){

	Trie test;
	argc = 2;

    cout << "Setting output file of testing as: " << argv[1] << endl;
	test.SetFileName(argv[1]);

////////////////////////////////////////////////////////////////////////////

	cout << "Testing Insert Function" << endl;
	test.insert("GTTAT");	
	test.insert("ATTGC");
	test.insert("ATTAT");
	
    cout << "Testing Node Count function" << endl;
	test.numNodes();
	cout << "Should return 12" << endl;
	
    test.insert("CCGTATG");
	test.insert("GTTAC");
    test.insert("CATG");
    test.insert("GTAAG");
    test.insert("GTTAC");  //already inserted
	test.insert("GTAGCC"); //these two cases are extensions of already inserted
	test.insert("GTAGCCC"); //sequences
	cout << "Done testing insert: Now Printing to Outfile" << endl;
	test.print();
	
////////////////////////////////////////////////////////////////////////////

	cout << "testing prefixQuery" << endl;
	test.prefixQuery("GTA"); //should have two matches
	test.prefixQuery("GTACG"); //should return no match found
	test.prefixQuery("AT"); 
	cout << "finished" << endl;

//////////////////////////////////////////////////////////////////////////// 
    
	cout << "Testing Remove Function" << endl;
	test.remove("CATG");
	test.remove("CATG"); //should return no match found
	test.remove("GTAGCCC");
	test.remove("ATTGC");
	cout << "done removing" << endl;
	test.insert("TTAG"); //show that you can insert after removing
	test.print();

////////////////////////////////////////////////////////////////////////////

    cout << "Testing deleteAll function -- should return 0 node count" << endl;
    test.deleteAll();

////////////////////////////////////////////////////////////////////////////

	cout << "Testing query request" << endl;

    cout << "preliminary inserts" << endl;
    test.insert("TAGTAGT");
    test.insert("TACAGGT");
    test.insert("ACCATAC");
    test.insert("ACAT");
    test.insert("TAC");
    cout << "done inserting" << endl;

    test.queryRequest("ACGT");  //both should match with ACAT
    test.queryRequest("ACA");   //first 50% and second 75%
    test.queryRequest("TACA");
    test.queryRequest("CGT"); //should return 0% match
    test.queryRequest("TAGTA");
    cout << "done testing: destructor should run" << endl;
    
	 return 0;
}