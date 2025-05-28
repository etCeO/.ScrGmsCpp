// Full Name: Ethan E. Lopez
// Student ID: 2425516 
// Chapman Email: etlopez@chapman.edu
// Course Number And Section: CPSC-350-03
// Assignment Or Exercise Number: PA5: Scare Games

#ifndef TOURNAMENTTREE_H // instantiates class only once
#define TOURNAMENTTREE_H // defines TournamentTree class

#include <iostream> // includes input and output functions
#include <string> // includes std::string
#include <vector> // includes std::vector
#include <fstream> // includes std::ofstream and std::ifstream
#include "Monster.h" // includes Monster class
#include "TournamentNode.h" // includes TournamentNode class

using std::cout; // shortens output to cout
using std::endl; // shortens newline to endl

class TournamentTree { // class body

    private:
        int size; // size of the current tree, used during max heap implementation
        int getParent(int i); // gets parent nodes
        int getLeftChild(int i); // gets left child
        int getRightChild(int i); // gets right child

    public:
        std::vector<TournamentNode*> mVector; // a vector of tournament nodes when the tournament is ran (results of matches displayed here)
        std::vector<TournamentNode*> tree; // a vector representing the actual order of the tree in max heap style 
        // first node is the root while the following nodes are its children and subchildren
        TournamentTree(); // default constructor
        ~TournamentTree(); // default destructor
        void insert(TournamentNode* t); // inserts a new node into the tree's construction
        void assignPointers(); // assigns all pointers to the tree after max heap creation
        void saveTreeAsDot(const std::string& outFilename, TournamentNode* rootNode); // saves the tree into a dot file
        void saveTreeAsDotHelper(TournamentNode* node, std::ofstream& file, int& nodeID); // helps saveTreeAsDot() method for each node

};

#endif // end of class definition