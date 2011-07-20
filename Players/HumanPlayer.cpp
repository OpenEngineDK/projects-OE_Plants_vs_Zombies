#include "HumanPlayer.h"

#include <iostream>
#include <cstdlib>

void HumanPlayer::update()
{
    std::string s;

    while(true)
    {
        std::cout << "plants> ";
        std::cin >> s;

        if(!s.compare("exit") or !s.compare("quit") or std::cin.eof())
        {
            std::cout << "Thanks for playing!" << std::endl;
            exit(0);
        }

        if (!s.compare("help"))
        {
            print_help();
            continue;
        }
        if (!s.compare("board"))
        {
            print_board();
            continue;
        }
        if (!s.compare("skip"))
        {
            return;
        }

        if (!s.compare("new") or !s.compare("reset"))
        {
            board->newGame();
			continue;
		}

        bool move_valid = board->parse_move(s);
        if(move_valid)
        {
            bool move_made = board->make_move(s);
            if(move_made)
            {
                return;
            }
            else
            {
                std::cout << "Plants can't be stacked ontop of each other." << std::endl;
            }
        }
        else
        {
            std::cout << "Illegal move." << std::endl;
            continue;
        }
    }
}

void HumanPlayer::print_help()
{
    std::cout << "board - display the board" << std::endl;
    std::cout << "exit/quit - exit the program" << std::endl;
    std::cout << "new/reset - start a new game" << std::endl;
    std::cout << "Enter moves in coordinate notation, e.g.: e2->sunflower, e7->PeaShooter" << std::endl;
}

void HumanPlayer::print_board()
{
    //Assume square map
    unsigned int numLines   = board->numLines();
    unsigned int numColumns = board->numColumns();

    std::cout << ":::PLANT MAP:::" << std::endl;
    for(unsigned int x=0; x<numLines; x++)
    {
        std::cout << x << " ";
        for(unsigned int y=0; y<numColumns; y++)
        {
            const Plant* p = board->getPlant(x,y);
            if(p != 0)
                std::cout << p->toChar() << " ";
            else 
                std::cout << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << "  a b c d e f g h i" << std::endl;

    std::cout << ":::ZOMBIE MAP:::" << std::endl;
    for(unsigned int x=0; x<numLines; x++)
    {
        std::cout << x << " " << board->numZombies(x) << std::endl;
    }

    std::cout << ":::PEA MAP:::" << std::endl;
    for(unsigned int x=0; x<numLines; x++)
    {
        std::cout << x << " " << board->numPeas(x) << std::endl;
    }
}
