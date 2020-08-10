//Name: Yves Chen
//Date: 4/3/19
//Purpose: Implementation of Actor Object
//Uses: classes, conditionals, functions
#include <iostream>
#include "Actor.h"
#include "LinkedList.h"
using namespace std;

//unparameterized constructor
Actor::Actor(){
    ActorName = "";
}

//paramaterized constrctor
Actor::Actor(string name)
{
    ActorName = name;
}


//inserts movie
void Actor::InsertMovie(string Movie){
    if(!IsActorInMovie(Movie))
        ActorMovies.insert(Movie);
}

//checks if movie is inserted before
bool Actor::IsActorInMovie(string Movie){
    bool ifTrue = false;
    ActorMovies.find(Movie, ifTrue);
    if (ifTrue)
        return true;
    else
        return false;
}

//returns the movie that two actors are connected
string Actor::connect(Actor ActTwo){
    for (int i = 0; i < ActorMovies.get_length(); i++){
        if (ActTwo.IsActorInMovie(ActorMovies.get_value_at(i)))
            return ActorMovies.get_value_at(i);
    }
    return "";
}

//overload operator for comparison
bool operator ==(const Actor& ActOne, const Actor &ActTwo){
    return (ActOne.ActorName == ActTwo.ActorName);
}

//overload operator for not equal
bool operator !=(const Actor& ActOne, const Actor &ActTwo){
    return (ActOne.ActorName != ActTwo.ActorName);
}

//overload operator for outing actorname
ostream& operator <<(ostream& outs, const Actor &Object){
    outs << Object.ActorName;
    return outs;
}





