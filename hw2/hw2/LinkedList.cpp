/*
 * LinkedList.cpp
 * COMP15
 * Spring 2019
 * 
 * Implementation for Linked List of Green Line Extension Stations
 */

#include "LinkedList.h"
#include <iostream>
using namespace std;

// Default constructor
LinkedList::LinkedList(){
    length = 0;
    head = NULL;
    currPos = NULL;
}

// Destructor
LinkedList::~LinkedList() {
    NodeType *temp = head;
    NodeType *curr;
    while (temp != NULL){
        curr = temp->next;
        delete temp;
        temp = curr;
    }
}

// Creates NewNode
NodeType *LinkedList::NewNode(Station s, NodeType *next){
    NodeType *NewNode = new NodeType;
    NewNode->info = s;
    NewNode->next = next;
    return NewNode; 
}

// Assignment operator
LinkedList & LinkedList::operator = (const LinkedList &l){
    NodeType *temp;
    while (head != NULL){
        temp = head;
        head = head->next;
        delete temp;
    }
    length = l.length;
    currPos = NULL;
    if (l.head == NULL)
        head = NULL;
    else{
        head = new NodeType;
        head->info = l.head->info;
        head->next = NULL;
        NodeType *curr = head;
        NodeType *orig = l.head;
        while (orig->next != NULL){
            curr->next = new NodeType;
            curr->next->info = orig->next->info;
            curr->next->next = NULL;
            orig = orig->next;
            curr = curr->next;
        }
    }
    return *this;
}

// Input: nothing
// Returns: the length
// Does: returns the length of the LL
int LinkedList::getLength() const{
    return length;
}

// Input: nothing
// Returns: true if currPos is NULL
// Does: determines if currPos is NULL or not
bool LinkedList::isCurrPosNull() const{
    return currPos == NULL;    
}

// Input: a station
// Returns: nothing
// Does: inserts a station at beginning of LL
void LinkedList::insertStation(Station s){
    if (head ==NULL){
        head = NewNode(s, NULL);
        length++;
        return;
    }
    NodeType *Block = NewNode(s, head);
    head = Block;
    length++;
}

// Input: a station
// Returns: nothing
// Does: searches LL for station, removes it and sets the 
//previous nodes next pointer to the removed nodes' next
void LinkedList::removeStation(Station s){
    NodeType *curr, *temp = head;
    if (head == NULL)
       return;
    if (head->info.isEqual(s)){
        NodeType *temp = head->next;
        delete head;
        head = temp;
        length--;
        return;
    }
    while ((temp->next != NULL) and !(temp->info.isEqual(s))){
        curr = temp;
        temp = temp->next;
    }
    if (temp->info.isEqual(s)){   
        curr->next = temp->next;
        if (temp == currPos) //part e
            resetCurrPos();
        delete temp;
        length--;
    }
}


// Input: nothing
// Returns: a station (that currPos is pointing to)
// Does: takes station currPos is pointing to and returns it. updates
//currPos to next station
Station LinkedList::getNextStation(){
    if (currPos == NULL){
        currPos = head->next;
        return head->info;
    }
    NodeType *back = head;
    while (back->next != NULL){
        back = back->next;
    }

    if (currPos == back){
        NodeType *temp = currPos;
        currPos = head;
        return temp->info;
    }
    if (currPos != NULL){
        NodeType *temp = currPos;
        currPos = currPos->next;
        return temp->info;
    }

}

// Input: 
// Returns: 
// Does: sets currPos to NULL
void LinkedList::resetCurrPos(){
   currPos = NULL;
}

// Input: 
// Returns: 
// Does: empites the list, making sure to delete all Nodes and sets front Null
void LinkedList::makeEmpty(){
     NodeType *temp = head;
    NodeType *curr;
    while (temp != NULL){
        curr = temp->next;
        delete temp;
        temp = curr;
    }
    length = 0;
    currPos = NULL;
    head = NULL;
}



// Input: a file to write to
// Returns: 
// Does: print the linked list in a certain way as it progresses
void LinkedList::print(ostream &out){
    //test
    int counter = length;
    NodeType *temp = head;
    while (temp != NULL){
        temp->info.print(out);
        out << " " << counter - 1;
            if (temp->next != NULL)
                out<< " == ";
                temp = temp->next;
                counter--;
    }
    out << endl;
}



