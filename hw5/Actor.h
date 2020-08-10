//Name: Yves Chen
//Date: 4/3/19
//Purpose: Interface for Actor class 
//Uses: classes, public, private, file io
#include "LinkedList.h"
#include <iostream>
#ifndef ACTOR_H_
#define ACTOR_H_

class Actor
{
public:
    Actor();
    Actor(string name);
    friend bool operator ==(const Actor & ActOne, const Actor& ActTwo);
    friend bool operator !=(const Actor & ActOne, const Actor& ActTwo);
    friend ostream& operator <<(ostream& outs, const Actor &Object);
    void InsertMovie(string Movie);
    bool IsActorInMovie(string Movie);
    string connect(Actor ActTwo);

   

private:
    
    LinkedList<string> ActorMovies;
    string ActorName;


};

#endif