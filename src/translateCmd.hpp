#ifndef TRANSLATECMD_H
#define TRANSLATECMD_H

#include <utility>

//
// Exit command
//
bool isExit(std::string inStr);

//
// Help command
//
bool isHelp(std::string inStr);

//
// Check if string indicates a valid move command
//
bool isMove(std::string inStr);

//
// Undo last move
//
bool isUndo(std::string inStr);

//
// Display board
//
bool isDisp(std::string inStr);

//
// Restart game without exiting
//
bool isRestart(std::string inStr);

//
// Help instructions
//
void displayHelp();

//
// Translate a valid move command string to
// a (row, col) pair
//
std::pair<uint8_t, uint8_t> cmd2Move(std::string inStr);

#endif