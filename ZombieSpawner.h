#ifndef _OE_PLANTS_ZOMBIE_SPAWNER_H_
#define _OE_PLANTS_ZOMBIE_SPAWNER_H_

#include "Board.h"
#include "Listener.h"
#include "Zombies/DefaultZombie.h"

class ZombieSpawner : public Listener
{
    //---------
    //Functions
    public:
        ZombieSpawner(Board *b)
        : board(b), counter(0) {}
        void update()
        {
            counter++;
            if(counter==3000)
            {
                counter=0;
                int line = rand() % board->numLines();
                board->addZombie(new DefaultZombie(board->numColumns(),
                                                   rand() % board->numLines(),
                                                   -0.005f,
                                                   5)); 
            }
        }
    private:
    protected:
    //---------
    //Variables
    public:
    private:
        Board *board;
        unsigned int counter;
    protected:
};

#endif //_OE_PLANTS_ZOMBIE_SPAWNER_H_

