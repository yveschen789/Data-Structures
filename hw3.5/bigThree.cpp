/*
 * COMP15 HW3.5
 * Spring 2019
 * 3/1/2019
 * Example program to solidify memory allocation and class concepts
 * Matias Korman
 * Edits: Lawrence Chan, Kevin Destin 3/1 copy constructor
 * Edits: Lawrence Chan 3/4 assignment operator
 */

#include <iostream>
#include <cstdlib>
using namespace std;

//compile with: clang++ -Wall -Wextra -g bigThree.cpp -o bigthree

//Silly class that reports whenever the Big Three (and constructor) are executed;
class myClass{
    // An integer is size 4
    int *i;

    public:
        myClass(){
            cout << "constructor of " << this << endl;
            i = new int;
        };

        ~myClass(){
            cout << "destructor of " << this << endl;
            delete i;
        };

        myClass(const myClass &otherObj){
            cout << "copy const of " << this << " from " << &otherObj << endl;
            // deep copying
            this->i = new int;
            *i = *(otherObj.i);
        };

        myClass& operator=(const myClass& otherObj) {
            cout << "assignment op of " << this << " from " << &otherObj << endl;

            if (this != &otherObj){
                delete i;
                this->i = new int;
                *i = *(otherObj.i);
            }
	    
            return *this;
        };
        
};

//Auxiliary function to pass an object of myClass
myClass foo(myClass c){
    return c;
}; 

int main(){
        myClass obj1;
        myClass obj2;

        obj2 = obj1;

        myClass obj3 = foo(obj1);
        // Program will end immediately after exit(0);
        // How many times is the destructor executed? why?
        // Run valgrind to see find memory leaks (if any) 
        // Remember to look at "still reachable" too@
        //exit(0);
        // Now try commenting the line above (exit(0)) and recompile.
        // How many times is the Destructor invoked?
        // Why?
        // Run valgrind to see find memory leaks (if any) 
        // Has anything changed? why?
        return 0;
        cout << "this line of code is never executed" << endl;
}
