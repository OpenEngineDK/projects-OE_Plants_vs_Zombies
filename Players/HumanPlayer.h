#ifndef _OE_CHESS_HUMAN_PLAYER_H_
#define _OE_CHESS_HUMAN_PLAYER_H_

#include "../Player.h"

class HumanPlayer : public Player
{
    //---------
    //Functions
    public:
        void update();

    private:
        void print_help();
        void print_board();
    protected:    
    //---------
    //Variables
    public:
    private:
    protected:
};

#endif //_OE_CHESS_HUMAN_PLAYER_H_
