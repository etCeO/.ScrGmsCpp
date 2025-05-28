// Full Name: Ethan E. Lopez
// Student ID: 2425516 
// Chapman Email: etlopez@chapman.edu
// Course Number And Section: CPSC-350-03
// Assignment Or Exercise Number: PA5: Scare Games

#include <iostream> // includes input and output functions
#include <string> // includes std::string
#include <fstream> // includes ifstream and ofstream
#include <sstream> // include std::stringstream
#include <vector> // includes std::vector
#include "RunScareGame.h" // includes scare game class
#include "TournamentTree.h" // includes tournament tree class
#include "TournamentNode.h" // includes tournament node class
#include "Monster.h" // includes Monster class

using std::cout; // shortens output to cout
using std::endl; // shortens newline to endl

RunScareGame::RunScareGame(){}; // default constructor

RunScareGame::~RunScareGame(){}; // default destructor

void RunScareGame::runTournament(std::string inFileName, std::string competition) {
// a public void method for running the tournament based on the monster file and competition type
    std::ifstream inFile(inFileName); // declare file reader
    std::string line; // declare line string for txt lines
    
    if (inFile.is_open()) {
    // if the file is opened
        std::vector<Monster*> monsters; // create a vector for listing the monsters in the tournament

        while (std::getline(inFile, line)) {
        // for every line read
            std::stringstream ss(line); // create a stream
            std::string mName; // a string to hold the monster's name
            std::string mPowerString; // a string to hold the monster's scream power

            if (std::getline(ss, mName, ',') && std::getline(ss, mPowerString)) {
            // if there are two values available separated by a comma
                int mScreamPower = stoi(mPowerString);
                // convert power string into an integer
                monsters.emplace_back(new Monster(mName, mScreamPower));
                // use vector's built in emplace_back() method to create a Monster object and add it to the monster list
            }
        }

        // ERROR / ALGORITHM Correction techniques

        if (monsters.size() % 2 != 0) {
        // if the number of initial competitors is odd
        // add a "dummy" monster to pair the last odd node
            monsters.emplace_back(new Monster());
            // this monster is named nothing with a power of 0 and results in proper tree construction
            // for ex. if monsters = [3,6,9], the list becomes [3,6,9,0]
        }
        if (monsters.size() > 9) {
        // if the number of competitors is a double digit, this is where tree construction gets more complex
            if ((monsters.size()/2) % 2 != 0) {
            // if the size of the vector does not have an even multiple accompanied by 2
                monsters.emplace(monsters.begin(), new Monster()); // add one "dummy" monster at the beginning
                monsters.emplace(monsters.begin() + (monsters.size()/2), new Monster()); // add another somewhere in the middle
            }
            // for ex. if monsters = [3,1,2,5,6,7,4,8,9,10], this becomes [0,3,1,2,5,0,6,7,4,8,9,10]
        }
        // WORST CASE SCENARIO - it's possible to have 3 dummy monsters in a single tree (beginning, middle, and end)
        // arbitrary as this seems, this is necessary for a max heap implementation to work

        TournamentTree tournament; // create a default tree to begin the tracking of the monster's tournament
        // this will either be just the winners tree or the losers and winners trees tied together depending on the competition type

        if (competition == "single" || competition == "Single") {
        // if the competition type is a single
            for (int i = 0; i < monsters.size(); i++) {
            // for all monsters in the monsters array
            // add them to the tournament monster vector
            // for ex. where monsters = [3,6,9,4]
                tournament.mVector.emplace_back(new TournamentNode(monsters[i]));       
                // mVector becomes [3,6,9,4] with TournamentNodes
            }
            int idx = 0; // index for looping throughout the vector
            while (monsters.size() > 1) {
            // while the list of monsters is greater than 1 (there is no winner)
                if (idx >= monsters.size() - 1) { // if an index is out of bounds
                    idx = 0; // reset to 0
                }
                int j = idx % monsters.size(); // error handling (only indexes in the vector)
                if (j < monsters.size() - 1) {
                // if the index is not the last index
                    if (monsters[j]->screamPower > monsters[j+1]->screamPower) {
                    // if the first monster scored better than the second monster
                        tournament.mVector.emplace_back(new TournamentNode(monsters[j])); // first monster moves forward by getting added
                        monsters.erase(monsters.begin() + (j+1)); // competitor is eliminated
                    }
                    else {
                    // if the second monster scored better or the same as the first monster
                        tournament.mVector.emplace_back(new TournamentNode(monsters[j+1])); // second monster moves forward by getting added
                        monsters.erase(monsters.begin() + j); // competitor is eliminated
                    }
                }
                ++idx; // increment index
                // for monsters -> [3,6,9,4], mVector becomes [3,6,9,4,6,9,9] because 6 and 9 are the winners of pairs 3,6 and 9,4 and 9 is the winner of 6,9
            }
            for (int i = tournament.mVector.size() - 1; i >= 0; i--) {
            // for all nodes in the tournament
                tournament.insert(tournament.mVector[i]);
                // insert them into the max heap in reverse order
                // "tree" structure in the class is now [9,9,6,4,9,6,3]
            }
            tournament.assignPointers(); // assigns all children and parents in each node
            tournament.saveTreeAsDot("winners_bracket.dot", tournament.tree[0]); // save the tree as a dot file beginning at the root
        }
        else if (competition == "double" || competition == "Double") {
            TournamentTree winners; // keeps track of winners
            TournamentTree losers; // keeps track of losers
            std::vector<Monster*> monsters2; // a vector to store the losers
            for (int i = 0; i < monsters.size(); i++) {
            // for all monsters in the monsters array
            // add them to the winners tournament monster vector (everyone starts out in this bracket)
            // for ex. monsters = [3,6,9,4]
                winners.mVector.emplace_back(new TournamentNode(monsters[i]));
                // mVector = [3,6,9,4] with tournamentNodes
            }

            // WINNERS

            int idx = 0; // index for looping throughout the vector
            while (monsters.size() > 1) {
            // while the list of monsters is greater than 1 (there is no winner)
                if (idx >= monsters.size() - 1) { // if an index is out of bounds
                    idx = 0; // reset to 0
                }
                int j = idx % monsters.size(); // error handling (only indexes in the vector)
                if (j < monsters.size() - 1) {
                // if the index is not the last index
                    if (monsters[j]->screamPower > monsters[j+1]->screamPower) {
                    // if the first monster scored better than the second monster
                        winners.mVector.emplace_back(new TournamentNode(monsters[j])); // first monster moves forward by getting added in winners
                        monsters2.push_back(monsters[j+1]); // competitor is added into the losers tournament
                        monsters.erase(monsters.begin() + (j+1)); // then eliminated from the winners bracket
                    }
                    else {
                    // if the second monster scored better or the same as the first monster
                        winners.mVector.emplace_back(new TournamentNode(monsters[j+1])); // second monster moves forward by getting added in winners
                        monsters2.push_back(monsters[j]); // competitor is added into the losers tournament
                        monsters.erase(monsters.begin() + j); // then eliminated
                    }
                }
                ++idx; // increment index
                // for monsters -> [3,6,9,4], mVector becomes [3,6,9,4,6,9,9] because 6 and 9 are the winners of pairs 3,6 and 9,4 and 9 is the winner of 6,9
            }
            for (int i = winners.mVector.size() - 1; i >= 0; i--) {
            // for all nodes in the tournament
                winners.insert(winners.mVector[i]);
                // insert them into the winners max heap in reverse order
                // tree structure is now [9,9,6,4,9,6,3]
            }
            winners.assignPointers(); // assign all children and parents in each node

            // LOSERS

            // ERROR / ALGORITHM Correction techniques

            if (monsters2.size() % 2 != 0) {
            // if the number of initial losers is odd
            // add a "dummy" monster to pair the last odd node
                monsters2.emplace_back(new Monster());
                // this monster is named nothing with a power of 0 and results in proper tree construction
                // for ex. if monsters2 (losers) = [3,4,6], the list becomes [3,4,6,0]
            }
            if (monsters2.size() > 9) {
            // if the number of losers is a double digit, this is where tree construction gets more complex
                if ((monsters2.size()/2) % 2 != 0) {
                // if the size of the vector does not have an even multiple accompanied by 2
                    monsters2.emplace(monsters2.begin(), new Monster()); // add one "dummy" monster at the beginning
                    monsters2.emplace(monsters2.begin() + (monsters2.size()/2), new Monster()); // add another somewhere in the middle
                }
                // for ex. if monsters = [3,1,2,5,6,7,4,8,9,10], this becomes [0,3,1,2,5,0,6,7,4,8,9,10]
            }
            // WORST CASE SCENARIO - it's possible to have 3 dummy monsters in a single tree (beginning, middle, and end)
            // arbitrary as this seems, this is necessary for a max heap implementation to work

            for (int i = 0; i < monsters2.size(); i++) {
            // for all monsters in the monsters array
            // add them to the losers monster vector
            // for loser monsters = [3,4,6,0]
                losers.mVector.emplace_back(new TournamentNode(monsters2[i]));
                // mVector = [3,4,6,0] with tournamentNodes
            }
            int idx2 = 0; // index for looping throughout the vector
            while (monsters2.size() > 1) {
            // while the list of monsters is greater than 1 (there is no winner)
                if (idx2 >= monsters2.size() - 1) { // if an index is out of bounds
                    idx2 = 0; // reset to 0
                }
                int y = idx2 % monsters2.size(); // error handling (only indexes in the vector)
                if (y < monsters2.size() - 1) {
                // if the index is not the last index
                    if (monsters2[y]->screamPower > monsters2[y+1]->screamPower) {
                    // if the first monster scored better than the second monster
                        losers.mVector.emplace_back(new TournamentNode(monsters2[y])); // first monster moves forward by getting added in losers
                        monsters2.erase(monsters2.begin() + (y+1)); // competitor is eliminated
                    }
                    else {
                    // if the second monster scored better or the same as the first monster
                        losers.mVector.emplace_back(new TournamentNode(monsters2[y+1])); // second monster moves forward by getting added in losers
                        monsters2.erase(monsters2.begin() + y); // competitor is eliminated
                    }
                }
                ++idx2; // increment index
                // for monsters2 -> [3,4,6,0], mVector becomes [3,4,6,0,4,6,6] because 4 and 6 are the winners of pairs 3,4 and 6,0 and 6 is the winner of 4,6
            }
            for (int i = losers.mVector.size() - 1; i >= 0; i--) {
            // for all nodes in the losers tournament
                losers.insert(losers.mVector[i]);
                // insert them into the max heap in reverse order
                // tree structure is now [6,6,4,0,6,4,3]
            }
            losers.assignPointers(); // assigns children and parents to nodes
            losers.saveTreeAsDot("losers_bracket.dot", losers.tree[0]); // save the losers tree as a dot file beginning at the root

            // FINAL TREE

            tournament.insert(new TournamentNode(winners.tree[0]->m_data));
            // create a new TournamentNode starting with the winner monster of the winners bracket and add this into the tournament tree
            // since we know this monster is going to be the final winner, we want to start with this node at the root
            tournament.tree[0]->winner = tournament.tree[0]; // assign winner to the node itself
            tournament.tree[0]->left = winners.tree[0]; // assign left child to the root of the winners bracket
            tournament.tree[0]->right = losers.tree[0]; // assign right child to the root of the losers bracket
            // when these children are assigned, it connects both trees together to form a double tournament structure
            tournament.saveTreeAsDot("winners_bracket.dot", tournament.tree[0]); // save double tournament tree with both losers and winners in the "winners" bracket
            // be sure to start at the root to connect both brackets together
        }
        else { // error handling for other types of tournaments
            cout << "Invalid competiton type! Try again..." << endl;
        }
        inFile.close();
    }
    else { // if the file is not open, print an error
        cout << "Error: something went wrong when reading from the file" << endl;
    }
}