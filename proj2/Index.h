// Index.h
// purpose: header file for Index class
// uses: classes, functions, pointers, structs, private, public
// name: Yves Chen
// date: 4/19/19

#ifndef INDEX_H
#define INDEX_H

#include <vector>
#include <functional>
#include <sstream>
#include <string>
#include <fstream>
#include "FSTree.h" 
#include <cmath>

using namespace std;


// second auxiluary struct that stores the path and line num
    struct pathInfo{
    string path;
    int lineNum;
    pathInfo(string path_,int lineNum_){
        path = path_;
        lineNum = lineNum_;
    };
};

//first auxiluary struct that stores the original word and vector of paths
struct wordInfo{
    string OGword;
    vector<pathInfo> path;
    wordInfo(string OGword_, pathInfo path_){
        OGword = OGword_;
        path.push_back(path_);
    };
};

//struct that is a linked list when indexed. contains the key and a vector
//of auxiluary structs to store word data
struct wordStruct{
    string key;
    vector<wordInfo> info;
    wordStruct * next;
    wordStruct(){

    };
    wordStruct(string key_, wordInfo info_){
        key = key_;
        info.push_back(info_);
        next = NULL;
    };
    wordStruct (wordStruct *node){
        key = node->key;
        info = node->info;
        next = NULL;
    };
};

class Index
{

private:
    
    //private variables

    wordStruct **hashTable;
    int currTableSize;
    int entries;
    static const int INITIAL_TABLE_SIZE = 200;

    //hash functions

    void expand();
    void expandHelper(wordStruct * node, wordStruct **&newTable);
    void clearTable(int size);
    void clearStruct(wordStruct * node);

    //indexing

    void FSTreeTraversal(DirNode * node, string directory);
    void intakeFile(string path);
    void processLine(string filepath, istream& fullLine, int line);

    //adding to hash

    void addWord(wordStruct *&hashTable, string key, wordInfo info, 
        wordStruct *&prev);
    void addWord(wordStruct *&hashTable, string key, wordInfo info);
    void saveSpace(wordStruct *&hashTable, wordInfo info);

public:
    
    //constructor and destructor

    Index();
    ~Index();

    //called by main to start indexing process

    void run(string directory);

    // Helper Functions
    wordStruct **&returnTable();
    size_t hashKey(string key);
    string sanitizeWord(string input);

};

#endif