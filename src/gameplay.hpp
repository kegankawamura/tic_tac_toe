#ifndef GAMEPLAY_H
#define GAMEPLAY_H

//
// This header file defines the top-level functionality required
// for a standard game of tic-tac-toe. It shall define the interface
// between the player and the program.
//

#include <string>
#include "board.hpp"

int gameplay();

std::string otherPlayerStr(const std::string& p1p2);

Player askForXO();

bool askForRestart();



#endif
