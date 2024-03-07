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
    std::string normStr{normalizeStr(inStr)};

    if (normStr.length() >= 7 && normStr.substr(0, 7) == "display")
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

void displayUsage()
{
    static const std::string help{
        "\n\t--- How to use TicTacToe ---\n\n"
        "This program allows you to play Tic-Tac-Toe through the terminal\n"
        "with another player. You can call the program without any flags to\n"
        "play regaular Tic-Tac-Toe with a friend next to you.\n\n"
        "Usage:\tTicTacToe <flags>\n\n"
        "Flag List:\n"
        "\t-h, -help     : Display this message.\n\n"
        "\t-q, -quiet    : Keep the Tic-Tac-Toe board from displaying after\n"
        "\t                every move.\n\n"
        "\t-s, -solo     : Play against an AI (IN DEVELOPMENT)\n\n"
        "\t-u, -ultimate : Play ultimate Tic-Tac-Toe\n\n"
    };

    std::cout << help << std::endl;
}

void displayHelp()
{
    static const std::string help{
        "\n\t--- Welcome to Tic-Tac-Toe! ---\n\n"
        "This game involves two players taking turns marking \n"
        "the spaces in a three-by-three grid with X or O.\n\n"
        "The goal of this game is to mark three spaces in the grid\n"
        "such that they form either a vertical, horizontal,\n"
        "or diagonal row by your mark.\n"
        "\n\t--- How to play Tic-Tac-Toe ---\n\n"
        "You can make moves on the grid by specifying a square\n"
        "on the grid where you would like to mark an X or O.\n\n"
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

void displayUltHelp()
{

    static const std::string help{
        "\n\t--- Welcome to Ultimate Tic-Tac-Toe! ---\n\n"
        "This game involves two players taking turns marking \n"
        "the spaces in nine different three-by-three grids with X or O.\n"
        "We'll refer to these grids as the `inner grids`.\n"
        "These nine inner grids are themselves organized into a\n"
        "three-by-three grid, which we'll refer to as the outer grid.\n\n"
        "The goal of this game is to mark three spaces in the outer grid\n"
        "such that they form either a vertical, horizontal,\n"
        "or diagonal row by your mark.\n"
        "\n\t--- How to play Ultimate Tic-Tac-Toe ---\n\n"
        "You can make moves on the inner grid by specifying a square\n"
        "on the grid where you would like to mark an X or O.\n\n"
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
        "For example, to make a move in the top left corner of the top left\n"
        "inner grid, type\n\n"
        "\t'A1 A1'\n\n"
        "Once a vertical, horizontal, or diagonal row is marked by an\n"
        "X or O in the inner grid, the outer grid's square in which the\n"
        "inner grid lies is marked by an X or O (whichever symbol won the\n"
        "inner grid).\n\n"
        "The move made by the previous player constrains the moves the next\n"
        "player can make. For example, if the previous player marks 'A1' in\n"
        "an inner grid, the next player must play on the inner grid within\n"
        "'A1' in the outer grid. In the case that the outer 'A1' (in this\n"
        "example) already has a completed inner grid, the player may choose\n"
        "to play on any other grid.\n\n"
        "You may also type other commands before making a move to\n"
        "manipulate the state of the game. These commands are\n"
        "described below:\n\n"
        "\t'help'         -   Display this message.\n\n"
        "\t'exit'         -   Exits the interactive tic tac toe gamplay.\n\n"
        "\t'display'      -   Displays the current state of the outer tic tac\n"
        "                     toe board.\n\n"
        "\t'display full' -   Displays the current state of the full tic tac\n"
        "                     toe board.\n\n"
        "\t'display [COORDINATE]'\n"
        "                 -   Displays the current state of the inner grid\n"
        "                     tic tac toe board specified by [COORDINATE].\n\n"
        "\t'restart'      -   Start a new game without exiting the\n"
        "                     interactive gamplay.\n\n"
        "\t'undo'         -   Undo the last move made.\n\n"};

    std::cout << help << std::endl;
}

std::pair<int, int> cmd2Move(const std::string &inStr)
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