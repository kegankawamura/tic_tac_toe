#include "translateCmd.hpp"

#include<iostream>
#include<map>
#include<utility
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


std::pair<uint8_t, uint8_t> cmd2Move(const std::string& inStr)
{
    if (inStr.size() != 2)
    {
        std::string msg{ "Move command should have exactly two characters." };
        throw std::invalid_argument(msg);
    }

    static const std::map<char, uint8_t> c2mRow{{'a', 1}, {'b', 2}, {'c', 3}};
    static const std::map<char, uint8_t> c2mCol{{'1', 1}, {'2', 2}, {'3', 3}};

    auto rowIter{c2mRow.find(inStr[0])};
    auto colIter{c2mCol.find(inStr[1])};

    if (rowIter == c2mRow.end() || colIter == c2mCol.end())
    {
        std::string msg{"Move command should have a letter 'a', 'b', or 'c' "
                        "followed by a number '1', '2', or '3'." };
        throw std::invalid_argument(msg);
    }

    return std::make_pair(*rowIter, *colIter);
}