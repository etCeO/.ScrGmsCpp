# Scare Games

- A binary tree-based tournament simulation that organizes and tracks players according to their scores, dynamically modeling competitive progression and advancement in a bracket-style structure inspired by the tournament system depicted in Disney’s Monsters, Inc.

## Author Info

- Full Name: Ethan E. Lopez
- Chapman Email: etlopez@chapman.edu

## Source Files

- Main.cpp
- RunScareGame.cpp
- RunScareGame.h
- TournamentTree.cpp
- TournamentTree.h
- TournamentNode.cpp
- TournamentNode.h
- Monster.cpp
- Monster.h
- monsters.txt

## Errors
- N/A

## Instructions For Running
- To compile: g++ *.cpp -o scaregames.exe
- To run: ./scaregames monsters.txt double

Notes: 

1. "monsters.txt" may be replaced with any file containing monster information.
2. "double" represents a double tournament with winner and loser brackets.
3. If a single tournament where losers are eliminated is desired, simply type "single" in place of double.

## Usage

This program simulates a competitive tournament using a binary tree structure.

### What The Program Does
---

1. Reads in a list of monsters and their attributes from an input file
2. Initializes a tournament bracket (tree structure)
3. Simulates matches between monsters:
  - Winners move forward in the tournament bracket
  - Losers:
    - Lose in a loser’s bracket (double elimination)
OR
    - Are eliminated (single elimination) in the tournament bracket

4. Play continues until a winner is determined in the tournament bracket

### Output
---

The program:

- Matches pairings and results
- Shows progression through the tournament bracket
- Shows the winner of the tournament bracket
- Constructs and displays the tournament tree

Example Run

- ./scaregames monsters.txt double

- Example conceptual output:

  - Round 1:
  - Mike vs Sully -> Winner: Sully
  - Randall vs Boo -> Winner: Randall

  - Winners Bracket Final:
  - Sully vs Randall -> Winner: Sully

  - Losers Bracket:
  - Mike vs Boo -> Winner: Mike
  - Mike vs Randall -> Winner: Randall

  - Final:
  - Sully vs Randall -> Champion: Sully
 
## Input Format

The input file is expected to contain a list of monsters.

### Example
---

- Mike, 75
- Sully, 95
- Randall, 85
- Boo, 60

### Rules
---
Each monster is expected to have the following attributes:

1. The monster's name (string, no space recommended)
2. The monster's power level (integer)
3. The monster with the higher power level is expected to win the game

In case both monsters have the same power level, the outcome is dependent on the program's implementation (i.e., either random or the order in which they are read).

## Implementation Details

### Core Concept – Tournament Tree
---

A binary tree represents the tournament:
- Each node represents a game
- Leaf nodes are the initial competitors
- Each parent node contains the winner of their children’s games

### Match Simulation
---

Each node in the tree contains:
- A game between two monsters
- Comparison of their scores
- The winner of the game goes to the next level
- Result propagates to the parent node

1. Single Elimination Mode

Behavior:
- Loser is removed from the tree
- Winner goes to the next level
- Ends when only one champion is left

2. Double Elimination Mode

Structure:
- Winners bracket: main tree structure
- Loser’s bracket: auxiliary structure

Behavior:
- First loss: move to loser’s bracket
- Second loss: removed from the tree

Final may involve one or two games depending on whether the winner of the loser’s bracket defeats the undefeated player.
