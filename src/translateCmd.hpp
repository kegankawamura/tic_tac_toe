#ifndef TRANSLATECMD_H
#define TRANSLATECMD_H

#include <utility>

//
// Check if string indicates a valid move command
//
bool isMove(std::string inStr);

//
// Translate a valid move command string to
// a (row, col) pair
//
std::pair<uint8_t, uint8_t> cmd2Move(std::string inStr);

#endif