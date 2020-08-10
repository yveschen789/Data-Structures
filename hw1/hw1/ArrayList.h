/*
 * ArrayList.h
 * COMP15
 * Spring 2019 
 *
 * Interface for Array of Pirates, matey
 */

#include "Pirate.h"

#ifndef ARRAY_H_
#define ARRAY_H_

const int MAX_PIRATES = 100;


class ArrayList
{
public:
    // Default constructor
    ArrayList();
    ~ArrayList();

    // The basic operations:
    // Insert, Delete, and Find
    Pirate find(Pirate, bool &) const;
    void insert(Pirate);
    void remove(Pirate);
    Pirate getNext();

    // Start over at the beginning of the list
    void makeEmpty();
    void resetArray();

    // Return some basic info
    bool isFull() const;
    int getLength() const;

    // Print the array
    void print(ostream &theStream) const;

    // expand and shrink dynamic array
    void expand();
    void shrink();

private:
    int length;
    Pirate *pirates;
    int currPos;
    int capacity;
};

#endif
