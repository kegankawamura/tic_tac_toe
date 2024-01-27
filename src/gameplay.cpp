#include <iostream>
#include <string>
#include "gameplay.hpp"
#include "board.hpp"
#include "translateCmd.hpp"

static const std::string P1{"Player 1"};
static const std::string P2{"Player 2"};

std::string nextPlayer(const std::string &p1p2)
{
    std::string otherPlayerStr;

    if (p1p2 == P1)
    {
        otherPlayerStr = P2;
    }
    else if (p1p2 == P2)
    {
        otherPlayerStr = P1;
    }
    else
    {
        std::string msg{"Not a valid player string."};
        throw std::invalid_argument(msg);
    }
    return otherPlayerStr;
}

Player askForXO()
{
    std::string playerStr;
    do
    {
        std::cout
            << P1
            << ", please choose 'x' or 'o': ";
        std::cin >> playerStr;
        if (playerStr == "x" || playerStr == "o")
        {
            break;
        }
    } while (true);

    Player playerEnum;

    if (playerStr == "x")
    {
        playerEnum = Player::X;
    }

    if (playerStr == "o")
    {
        playerEnum = Player::O;
    }

    return playerEnum;
}

int gameplay()
{
    std::string playerStr { P1 };
    Player playerEnum { askForXO() };

    //
    // Create Board object
    //
    Board board;

    displayHelp();

    std::string cmd;

    while (true)
    {
        std::cout << playerStr <<  " > ";
        std::cin >> cmd;

        //
        // Create input parser(s) in translateCmd.cpp
        // is***(cmd) can help define the commands
        // supported by the gameplay
        //

        cmd = normalizeStr(cmd);

        if (isExit(cmd))
        {
            return 0;
        }
        else if (isHelp(cmd))
        {
            displayHelp();
            continue;
        }
        else if (isMove(cmd))
        {
            // TODO: translate command to move
            //       add move to board
            playerStr = otherPlayerStr(playerStr);
            playerEnum = otherPlayerEnum(playerEnum);
        }
        else if (isUndo(cmd))
        {
            board.undoLastMove();
            // TODO: return move so we know how to set the next player
        }
        else if (isDisp(cmd))
        {
            board.displayBoard();
        }
        else if (isRestart(cmd))
        {
            board.clear();
            displayHelp();
            playerStr = P1;
            Player playerEnum{askForXO()};
        }
        else
        {
            // Not a valid command
            std::cout << "\tHmm... command not recognized. Try again.\n"
                      << "\tType 'help' to list the valid commands."
                      << std::endl;
        }

                    
    }
}
