#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <vector>

enum Player{ O, X, N };

Player otherPlayerEnum(Player xo);

class Board
{
public:

    //
    // Constants identifying the type of a move
    //
    static constexpr bool RMV{false};
    static constexpr bool ADD{true};

    //
    // Struct describing a move in Tic-Tac-Toe
    //
    struct Move
    {
        Player p;       // Player
        bool type;      // Add or Remove
        uint8_t row;    // Row on grid
        uint8_t col;    // Column on grid
    };

    //
    // Clear the Board and its history
    //
    void clear();

    //
    // Add a move to the board
    // Return true if move is successful
    //
    bool addMove(Player p, uint8_t row, uint8_t col);

    //
    // Undo the last move made
    //
    Player undoLastMove();

    //
    // Remove a move from the board
    // If there is no move in the specified grid, nothing happens.
    //
    void rmvMove(uint8_t row, uint8_t col);


    //
    // Check if there is a Tic-Tac-Toe winner
    // Return Player::N if no winner
    //
    bool isGameOver(Player& winner);

    //
    // Print out the current state of the board
    //
    void displayBoard();


private:

    //
    // Throw an exception if row is out of range
    //
    void checkRowBounds(uint8_t row);

    //
    // Throw an exception if column is out of range
    //
    void checkColBounds(uint8_t col);

    //
    // Convert a (row, col) pair to the grid index
    //
    uint8_t rc2Idx(uint8_t row, uint8_t col);

    //
    // Check if there's a winner along column, row, or diagonal
    //
    Player checkVertical(uint8_t col);
    Player checkHorizontal(uint8_t row);
    Player checkDiagonal(uint8_t diag);

    //
    // Translate player to character
    //
    char player2Char(Player p);


    //
    // Keeps track of the history of the game
    // Specifically, addMove and rmvMove
    //
    std::vector<Move> playHist;

    //
    // The grid
    //
    std::array<Player, 9> grid;

};

#endif