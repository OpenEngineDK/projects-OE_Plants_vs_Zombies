#ifndef _OE_PLANTS_PLAYER_H_
#define _OE_PLANTS_PLAYER_H_

#include "Board.h"

class Player
{
    //---------
    //Functions
    public:
        virtual void update() = 0;
        void seedBoard(Board *b)
        {
            board = b;
        }
    private:
    protected:    
    //---------
    //Variables
    public:
    private:
    protected:
        Board *board;
};

#endif //_OE_PLANTS_PLAYER_H_
