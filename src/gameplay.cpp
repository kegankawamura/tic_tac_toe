#include <iostream>
#include <string>
#include "gameplay.hpp"
#include "board.hpp"
#include "translateCmd.hpp"

void displayHelp()
{
    static const std::string help {
        "How to play Tic-Tac-Toe"
    };

    std::cout << help << std::endl;
}


int gameplay()
{

    //
    // Create Board object
    //
    Board board();

    displayHelp();

    std::string cmd;

    while (true)
    {
        std::cout << ">";
        std::cin >> cmd;

        //
        // Create input parser(s) in translateCmd.cpp
        // is***(cmd) can help define the commands
        // supported by the gameplay
        //

        if (cmd == "exit")
        {
            return 0;
        }

        if (cmd == "help")
        {
            displayHelp();
            continue;
        }
    }
}