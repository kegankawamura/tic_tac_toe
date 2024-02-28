#include <iostream>
#include <string>
#include "gameplay.hpp"
#include "board.hpp"
#include "ultBoard.hpp"
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

        std::getline(std::cin, playerStr);
        // std::cin >> playerStr;
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

int gameplay(const std::unordered_set<int> &opt)
{

    std::cout << (opt.find(ULTIMATE) != opt.end()) << std::endl;
    if (opt.find(ULTIMATE) != opt.end())
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
        std::cout << playerStr << " > ";
        // std::cin >> cmd;
        std::getline(std::cin, cmd);

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
                if (opt.find(QUIET) == opt.end())
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

int ultimateGameplay(const std::unordered_set<int> &opt)
{

    std::string playerStr{P1};
    Player playerEnum{askForXO()};

    //
    // Create Board object
    //
    UltBoard board;

    displayUltHelp();

    std::string cmd;

    std::pair<int,int> prevMove { 0, 0 };

    while (true)
    {
        std::cout << playerStr << " > ";
        // std::cin >> cmd;
        std::getline(std::cin, cmd);

        cmd = normalizeStr(cmd);

        if (isExit(cmd))
        {
            return 0;
        }
        else if (isHelp(cmd))
        {
            displayUltHelp();
        }
        else if (isUltMove(cmd))
        {
            Player gridWinner;
            auto move{ultCmd2Move(cmd)};
            bool gridGameOver{board.isGameOver(prevMove.first, prevMove.second, gridWinner)};
            bool isPrevInNextOut { prevMove.first == move[0] && prevMove.second == move[1] };

            if (isPrevInNextOut && gridGameOver)
            {
                std::cout << "\tInvalid move.\n\tRow " << move[0] << " column " 
                          << move[1]
                          << " already has a winner. Make a move in any "
                          << "grid that doesn't have a winner yet."
                          << std::endl;
                continue;
            }
            else if (prevMove.first != 0 && prevMove.second != 0 &&  (!isPrevInNextOut && !gridGameOver))
            {
                std::cout << "\tInvalid move.\n\tYou must select row "
                          << prevMove.first << " and column "
                          << prevMove.second << " for the outer board."
                          << std::endl;
                continue;
            }
            if (!board.addMove(playerEnum, move[0], move[1], move[2], move[3] ))
            {
                std::cout << "\tInvalid move. Try again." << std::endl;
            }
            else
            {
                auto lastBoardMv{board.lastMove()};
                prevMove.first = move[2];
                prevMove.second = move[3];

                if (opt.find(QUIET) == opt.end())
                {
                    board.displayFullBoard();
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
                auto lastBoardMv{board.lastMove()};
                prevMove.first = lastBoardMv[2];
                prevMove.second = lastBoardMv[3];
                playerStr = otherPlayerStr(playerStr);
                playerEnum = last;
            }
        }
        else if (isDisp(cmd))
        {
            board.displayBoard();
        }
        else if (isUltDisp(cmd))
        {
            if (cmd.substr(7) == "full")
            {
                board.displayFullBoard();
            }
            else
            {
                auto gridSpace{cmd2Move(cmd.substr(7, 2))};
                board.displayInnerBoard(gridSpace.first, gridSpace.second);
            }
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