// Full Name: Ethan E. Lopez
// Student ID: 2425516 
// Chapman Email: etlopez@chapman.edu
// Course Number And Section: CPSC-350-03
// Assignment Or Exercise Number: PA5: Scare Games

#include <iostream> // includes input and output functions
#include <string> // includes std::string
#include <vector> // inclues std::vector
#include <fstream> // includes std::ofstream and std::ifstream
#include "TournamentTree.h" // includes header outFile
#include "TournamentNode.h" // includes TournamentNode class
#include "Monster.h" // includes Monster class

using std::cout; // shortens output to cout
using std::endl; // shortens newline to endl

TournamentTree::TournamentTree() : size(0) {}; // default constructor
// size defaults to 0 because the tree is empty

TournamentTree::~TournamentTree(){}; // default destructor

int TournamentTree::getParent(int i){
// a private int method for getting a parent node's index
  return (i-1)/2;
}

int TournamentTree::getLeftChild(int i){
// a private int method for getting a left child node's index
  return (2*i)+1;
}

int TournamentTree::getRightChild(int i){
  // a private int method for getting a right child node's index
  return (2*i)+2;
}

// PUBLIC METHODS

void TournamentTree::insert(TournamentNode* t){
// a public void method that inserts nodes into the tree storing the elements as a Max Heap
  ++size; // increments size of the tree
  tree.push_back(t); // pushes back the tournament node to the last index
  int current = size - 1; // current index of the node that came before
  while ((current != 0) && (tree[current]->m_data->screamPower > tree[getParent(current)]->m_data->screamPower)) {
  // heap rules checking
  // while the current is not the root and the current happens to be greater than its parent
    TournamentNode* temp = tree[current]; // assign temp to the current node
    tree[current] = tree[getParent(current)]; // switch the parent with the current node
    tree[getParent(current)] = temp; 
    current = getParent(current); // the current index is now the parent index of the previous node we checked
    // iterates throughout the tree vector to order elements in there appropriate place
  }
}

void TournamentTree::assignPointers() {
// a public void method that assigns each node's pointers once the vector of the tree is constructed
  for (int i = 0; i < tree.size(); i++) {
  // for every node in the tree
    tree[i]->winner = tree[i];
    // assign winner as the current node
    // all monsters begin as "winners" until they are no longer identified in the upper parents
    // if the root node, this will automatically default to itself
    if (getLeftChild(i) < tree.size()) {
    // if the index of a left child is not out of bounds of the tree's size
      tree[i]->left = tree[getLeftChild(i)];
      // the node's left child is the tree's index at 2*i + 1
    }
    if (getRightChild(i) < tree.size()) {
    // if the index of a right child is not out of bounds of the tree's size
      tree[i]->right = tree[getRightChild(i)];
      // the node's right child is the tree's index at 2*i + 2
    }
  }
}

void TournamentTree::saveTreeAsDot(const std::string& outFileName, TournamentNode* rootNode) {
// a public void method for saving the tree into a dot outFile once the tournament is finished
// outFileName is the name of the DOT file & rootNode is the tree's current root
    std::ofstream outFile(outFileName); // declare file writer
    if (!outFile.is_open()) {
        // if the File is not open
        std::cerr << "Failed to open outFile for DOT output: " << outFileName << "\n";
        // print an error occurred
        return; // stop the program
    }
    // otherwise
    outFile << "digraph TournamentTree {\n";
    // begin crafting tree
    int nodeID = 0; // nodeID starts at 0 for root
    saveTreeAsDotHelper(rootNode, outFile, nodeID); // recursive method for each node
    outFile << "}\n"; // ends outFile
    outFile.close(); // close writing
}

void TournamentTree::saveTreeAsDotHelper(TournamentNode* node, std::ofstream& outFile, int& nodeID) {
// a public void method for assisting the saveTreeAsDot() method
// recursor for placing nodes in their correct position
    if (node == NULL) return;
    // if there is no node, stop the program

    int currentID = nodeID++; // variable for the node's current ID
    // for every node, ID is incremented to keep track of vector indexing
    outFile << "    node" << currentID << " [label=\"" << node->winner->m_data->name
         << " (Power: " << node->winner->m_data->screamPower << ")\"];\n";
    // records node's match index with the current winner and winner information

    if (node->left) {
    // if the node to be written is a left child
        int leftID = nodeID; // ensure IDs are set
        saveTreeAsDotHelper(node->left, outFile, nodeID);
        // call method again for the left child
        outFile << "    node" << currentID << " -> node" << leftID << ";\n";
        // map the current node's next direction pointing to the left child
    }

    if (node->right) {
    // if the node to be written is a right child
        int rightID = nodeID; // ensure IDs are set
        saveTreeAsDotHelper(node->right, outFile, nodeID);
        // call method again for the right child
        outFile << "    node" << currentID << " -> node" << rightID << ";\n";
        // map the current node's next direction pointing to the right child
    }
}

