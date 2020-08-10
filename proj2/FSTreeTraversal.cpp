// FSTreeTraversal.cpp
// purpose: take an input and print the files and directories to cout
// name: Yves Chen
// date: 4/11

#include <iostream>
#include "DirNode.h"
#include "FSTree.h"

using namespace std;

void print_files(DirNode * curr, string file);



int main (int argc, char* argv[]){
    argc = 1;
    
    FSTree tree(argv[1]);



    print_files(tree.getRoot(), argv[1]);

    tree.burnTree();

    return 0;
}

void print_files(DirNode * curr, string file){
    
    if (curr->hasSubDir()){
        for (int i = 0; i < curr->numSubDirs(); i ++)
            print_files(curr->getSubDir(i), file + '/' + curr->getName() + '/');
    }

    if (curr->hasFiles()){
        for(int i = 0; i < curr->numFiles(); i ++){
                cout << file << curr->getFile(i) << endl;
        }
    }

     cout << curr->getName() << endl;
    
}

// void print_file_helper(DirNode * curr, string file, string prevFile){
    
    

//     if (curr->hasFiles()){
//         for(int i = 0; i < curr->numFiles(); i ++){
//                 cout << file << '/' << prevFile << '/' << curr->getName() << '/' 
//                 << curr->getFile(i) << endl;
//         }
//     }

//     if (curr->hasSubDir()){
//         for (int i = 0; i < curr->numSubDirs(); i ++)
//             print_file_helper(curr->getSubDir(i), file, curr->getName());
//     }

//     cout << curr->getName() << endl;

// }