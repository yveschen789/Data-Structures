// Query.h
// purpose: header file for Query class
// uses: classes, functions, pointers, private, public
// name: Yves Chen
// date: 4/19/19

#ifndef QUERY_H
#define QUERY_H

#include "Index.h"

class Query{

public:

    //private variable
    string filename;

    //called by main to find query at indexed location
    void find(wordStruct *&hashTable, string query, bool isCase);
    
    //sets filename
    void setFileName(string output);

private:
    
    //helper function to find (depending on caseSensitive) and call printquery
    void goDeeper(vector <wordInfo> &info, string query, bool isCase);
    
    //opens file, searches, and outputs the path, line num, and the string line
    void printQuery(vector<pathInfo> &location);

};

#endif