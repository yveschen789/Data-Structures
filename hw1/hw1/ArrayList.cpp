/*
 * Array.cpp
 * COMP15
 * Spring 2019
 *
 * Implementation for Arrrrrrray of Pirates
 */
#include <iostream>
#include "ArrayList.h"

using namespace std;

// Default constructor
// Length and current position default to 0
ArrayList::ArrayList(){
    length = 0;
    currPos = 0;
    pirates = new Pirate[MAX_PIRATES];
    capacity = MAX_PIRATES;
}

ArrayList::~ArrayList(){
    delete [] pirates;
}

// Inputs: Pirate object, bool by reference
// Returns: Pirate object
// Does: Looks for pirate in the array, modifies bool if found
//       Returns the object from the list and not the passed one
//       (In case they're different.)
Pirate ArrayList::find(Pirate p, bool &found) const{
    int location = 0;

    while ((location < length) && !found){
        if (p == pirates[location]){
            found = true;
            p = pirates[location];
            break;
        }
        location++;
    }
    return p;
}

// Inputs: Pirate object
// Returns: Nothing
// Does: Adds Pirate to end of array, increases length
void ArrayList::insert(Pirate p){
    for (int i = 0; i < length; i++){
        if (p == pirates[i]){
            cerr << "duplicate\n";
            return;
        }
    }
    
    pirates[length] = p;
    length++;

    if (length == capacity){
        expand();
    }
}

// Inputs: Pirate object
// Returns: Nothing
// Does: Deletes pirate, shifts everything else over
void ArrayList::remove(Pirate p){

    int index;
    bool piratefound = false;
    for (int i = 0; i < length; i++){
        if (pirates[i] == p){
            piratefound = true;
            index = i;
            break;  
        }    
    }
    if (piratefound){
        for (int j = index + 1; j < length; j++){
                pirates[j-1] = pirates[j];        
        
        }
        length--;
    }
    
    if (length <= capacity/2)
            shrink();
    return;
}

// Input: None
// Returns: Pirate object
// Does: Returns pirate at currPos
//       Increments currPos, but wraps around
Pirate ArrayList::getNext(){
    Pirate p = pirates[currPos];
    currPos = (currPos + 1) % length;
    return p;
}

// Input: none
// Returns: none
// Does: sets length to 0 (memory not modified)
void ArrayList::makeEmpty(){
    length = 0;
}

// Input: none
// Returns: none
// Does: sets currPos to 0 
void ArrayList::resetArray(){
    currPos = 0;
}

// Input: a file to write to
// Returns: nothing
// Does: Prints array from 0 to length in file
void ArrayList::print(ostream &theStream) const {
    for (int i = 0; i < length; i++){
        pirates[i].print(theStream);
        if (i != length - 1)
            theStream << ", ";
    }
}

// Input: none, const
// Returns: bool
// Does: Compares actual length to capacity
bool ArrayList::isFull() const {
    return (length >= MAX_PIRATES-1);
}

// Input: none, const
// Returns: int
// Does: Returns the value in length attribute
int ArrayList::getLength() const {
    return length;
}

void ArrayList::expand(){
    cout << "Expand to " << capacity*2 << endl;
    capacity = capacity*2;
    Pirate *newlist = new Pirate[capacity];
    for (int i = 0; i < length; i++){
        newlist[i] = pirates[i];
    }
    delete [] pirates;
    pirates = newlist;
}

void ArrayList::shrink(){
    Pirate *newlist = new Pirate[capacity/2];
    cout << "Shrink to " << capacity/2 << endl;
    for (int i = 0; i < capacity/2; i++){
        newlist[i] = pirates[i];
    }
    delete [] pirates;
    pirates = newlist;
    capacity = capacity/2;
}
