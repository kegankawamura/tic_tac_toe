#ifndef ULTBOARD_H
#define ULTBOARD_H

#include "board.hpp"

class UltBoard
{
public:


    //
    // Constructor
    //
    UltBoard();

    //
    // Clear the Board and its history
    //
    void clear();

    //
    // Add a move to the board
    // Return true if move is successful
    //
    bool addMove(Player p, int orow, int ocol, int irow, int icol);

    //
    // Undo the last move made
    //
    Player undoLastMove();

    //
    // Remove a move from the board
    // If there is no move in the specified grid, nothing happens.
    //
    void rmvMove(int orow, int ocol, int irow, int icol);

    //
    // Returns the last move in the play history.
    //
    std::array<int,4> lastMove();


    //
    // Check if there is a Tic-Tac-Toe winner
    // Return Player::N if no winner
    //
    bool isGameOver(Player &winner) const;

    //
    // Check if there is a Tic-Tac-Toe winner in row
    // 'orow' and column 'ocol'
    // Return Player::N if no winner
    //
    bool isGameOver(int orow, int ocol, Player &winner) const;

    //
    // Print out the current state of the board
    //
    void displayBoard() const;

    //
    // Print out the current state of the board
    //
    void displayInnerBoard(int row, int col) const;

    //
    // Print out the current state of the board
    //
    void displayFullBoard() const;

private:
    //
    // Throw an exception if row is out of range
    //
    void checkRowBounds(int row) const;

    //
    // Throw an exception if column is out of range
    //
    void checkColBounds(int col) const;

    //
    // Convert a (row, col) pair to the grid index
    //
    int rc2Idx(int row, int col) const;

    //
    // Check if there's a winner along column, row, or diagonal
    //
    Player checkVertical(int col) const;
    Player checkHorizontal(int row) const;
    Player checkDiagonal(int diag) const;

    //
    // Translate player to character
    //
    char player2Char(Player p) const;

    //
    // Keeps track of the history of the game
    // Specifically, addMove and rmvMove
    //
    std::vector<int> playHist;

    //
    // The grid
    //
    std::array<Board, 9> grid;

    std::array<Player, 9> overGrid;
};

#endif