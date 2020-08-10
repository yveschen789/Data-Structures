// testMain.cpp
// purpose: client file that calls to index and instantiates query
// uses: classes, hashtables, functions, loops, file IO, recursion, big 3, 
// pointers, cin cout, other classes
// name: Yves Chen
// date: 4/19/19

#include <iostream>
#include "Index.h"
#include "Query.h"

using namespace std;

// first step in finding query, checks if its a command or query word
void inputcmd(string one);

// called when user searches for word and will start query request
void search(string query, bool isCase);


Index theIndex;
Query theQuery;
bool userQuit;

int main(int argc, char* argv[]){

    if (argc != 3){
        cerr << "./gerp input_directory output_directory" << endl;
        return -1;
    }
    userQuit = true;
    
    theIndex.run(argv[1]);

    theQuery.setFileName(argv[2]);

    string prefix;

    while (!cin.eof() and userQuit){
    
        cout << "Query? " << endl;
        cin >> prefix;
        
        inputcmd(prefix);

    }
    
    cout << "Goodbye! Thank you and have a nice day." << endl;

    return 0;

}

//input: string
//output: nothing
//purpose: takes user input and checks what the user wants and calls functions
//depending on the request
void inputcmd(string one){
    
    if (one == "i" or one == "insensitive"){
        string request;
        cin >> request;
        search(request, true);
    }
    
    else if (one == "q" or one == "quit"){
        userQuit = false;
    }
    
    else if (one == "f"){
        string request;
        cin >> request;
        theQuery.setFileName(request);
    }
    
    else search(one, false);
}

//input: string and bool case
//output: calls find in Query class
//purpose: takes the query and converts it to an index and passes the hash
//table at that index (wordStruct) and the bool to call Query function
void search(string query, bool isCase){
    
    query = theIndex.sanitizeWord(query);
    
    string temp = query;
        
    for (unsigned long i = 0; i < temp.length(); i++){
        temp[i] = tolower(temp[i]); //lowercase query
    }
        
    string key = temp;
        
    size_t index = theIndex.hashKey(key); //finds index
        
    if (theIndex.returnTable()[index] != NULL){
        wordStruct *temp = new wordStruct; //create wordStruct pointer and 
        temp = theIndex.returnTable()[index]; //points to hashtable from index
        theQuery.find(temp, query, isCase);
    }
        
    else{
    ofstream outfile;
    outfile.open(theQuery.filename, ofstream::app);
    if (!outfile.is_open()){
        cerr << "Could not open output file" << endl;
        exit(1);
    }

        outfile << "query not found" << endl;

        outfile.close();
    }

}