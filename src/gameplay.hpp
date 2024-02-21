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

int gameplay(const std::unordered_set<int>& opt);

int ultimateGameplay(const std::unordered_set<int> &opt);

std::string otherPlayerStr(const std::string& p1p2);

Player askForXO();

bool askForRestart();



#endif
