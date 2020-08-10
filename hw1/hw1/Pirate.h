/*
 * Pirate.h
 * COMP15
 * Spring 2019
 *
 * Interface for a Pirate class
 * yo ho ho
 */

#include <fstream>
#include <string>
using namespace std;

#ifndef PIRATE_H_
#define PIRATE_H_


class Pirate
{
public:
    Pirate();
    Pirate(string);
    void print(ostream &theStream) const;
    void generatePirateName(ifstream &, int);
    void generateNextPirate(ifstream &infile);
    void assignPirateId();
    friend bool operator == (const Pirate &, const Pirate &);
private:
    int pirateId;
    string name;
    static int pirate_count;
};

#endif
