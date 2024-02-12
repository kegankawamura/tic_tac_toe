#include <iostream>
#include <sstream>
#include "ultBoard.hpp"
#include <string>

UltBoard::UltBoard() : playHist{}
{
    clear();
}

void UltBoard::clear()
{
    for ( Board& b : grid)
    {
        b.clear();
    }
    overGrid.fill(Player::N);
    playHist.clear();
}

bool UltBoard::addMove(Player p, int orow, int ocol, int irow, int icol)
{

    checkRowBounds(orow);
    checkColBounds(ocol);

    int idx{rc2Idx(orow, ocol)};

    if (overGrid[idx] != Player::N || !grid[idx].addMove(p, irow, icol))
    {
        return false;
    }

    grid[idx].isGameOver(overGrid[idx]);
    playHist.push_back(idx);
    return true;
}

Player UltBoard::undoLastMove()
{
    if (playHist.empty())
    {
        return Player::N;
    }

    int lastMove{playHist.back()};

    Player p { grid[lastMove].undoLastMove() };

    grid[lastMove].isGameOver(overGrid[lastMove]);

    playHist.pop_back();

    return p;
}

void UltBoard::rmvMove(int orow, int ocol, int irow, int icol)
{

    checkRowBounds(orow);
    checkColBounds(ocol);

    int idx{rc2Idx(orow, ocol)};

    grid[idx].rmvMove(irow, icol);
    playHist.push_back(idx);
    
    return;
}

bool UltBoard::isGameOver(Player &winner) const
{

    Player p;

    //
    // Check if tie
    //
    bool tie{true};
    for (Player p : overGrid)
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
    for (int i = 1; i <= 3; ++i)
    {
        if ((p = checkVertical(i)) != Player::N || (p = checkHorizontal(i)) != Player::N)
        {
            winner = p;
            return true;
        }
    }
    for (int i = 1; i <= 2; ++i)
    {
        if ((winner = checkDiagonal(i)) != Player::N)
        {
            winner = p;
            return true;
        }
    }

    return false;
}

void UltBoard::displayBoard() const
{

    std::stringstream gridOut;

    gridOut << "     |     |     \n"
            << "  " << player2Char(overGrid[0]) << "  |  "
            << player2Char(overGrid[1]) << "  |  "
            << player2Char(overGrid[2]) << "  \n"
            << "_____|_____|_____\n";

    gridOut << "     |     |     \n"
            << "  " << player2Char(overGrid[3]) << "  |  "
            << player2Char(overGrid[4]) << "  |  "
            << player2Char(overGrid[5]) << "  \n"
            << "_____|_____|_____\n";

    gridOut << "     |     |     \n"
            << "  " << player2Char(overGrid[6]) << "  |  "
            << player2Char(overGrid[7]) << "  |  "
            << player2Char(overGrid[8]) << "  \n"
            << "     |     |     \n";

    std::cout << "\n"
              << gridOut.str() << std::endl;

    return;
}

//
// Print out the current state of the board
//
void UltBoard::displayFullBoard() const
{

    std::stringstream gridOut;

    gridOut << " " << player2Char(overGrid[0]) << " | "
            << player2Char(overGrid[1]) << " | "
            << player2Char(overGrid[2]) << "  |  "
            << "_____|_____|_____\n";

    gridOut << "     |     |     \n"
            << "  " << player2Char(overGrid[3]) << "  |  "
            << player2Char(overGrid[4]) << "  |  "
            << player2Char(overGrid[5]) << "  \n"
            << "_____|_____|_____\n";

    gridOut << "     |     |     \n"
            << "  " << player2Char(overGrid[6]) << "  |  "
            << player2Char(overGrid[7]) << "  |  "
            << player2Char(overGrid[8]) << "  \n"
            << "     |     |     \n";

    std::cout << "\n"
              << gridOut.str() << std::endl;

    return;
}

//
// --- Private Methods ---
//

void UltBoard::checkRowBounds(int row) const
{
    if (row < 1 || row > 3)
    {
        std::string msg{"Row must be 1, 2, or 3."};
        throw std::invalid_argument(msg);
    }
}
void UltBoard::checkColBounds(int col) const
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
inline int UltBoard::rc2Idx(int row, int col) const
{
    return 3 * (row - 1) + (col - 1);
}

//
// Check for a winner in a vertical column
//
Player UltBoard::checkVertical(int col) const
{
    // try
    // {
    checkColBounds(col);

    int firstIdx{col - 1};
    if (grid[firstIdx] == grid[firstIdx + 3] && grid[firstIdx] == grid[firstIdx + 6])
    {
        return grid[firstIdx];
    }

    return Player::N;
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
}

//
// Check for a winner in a horizontal row
//
Player UltBoard::checkHorizontal(int row) const
{
    // try
    // {
    checkRowBounds(row);

    int firstIdx{3 * (row - 1)};
    if (grid[firstIdx] == grid[firstIdx + 1] && grid[firstIdx] == grid[firstIdx + 2])
    {
        return grid[firstIdx];
    }

    return Player::N;
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
}

//
// Check for a winner on a diagonal
//
Player UltBoard::checkDiagonal(int diag) const
{
    // try
    // {
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
    // }
    // catch (const std::exception &e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
}