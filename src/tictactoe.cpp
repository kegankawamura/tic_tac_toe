#include <algorithm>
#include <string>
#include "gameplay.hpp"
#include "translateCmd.hpp"

bool findCommandOption( char** begin, char** end, const std::string& option )
{
    return std::find(begin, end, option) != end;

}

int main( int argc, char* argv[])
{

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
        displayHelp();
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
    }

    return gameplay();

}