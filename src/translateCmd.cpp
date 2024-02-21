#include "translateCmd.hpp"

#include<array>
#include<iostream>
#include<map>
#include<utility>
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

bool isExit(const std::string& inStr)
{
    //
    // Make it case insensitive?
    // Lower case the input string?
    // Trim whitespace?
    //
    return normalizeStr(inStr) == "exit";
}

bool isHelp(const std::string& inStr)
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

bool isUltMove(const std::string &inStr)
{
    std::string moveStr{normalizeStr(inStr)};

    if (moveStr.size() == 4)
    {
        if(isMove(moveStr.substr(0,2)) && isMove(moveStr.substr(2,2)))
        {
            return true;
        }
    }
    return false;
}

bool isUndo(const std::string &inStr)
{
    return normalizeStr(inStr) == "undo";
}

bool isDisp(const std::string &inStr)
{
    return normalizeStr(inStr) == "display";
}

bool isUltDisp(const std::string &inStr)
{
    std::string normStr { normalizeStr(inStr) };
    if (normStr.substr(0, 7) == "display")
    {
        if (isMove(normStr.substr(7)) || normStr.substr(7) == "full")
        {
            return true;
        }
    }
    return false;
}

bool isRestart(const std::string &inStr)
{
    return normalizeStr(inStr) == "restart";
}

void displayHelp()
{
    static const std::string help{
        "\n\t--- Welcome to Tic-Tac-Toe! ---\n\n"
        "This game involves two players taking turns marking \n"
        "the spaces in a three-by-three grid with X or O.\n\n"
        "The goal of this game is to mark three spaces in the grid\n"
        "such that they form either a vertical, horizontal,\n"
        "or diagonal row.\n"
        "\n\t--- How to play Tic-Tac-Toe ---\n\n"
        "You can make moves on the grid by specifying a square\n"
        "on the grid where you would like to make an X or O.\n\n"
        "Rows are specified by 'A', 'B', or 'C'.\n"
        "Columns are specified by '1', '2', or '3'.\n\n"
        "\t    1     2     3   \n"
        "\t       |     |      \n"
        "\tA      |     |      \n"
        "\t  _____|_____|_____ \n"
        "\t       |     |      \n"
        "\tB      |     |      \n"
        "\t  _____|_____|_____ \n"
        "\t       |     |      \n"
        "\tC      |     |      \n"
        "\t       |     |      \n\n"
        "For example, to make a move in the top left corner, type\n\n"
        "\t'A1'\n\n"
        "You may also type other commands before making a move to\n"
        "manipulate the state of the game. These commands are\n"
        "described below:\n\n"
        "\t'help'    -   Display this message.\n\n"
        "\t'exit'    -   Exits the interactive tic tac toe gamplay.\n\n"
        "\t'display' -   Displays the current state of the tic tac toe board.\n\n"
        "\t'restart' -   Start a new game without exiting the interactive gamplay.\n\n"
        "\t'undo'    -   Undo the last move made.\n\n"};

    std::cout << help << std::endl;
}


std::pair<int, int> cmd2Move(const std::string& inStr)
{
    if (inStr.size() != 2)
    {
        std::string msg{ "Move command should have exactly two characters." };
        throw std::invalid_argument(msg);
    }

    static const std::map<char, int> c2mRow{{'a', 1}, {'b', 2}, {'c', 3}};
    static const std::map<char, int> c2mCol{{'1', 1}, {'2', 2}, {'3', 3}};

    auto rowIter{c2mRow.find(inStr[0])};
    auto colIter{c2mCol.find(inStr[1])};

    if (rowIter == c2mRow.end() || colIter == c2mCol.end())
    {
        std::string msg{"Move command should have a letter 'a', 'b', or 'c' "
                        "followed by a number '1', '2', or '3'." };
        throw std::invalid_argument(msg);
    }

    return std::make_pair(rowIter->second, colIter->second);
}

std::array<int, 4> ultCmd2Move(const std::string &inStr)
{
    if (inStr.size() != 4)
    {
        std::string msg{"Move command should have exactly four characters."};
        throw std::invalid_argument(msg);
    }

    auto outerMove{cmd2Move(inStr.substr(0, 2))};
    auto innerMove{cmd2Move(inStr.substr(2, 2))};

    std::array<int, 4> ultMove { outerMove.first, outerMove.second,
                                 innerMove.first, innerMove.second };

    return ultMove;
}