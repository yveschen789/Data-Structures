/*
PirateMates.h
Name: Yves Chen
Date: 1/24/18
Purpose: Struct used by hookbook
*/

#include "Pirate.h"
#include "ArrayList.h"


// struct that holds a pirate and an ArrayList that dynamically stores
// that pirates' mates
struct PirateMates {
	Pirate pirate;
	ArrayList mates;
};
