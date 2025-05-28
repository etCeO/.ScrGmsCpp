// Full Name: Ethan E. Lopez
// Student ID: 2425516 
// Chapman Email: etlopez@chapman.edu
// Course Number And Section: CPSC-350-03
// Assignment Or Exercise Number: PA5: Scare Games

#include <iostream> // includes input and output functions
#include <string> // includes std::string
#include "Monster.h" // includes header class

Monster::Monster() : name(""), screamPower(0) {}; // default constructor
// creates "dummy" monsters when desired that hold no name and a scream power level of 0

Monster::Monster(std::string n, int level) : name(n), screamPower(level) {};
// overloaded constructor
// takes in a monster's name and power level and assigns it to the appropriate variables

Monster::~Monster(){};
// default destructor