#include "translateCmd.hpp"

#include<iostream>
#include<vector>


std::string normalizeStr(std::string strIn)
{
    strIn.erase(std::remove(strIn.begin(), strIn.end(), ' '), strIn.end());
    std::transform(
        strIn.begin(),
        strIn.end(),
        strIn.begin(),
        [](unsigned char c){return std::tolower(c); } );
    return strIn;
}

inline bool isExit(const std::string& inStr)
{
    //
    // Make it case insensitive?
    // Lower case the input string?
    // Trim whitespace?
    //
    return normalizeStr(inStr) == "exit";
}

inline bool isHelp(const std::string& inStr)
{
    return normalizeStr(inStr) == "help";
}

bool isMove(const std::string& inStr)
{
    std::string moveStr { normalizeStr(inStr) };

    if (moveStr.size() == 2)
    {
        char first{moveStr[0]};
        char second{moveStr[1]};
        if ((first == 'a' || first == 'b' || first == 'c') && (second == '1' || second == '2' || second == '3'))
        {
            return true;
        }
    }
    return false;
}

inline bool isUndo(const std::string& inStr)
{
    return normalizeStr(inStr) == "undo";
}

inline bool isDisp(std::string inStr)
{
    return normalizeStr(inStr) == "display";
}

bool isRestart(std::string inStr)
{
    return normalizeStr(inStr) == "restart";
}

void displayHelp()
{
    static const std::string help{
        "How to play Tic-Tac-Toe"};

    std::cout << help << std::endl;
}
