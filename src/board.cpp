#include <iostream>
#include <sstream>
#include "board.hpp"

Player otherPlayerEnum(Player xo)
{
    switch(xo)
    {
        case Player::X:
            return Player::O;

        case Player::O:
            return Player::X;

        default:
            return Player::N;
    }
}

Board::Board() : playHist{}
{
    clear();
}

void Board::clear()
{
    std::fill(grid.begin(), grid.end(), Player::N);
    playHist.clear();
}

bool Board::addMove(Player p, uint8_t row, uint8_t col)
{
    try
    {
        checkRowBounds(row);
        checkColBounds(col);

        uint8_t idx{rc2Idx(row, col)};

        if ( grid[idx] != Player::N)
        {
            return false;
        }

        Move add{p, ADD, row, col};
        grid[idx] = p;
        playHist.push_back(add);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}
Player Board::undoLastMove()
{
    try
    {
        if (playHist.empty())
        {
            return Player::N;
        }

        Move lastMove { playHist.back() };
        if (lastMove.type == ADD)
        {
            grid[rc2Idx(lastMove.row, lastMove.col)] = Player::N;
        }
        else
        {
            grid[rc2Idx(lastMove.row, lastMove.col)] = lastMove.p;
        }

        playHist.pop_back();

        return lastMove.p;

        // Consider returning Move?
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Board::rmvMove(uint8_t row, uint8_t col)
{
    try
    {
        checkRowBounds(row);
        checkColBounds(col);

        uint8_t idx{rc2Idx(row, col)};
        Move rmv {grid[idx], RMV, row, col};

        grid[idx] = Player::N;
        playHist.push_back( rmv );
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

bool Board::isGameOver(Player& winner)
{
    //
    // Need to check 8 configurations
    // 3 Vertical
    // 3 Horizontal
    // 2 Diagonal
    //

    Player p;

    //
    // Check if tie
    //
    bool tie { true };
    for (Player p : grid)
    {
        if (p == Player::N)
        {
            tie = false;
            break;
        }
    }

    if (tie)
    {
        winner = Player::N;
        return true;
    }

    //
    // Check if winner
    //
    for (uint8_t i = 1; i <= 3; ++i)
    {
        // winner = checkVertical(i);
        if ((p = checkVertical(i)) != Player::N || (p = checkHorizontal(i)) != Player::N)
        {
            winner = p;
            return true;
        }
        // winner = checkHorizontal(i);
        // if (winner != Player::N)
        // {
        //     return winner;
        // }
    }
    for (uint8_t i = 1; i <= 2; ++i)
    {
        if ((winner = checkDiagonal(i)) != Player::N)
        {
            winner = p;
            return true;
        }
    }

    return false;
}

void Board::displayBoard()
{

    std::stringstream gridOut;

    gridOut << "   |   |   \n"
            << " " << player2Char(grid[0]) << " | "
            << player2Char(grid[1]) << " | "
            << player2Char(grid[2]) << " \n"
            << "___|___|___\n";

    gridOut << "   |   |   \n"
            << " " << player2Char(grid[3]) << " | "
            << player2Char(grid[4]) << " | "
            << player2Char(grid[5]) << " \n"
            << "___|___|___\n";

    gridOut << "   |   |   \n"
            << " " << player2Char(grid[6]) << " | "
            << player2Char(grid[7]) << " | "
            << player2Char(grid[8]) << " \n"
            << "   |   |   \n";

    std::cout << gridOut.str() << std::endl;

    return;
}

//
// --- Private Methods ---
//

void Board::checkRowBounds(uint8_t row)
{
    if (row < 1 || row > 3)
    {
        std::string msg{"Row must be 1, 2, or 3."};
        throw std::invalid_argument(msg);
    }
}
void Board::checkColBounds(uint8_t col)
{
    if (col < 1 || col > 3)
    {
        std::string msg{"Column must be 1, 2, or 3."};
        throw std::invalid_argument(msg);
    }
}

//
// Translate (row, col) to the grid index
//
inline uint8_t Board::rc2Idx(uint8_t row, uint8_t col)
{
    return 3*(row-1) + (col-1);
}

//
// Check for a winner in a vertical column 
//
Player Board::checkVertical(uint8_t col)
{
    try
    {
        checkColBounds(col);

        uint8_t firstIdx{col - 1};
        if (grid[firstIdx] == grid[firstIdx + 3] && grid[firstIdx] == grid[firstIdx + 6])
        {
            return grid[firstIdx];
        }

        return Player::N;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

//
// Check for a winner in a horizontal row
//
Player Board::checkHorizontal(uint8_t row)
{
    try
    {
        checkRowBounds(row);

        uint8_t firstIdx{3 * (row - 1)};
        if (grid[firstIdx] == grid[firstIdx + 1] && grid[firstIdx] == grid[firstIdx + 2])
        {
            return grid[firstIdx];
        }

        return Player::N;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

//
// Check for a winner on a diagonal
//
Player Board::checkDiagonal(uint8_t diag)
{
    try
    {
        if (diag == 1)
        {
            if (grid[0] == grid[4] && grid[0] == grid[8])
            {
                return grid[0];
            }
        }
        else if (diag == 2)
        {
            if (grid[2] == grid[4] && grid[2] == grid[6])
            {
                return grid[2];
            }
        }
        else
        {
            std::string msg{"Diagonal must be 1 o 2."};
            throw std::invalid_argument(msg);
        }

        return Player::N;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

char Board::player2Char(Player p)
{
    switch(p)
    {
        case Player::N:
            return ' ';

        case Player::O:
            return 'O';

        case Player::X:
            return 'X';
    }
}