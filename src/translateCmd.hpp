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
bool isHelp(const std::string &inStr);

//
// Check if string indicates a valid move command
//
bool isMove(const std::string& inStr);

//
// Check if string indicates a valid move command
//
bool isUltMove(const std::string &inStr);

//
// Undo last move
//
bool isUndo(const std::string &inStr);

//
// Display board
//
bool isDisp(const std::string &inStr);

//
// Display board
//
bool isUltDisp(const std::string &inStr);

//
// Restart game without exiting
//
bool isRestart(const std::string &inStr);

//
// Display Program Usage instrucitons
//
void displayUsage();

//
// Help instructions
//
void displayHelp();

//
// Help instructions
//
void displayUltHelp();

//
// Translate a valid move command string to
// a (row, col) pair
//
std::pair<int, int> cmd2Move(const std::string& inStr);

//
// Translate a valid move command string to
// a (row, col) pair
//
std::array<int, 4> ultCmd2Move(const std::string &inStr);

#endif