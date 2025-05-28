// Full Name: Ethan E. Lopez
// Student ID: 2425516 
// Chapman Email: etlopez@chapman.edu
// Course Number And Section: CPSC-350-03
// Assignment Or Exercise Number: PA5: Scare Games

#include <iostream> // includes input and output functions
#include <string> // includes std::string
#include "TournamentNode.h" // includes header class
#include "Monster.h" // includes Monster class

TournamentNode::TournamentNode(){}; // default constructor

TournamentNode::TournamentNode(Monster* m) {
// overloaded constructor
// takes in Monster object m and assigns it as the node's data
    m_data = m; // Monster
    winner = NULL;
    left = NULL;
    right = NULL;
    // pointers "winner", left, and right are all assigned to NULL until updated during runtime
}

TournamentNode::~TournamentNode() {
    m_data = NULL;
    winner = NULL;
    left = NULL;
    right = NULL;
    // assign all values to null again to delete the match
}