#include <algorithm>
#include <iostream>
#include <string>
#include "gameplay.hpp"
#include "translateCmd.hpp"

//
// Search for a flag within the string array. 
//
bool findCommandOption( char** begin, char** end, const std::string& option )
{
    return std::find(begin, end, option) != end;
}

//
// Main TicTacToe function.
//
int main( int argc, char* argv[])
{

    std::unordered_set<int> opt;
    int numOpt{ 0 };
    //
    // -h, -help
    // Show instructions
    //
    if ( findCommandOption(argv, argv+argc, "-h") || 
         findCommandOption(argv, argv+argc, "-help") )
    {
        //
        // Show instructions
        //
        displayUsage();
        return 0;
    }

    //
    // -s, -solo
    // Play against AI
    //
    if ( findCommandOption(argv, argv+argc, "-s") || 
         findCommandOption(argv, argv+argc, "-solo") )
    {
        //
        // Play against AI
        //
        std::cout << "Solo mode is currently in development."
                  << "Playing the default mode instead."
                  << std::endl;;
        numOpt++;
    }

    //
    // -q, -quiet
    // Don't show grid every time a move is made
    //
    if ( findCommandOption(argv, argv+argc, "-q") || 
         findCommandOption(argv, argv+argc, "-quiet") )
    {
        //
        // Don't show grid every time a move is made
        //
        opt.insert(QUIET);
        numOpt++;
    }

    //
    // -u, -ultimate
    // Play ultimate tictactoe
    //
    if ( findCommandOption(argv, argv+argc, "-u") || 
         findCommandOption(argv, argv+argc, "-ultimate") )
    {
        //
        // Play ultimate tictactoe
        //
        opt.insert(ULTIMATE);
        numOpt++;
    }

    if (numOpt != argc - 1)
    {
        std::cout << "At least one invalid command argument detected: " << std::endl;
        for (int i = 1; i < argc; ++i)
        {
            std::cout << "\t" << argv[i] << std::endl;
        }
        return 1;
    }

    return gameplay(opt);

}