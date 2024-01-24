#include "translateCmd.hpp"

#include<iostream>

inline bool isExit(std::string inStr)
{
    //
    // Make it case insensitive?
    // Lower case the input string?
    // Trim whitespace?
    //
    return inStr == "exit";
}

inline bool isHelp(std::string inStr)
{
    return inStr == "help";
}

bool isMove(std::string inStr)
{
    if(inStr.size() == 2)
    {
        char first { inStr[0] };
        char second {inStr[1] };
        if ((first == 'a' || first == 'b' || first == 'c') && (second == '1' || second == '2' || second == '3'))
        {
            return true;
        }
    }
    return false;
}

inline bool isUndo(std::string inStr)
{
    return inStr == "undo";
}

inline bool isDisp(std::string inStr)
{
    return inStr == "display";
}

bool isRestart(std::string inStr)
{
    return inStr == "restart";
}

void displayHelp()
{
    static const std::string help{
        "How to play Tic-Tac-Toe"};

    std::cout << help << std::endl;
}
