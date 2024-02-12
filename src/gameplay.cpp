#include <iostream>
#include <string>
#include "gameplay.hpp"
#include "board.hpp"
#include "translateCmd.hpp"

static const std::string P1{"Player 1"};
static const std::string P2{"Player 2"};

std::string otherPlayerStr(const std::string &p1p2)
{
    std::string otherPlayer;

    if (p1p2 == P1)
    {
        otherPlayer = P2;
    }
    else if (p1p2 == P2)
    {
        otherPlayer = P1;
    }
    else
    {
        std::string msg{"Not a valid player string."};
        throw std::invalid_argument(msg);
    }
    return otherPlayer;
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

bool askForRestart()
{
    std::string cmd;
    std::cout << "\nPlay again? (y/n): ";
    std::cin >> cmd;

    return normalizeStr(cmd) == "y";
}

int gameplay(const std::unordered_set<Options> &opt)
{

    if (opt.find(Options::ULTIMATE) != opt.end())
    {
        return ultimateGameplay(opt);
    }

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

        cmd = normalizeStr(cmd);

        if (isExit(cmd))
        {
            return 0;
        }
        else if (isHelp(cmd))
        {
            displayHelp();
        }
        else if (isMove(cmd))
        {
            auto move { cmd2Move(cmd) };
            if ( !board.addMove(playerEnum, move.first, move.second) )
            {
                std::cout << "\tInvalid move. Try again." << std::endl;
            }
            else
            {
                if (opt.find(Options::QUIET) == opt.end())
                {
                    board.displayBoard();
                }
                Player winner;
                bool gameOver = board.isGameOver(winner);
                if (gameOver)
                {
                    if (winner != Player::N)
                    {
                        std::cout << playerStr << " wins the game!" << std::endl;
                    }
                    else
                    {
                        std::cout << "It's a tie!" << std::endl;
                    }
                    if (askForRestart())
                    {
                        board.clear();
                        displayHelp();
                        playerStr = P1;
                        playerEnum = askForXO();
                    }
                    else
                    {
                        std::cout << "Thanks for playing!" << std::endl;
                        return 0;
                    }
                }
                else
                {
                    playerStr = otherPlayerStr(playerStr);
                    playerEnum = otherPlayerEnum(playerEnum);
                }
            }
        }
        else if (isUndo(cmd))
        {
            Player last = board.undoLastMove();
            if (last == Player::N)
            {
                std::cout << "\tNo moves to undo!" << std::endl;
            }
            else
            {
                playerStr = otherPlayerStr(playerStr);
                playerEnum = last;
            }
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
            playerEnum = askForXO();
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

int ultimateGameplay(const std::unordered_set<Options> &opt)
{

    std::string playerStr{P1};
    Player playerEnum{askForXO()};
}