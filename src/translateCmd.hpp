#ifndef TRANSLATECMD_H
#define TRANSLATECMD_H

#include <utility>

//
// Normalize string
//
std::string normalizeStr(std::string strIn);


//
// Exit command
//
bool isExit(const std::string& inStr);

//
// Help command
//
bool isHelp(const std::string& inStr);

//
// Check if string indicates a valid move command
//
bool isMove(const std::string& inStr);

//
// Undo last move
//
bool isUndo(const std::string& inStr);

//
// Display board
//
bool isDisp(const std::string& inStr);

//
// Restart game without exiting
//
bool isRestart(const std::string& inStr);

//
// Help instructions
//
void displayHelp();

//
// Translate a valid move command string to
// a (row, col) pair
//
std::pair<uint8_t, uint8_t> cmd2Move(const std::string& inStr);

#endif