#ifndef GAMEPLAY_H
#define GAMEPLAY_H

//
// This header file defines the top-level functionality required
// for a standard game of tic-tac-toe. It shall define the interface
// between the player and the program.
//

#include <string>
#include "board.hpp"
#include <unordered_set>

//
// int so we can use for Hash.
//
static const int QUIET = 0;
static const int AI = 1;
static const int ULTIMATE = 2;

//
// Main gameplay function.
//
int gameplay(const std::unordered_set<int>& opt);

//
// Gameplay for ultimate tic-tac-toe.
//
int ultimateGameplay(const std::unordered_set<int> &opt);

//
// Helper function to swap strings between players.
//
std::string otherPlayerStr(const std::string& p1p2);

//
// Prompt player for 'X' or 'O'.
//
Player askForXO();

//
// Prompt player on whether to restart a new game.
//
bool askForRestart();


#endif
