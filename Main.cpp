// Full Name: Ethan E. Lopez
// Student ID: 2425516 
// Chapman Email: etlopez@chapman.edu
// Course Number And Section: CPSC-350-03
// Assignment Or Exercise Number: PA5: Scare Games

#include <iostream> // includes input and output functions
#include <string> // includes std::string
#include "RunScareGame.h" // includes scare game class
#include "TournamentTree.h" // includes tournament tree class
#include "TournamentNode.h" // includes tournament node class
#include "Monster.h" // includes Monster class

using std::cout; // shortens output to cout
using std::endl; // shortens newline to endl

int main(int argc, char* argv[]) { // main method
// takes in a txt file and processes its contents

    RunScareGame game; // scare game object created

    try { // try the following program
        game.runTournament(argv[1], argv[2]);
        // runs the scare game based on the file to output a winner
    }
    catch (const std::exception& e) { // if something goes wrong
        std::cerr << "Error loading file... " << e.what() << endl;
        // print an error occurred and communicate what happened
        return 1; // end the program
    }

    return 0; // ends the program when success

}