// Index.cpp
// purpose: implementation file that opens files from root, traverses and 
// breaks everything down into the word and stores its necessary data in a 
// hashtable.
// uses: classes, hashtables, functions, loops, file IO, recursion, big 3, 
// pointers
// name: Yves Chen
// date: 4/19/19

#include <iostream>
#include "Index.h"

using namespace std;

//input: nothing
//output: nothing
//purpose: Initializes hashtable to size of initial table size and sets
//pointers at each index to null
Index::Index(){
    
    currTableSize = INITIAL_TABLE_SIZE;
    entries = 0;

    hashTable = new wordStruct *[currTableSize];
    
    for (int i = 0; i < currTableSize; i++){
        hashTable[i] = NULL;
    }
}

//input: nothing
//output: nothing
//purpose: calls clear table which will also clear the structs at each index
Index::~Index(){
    clearTable(currTableSize);
}

//input: string with directory name
//output: nothing
//purpose: called by main to initialize indexing
void Index::run(string directory){
    
    FSTree fileTree(directory); //FSTree builds the tree of files and subdirs
    
    DirNode * root = fileTree.getRoot();

    FSTreeTraversal(root, directory += "/");
}

//input: root node and the directory path
//output: recurses through tree
//purpose: recurses through tree and calls intake file for every file for
// further processing
void Index::FSTreeTraversal(DirNode * node, string directory){
    
    if (node == NULL) return;

    string TempFile;

    for (int i = 0; i < node->numFiles(); i ++ ){
        
        TempFile = directory + node->getFile(i);
        
        intakeFile(TempFile);
    
    //called occationally and expand when load is
    //above .7 but if not, its a simple return
    if (i % 10 == 0)
        expand();

    }

    


    for (int i = 0; i < node->numSubDirs(); i ++){        
        
        DirNode * tempNode = node->getSubDir(i);
        string dir = directory + (tempNode-> getName()) + "/";
        
        //recurses with updated dir path and new node
        FSTreeTraversal(tempNode, dir);
    }
}

//input: file path
//output: nothing
//purpose: opens the file and takes each line, recording the line num as well
//and then calls processline
void Index::intakeFile(string path){
    
    ifstream infile;
    infile.open(path.c_str());

    if (!infile.is_open()){
        cerr << "error opening file";
        return; 
    }

    string theLine;
    int lineNum = 1;

    while (getline(infile, theLine)){
        
    //convert to istringstream so that I can overload to cp each word in line
        istringstream line_stream(theLine);
        processLine(path, line_stream, lineNum);
        lineNum++;
    }

}

//input: the file path, the line itself, and linenumber
//output:nothing
//purpose: takes each word in the line, creates the key (lowercase of word)
// creates the subsiduary structs that contain the original word and path and
//line num and calls addWord for hashing process
void Index::processLine(string filepath, istream& fullline, int line){

    string word;
    string key;

    while (fullline >> word){ //intaking each word
        
        //removes non alphabetic/numeric characters
        word = sanitizeWord(word);
        
        if (word != ""){

            string temp = word;

            //lowers the cases
            for (unsigned long i = 0; i < temp.length(); i++){
                temp[i] = tolower(temp[i]);
            }
            key = temp;

            //adds info to struct
            wordInfo newInfo(word, pathInfo(filepath, line));

            //creates index from key
            size_t index = hashKey(key);

            addWord(hashTable[index], key, newInfo);
        }   
    }

}

//input: string
//output: refined string
//purpose: removes non alphabetical/numerical characters from word
string Index::sanitizeWord(string input){
    while (! isalnum(input[0])){
        if(input.length() <= 0)
            return "";
        input = input.erase(0,1);
    }

    while(! isalnum(input[input.size()-1])){
        if(input.length() <= 0)
            return "";
        input = input.erase(input.size()-1, input.size());
    }

    return input;
}

//input: string
//output: size_t numerical index
//purpose: uses hash function return positive key and mods table size
size_t Index::hashKey(string key){
    size_t idx = hash<string>{}(key) % currTableSize;
    return idx;
}

//input: the hashtable at an index (wordStruct), the key string, and wordInfo 
//struct
//output: recurses with helper function
//purpose: checks if the key parameter is equal to the key in the existing 
//location of hash table. calls savespace() if true or recurses
void Index::addWord(wordStruct *&hashTable, string key, wordInfo info){
    
    //base case and creates new struct and has table at index point to it
    if (hashTable == NULL){
        hashTable = new wordStruct(key, info);
        entries++;
    }
    else {
        if (hashTable-> key == key)
            saveSpace(hashTable, info);
        else
            addWord(hashTable->next, key, info, hashTable);
    }
}

//input: hashtable at index (wordStrct), key, info struct, prev wordStruct 
//at hashtable idx
//output: recurses
//purpose: calls saveSpace() if matching key or recurses to end and ends new
//wordStruct at end of list
void Index::addWord(wordStruct *&hashTable, string key, wordInfo info, 
    wordStruct *&prev){

    if (hashTable == NULL){
        hashTable = new wordStruct(key, info);
        entries++;
        prev->next = hashTable; //links the list together
    }
    else {
        if (hashTable-> key == key)
            saveSpace(hashTable, info);
        else
            addWord(hashTable->next, key, info, hashTable);
    }
}

//input: wordStruct and wordInfo struct
//output: nothing
//purpose: checks if the original words are equal and will then only add
//to vector of location and linenum. if not, it will just add the wordStruct
//to back of vector
void Index::saveSpace(wordStruct *&hashTable, wordInfo info){
    
    int i = 0;
    int size = hashTable->info.size();
    
    for (i = 0; i < size; i++){
        
        if (hashTable->info[i].OGword == info.OGword){
        
        string loc = info.path.back().path; //saves memory
        int line = info.path.back().lineNum;
        hashTable->info[i].path.push_back(pathInfo(loc, line));
        return;
        
        }
    }

        hashTable->info.push_back(info);
    

}

//input: nothing
//output: nothing
//purpose: expands hashtable to decrease chance of collisions
void Index::expand(){
    
    float loadFactor = (float)entries/currTableSize;
    
    if(loadFactor < .7)
        return;


    int oldSize = currTableSize;

    currTableSize *= 2;

    wordStruct ** newTable = new wordStruct *[currTableSize];

    for (int i = 0; i < currTableSize; i++){
        newTable[i] = NULL;
    }

    for (int i = 0; i < oldSize; i++){
        wordStruct *temp = hashTable[i];
        while (temp != NULL){
            expandHelper(temp, newTable);
            temp = temp->next;
        }
    }
    clearTable(oldSize);
    hashTable = newTable;

}

//input: wordStruct and the new hashtable itself
//output: nothing
//purpose: creates new node with data set to old wordStruct and sets the
//the pointer of new hashtable at correct index to the new node
void Index::expandHelper(wordStruct * node, wordStruct **&newTable){
    if (node == NULL) return;

    wordStruct *newStruct = new wordStruct(node);
    size_t index = hashKey(node -> key);
    if (newTable[index] == NULL)
        newTable[index] = newStruct;
    else{
        wordStruct * passer = newTable[index];
        while (passer -> next != NULL)
            passer = passer->next;

        passer->next = newStruct;
    }
}

//input: int size
//output: nothing
//purpose: loops the length of size calling clear Struct and finishes with
// deleting the hashtable
void Index::clearTable(int size){
    
    for (int i = 0; i < size; i++){
        
        if (hashTable[i] != NULL){
            clearStruct(hashTable[i]);
    }  
        }

    delete [] hashTable;
}

//input: struct node
//output: nothing
//purpose: recurses to end of list and deletes all nodes after recursive
// operation is over
void Index::clearStruct(wordStruct * node){
    
    if (node -> next != NULL)
        clearStruct(node->next);
    
    delete node;
}

//input: nothing
//output: reference to hashtable
//purpose: used by main to pass the hashtable to query requests
wordStruct **&Index::returnTable(){
    return hashTable;
}
