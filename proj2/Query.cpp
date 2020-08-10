// Query.cpp
// purpose: implementation file that takes a wordStruct from index of hash
// -table and then queries a string, finding its location and printing it
// uses: classes, hashtables, functions, loops, file IO, recursion, big 3, 
// pointers
// name: Yves Chen
// date: 4/19/19

#include <iostream>
#include "Query.h"

//input: a wordstruct, query string, and bool value
//output: calls goDeeper
//purpose: finds which node of the linked list of wordStructs has
// the right key and calls goDeeper()
void Query::find(wordStruct *&hashTable, string query, bool isCase){
    
    //opens output file in case need for outfiling query not found    
    ofstream outfile;
    outfile.open(filename, ofstream::app);
    if (!outfile.is_open()){
        cerr << "Could not open output file" << endl;
        exit(1);
    }


        bool good = false;
        string temp = query;
        for (unsigned long i = 0; i < temp.length(); i++){
                temp[i] = tolower(temp[i]); //converts query to lowercase
        }

        while (hashTable != NULL){
            
            if (temp == hashTable->key){ //checks for match
                goDeeper(hashTable->info, query, isCase);
                good = true; 
            }
            
            hashTable = hashTable->next; //goes to next node in wordStruct list
        }

        if (!good) //if unable to find key
        outfile << "query not found" << endl;

    outfile.close();
    
}

//input: reference to wordinfo vector, query string and the case bool
//output: calls print Query
//purpose: has two conditionals depending on the case sensitive bool. 
//program will iterate through the wordInfo vector to find matching words
//and prints
void Query::goDeeper(vector <wordInfo> &info, string query, bool isCase){
    
    ofstream outfile;
    outfile.open(filename, ofstream::app); //opens file incase need to write
    if (!outfile.is_open()){               // to output
        cerr << "Could not open output file" << endl;
        exit(1);
    }

    if (isCase){
        for (unsigned long i = 0; i < info.size(); i++)
            printQuery(info[i].path); //freely prints
    }
    if (!isCase){
        bool isGood = false;
        for (unsigned long i = 0; i < info.size(); i++)
            if (query == info[i].OGword){ //checks that its exact word
                isGood = true;
                printQuery(info[i].path);
            }
        if (! isGood) //only if the case specific word is not found
            outfile << "query not found" << endl;
    }

    outfile.close(); 

}

//input: vector of pathInfo
//output: prints
//purpose: opens file at location path and loops to specific line and then
//outputs the result into output file in specified format
void Query::printQuery(vector<pathInfo> &location){

    ofstream outfile;
    outfile.open(filename, ofstream::app); ///opens file to write to
    if (!outfile.is_open()){
        cerr << "ERROR: File cannot be opened" << endl;
        exit(1);
    }

    ifstream file;
    string line;
    size_t counter;
    for (counter = 0; counter < location.size(); counter++){
        string filepath = location[counter].path;
        int linenumber = location[counter].lineNum;

        file.open(filepath); //opens directory based on path parameter

        for (int i = 1; i <= linenumber; i++)
            getline (file, line); //iterate until line var is the correct
                                  // queryed line
        file.close();

        if (line != ""){
            outfile << filepath << ":" << linenumber << ": " << line << endl;
        }
    }
    outfile.close();
}

///input: string text file
//output: nothing
//purpose: used by main to change and specify the correct file to output to
void Query::setFileName(string output){
    bool firstOpen = false;
    if (filename != ""){ //if filename is first opened firstopen stays false
        firstOpen = true;
    }
    filename = output; //sets filename to output
    ofstream outfile;
    outfile.open(filename, ofstream::app);
    if (!outfile.is_open()){
        cerr << "Could not open output file" << endl;
        exit(1);
    }
    if (firstOpen) // when output has been changed by client
        outfile << "Output file has been changed to " << output << endl;
    outfile.close();
}