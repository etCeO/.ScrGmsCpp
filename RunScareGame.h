// Full Name: Ethan E. Lopez
// Student ID: 2425516 
// Chapman Email: etlopez@chapman.edu
// Course Number And Section: CPSC-350-03
// Assignment Or Exercise Number: PA5: Scare Games

#ifndef RUNSCAREGAME_H // instantiates class only once
#define RUNSCAREGAME_H // defines RunScareGame class

#include <iostream> // includes input and output functions
#include <string> // includes std::string
#include <fstream> // includes ifstream and ofstream
#include <sstream> // includes std::stringstream
#include <vector> // includes std::vector
#include "TournamentTree.h" // includes tournament tree class
#include "TournamentNode.h" // includes tournament node class
#include "Monster.h" // includes Monster class

using std::cout; // shortens output to cout
using std::endl; // shortens newline to endl

class RunScareGame { // class body        

    public:
        RunScareGame(); // default constructor
        ~RunScareGame(); // default destructor
        void runTournament(std::string inFileName, std::string competition);
        // a method that manages the tournament with the input txt file and competition type

};

#endif // end of class definition