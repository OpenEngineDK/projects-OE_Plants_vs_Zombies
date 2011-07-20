#ifndef _OE_CHESS_GAME_H_
#define _OE_CHESS_GAME_H_

#include "Player.h"
#include "Board.h"

class Game
{
    //---------
    //Functions
    public:
        Game();

        void update();

        void seedPlayer(Player *p);
        void unseedPlayer();
        void seedBoard(Board *b);
        void unseedBoard();
        void newGame();
    private:
    protected:    
    //---------
    //Variables
    public:
    private:
        Player *player;
        Board *board;
    protected:
};

#endif //_OE_CHESS_GAME_H_

