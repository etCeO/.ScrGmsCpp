// Full Name: Ethan E. Lopez
// Student ID: 2425516 
// Chapman Email: etlopez@chapman.edu
// Course Number And Section: CPSC-350-03
// Assignment Or Exercise Number: PA5: Scare Games

#ifndef TOURNAMENTNODE_H // instantiates class only once
#define TOURNAMENTNODE_H // defines TournamentNode class

#include <iostream> // includes input and output functions
#include <string> // includes std::string
#include "Monster.h" // includes content from Monster class

class TournamentNode { // class body

    public:
        Monster* m_data; // monster data (name and scream power)
        TournamentNode* winner; // keeps track of current winner in the match
        TournamentNode* left; // the left child of the parent
        TournamentNode* right; // the right child of the parent
        TournamentNode(); // default constructor
        TournamentNode(Monster* m); // overloaded constructor
        ~TournamentNode(); // default destructor

};

#endif // end of class definition