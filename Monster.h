// Full Name: Ethan E. Lopez
// Student ID: 2425516 
// Chapman Email: etlopez@chapman.edu
// Course Number And Section: CPSC-350-03
// Assignment Or Exercise Number: PA5: Scare Games

#ifndef MONSTER_H // instantiates class only once
#define MONSTER_H // defines Monster class

#include <iostream> // includes input and output functions
#include <string> // includes std::string

class Monster { // class body

    public:
        std::string name; // monster's name
        int screamPower; // monster's power level
        Monster(); // default constructor for proper running and "dummy" monsters
        Monster(std::string n, int level); // overloaded constructor
        ~Monster(); // default destructor

};

#endif // end of class definition