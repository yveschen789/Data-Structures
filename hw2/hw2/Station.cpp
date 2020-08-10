/* 
 * Station.cpp
 * COMP15
 * Fall 2019
 *
 * Implementation of the Station class for homework 2
 */

#include "Station.h"

// Constructor
Station::Station(){
	name = "NoName";
    access = false;
}

// Parameterized Constructor
Station::Station(string input_name, bool input_access){
    name = input_name;
    access = input_access;
}

// Function: checks if two station classes are equal
// Input: a station
// Returns: a bool
// Does: checks if two stations are equal
bool Station::isEqual(Station s){
    if ((name == s.name) and (access == s.access))
    	return true;
    return false;
}

// Function: print station and bool as A or U
// Input: a file to write to
// Returns: nothing
// Does: prints station
void Station::print(ostream &outfile){
    outfile << name;
    outfile << " ";
    if (access)
    	outfile << "A";
    else
    	outfile << "U";
}


