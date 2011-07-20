#include "Board.h"

#include <cstdlib>

//Needed for the Parsing functions
#include <Utils/Convert.h>

Board::Board()
: x(8), y(6)
{
    newGame();
}

Board::Board(unsigned int x, unsigned int y)
: x(x), y(y)
{
    newGame();
}


bool Board::hitting(float x1, float y1, float x2, float y2, float min_distance)
{
    float xdiff = x2-x1;
    float ydiff = y2-y1;
    float distance = (xdiff*xdiff)+(ydiff*ydiff);
    if( distance < min_distance*min_distance)
    {
        return true;
    }
    return false;
}

void Board::update()
{
    // Update plants
    for(unsigned int i=0; i<numPlantsTotal(); i++)
    {
        std::vector<Pea*> shots_fired = board.at(i)->update();
        for(unsigned int z=0; z<shots_fired.size(); z++)
        {
            peas.push_back(shots_fired.at(z));
        }
    }
    // Update peas
    for(unsigned int i=0; i<numPeasTotal(); i++)
    {
        peas.at(i)->update();
    }
    // Update zombies
    for(unsigned int i=0; i<numZombiesTotal(); i++)
    {
        zombies.at(i)->update();
    }
    // Handle collisions Zombies
    for(unsigned int i=0; i<numZombiesTotal(); i++)
    {
        Zombie* z = zombies.at(i);
        float zombieX = z->getX();
        float zombieY = z->getY();

        z->isAttacking(false);

        for(unsigned int j=0; j<numPlantsTotal(); j++)
        {
            Plant* p = board.at(j);
            unsigned int plantX = p->getX();
            unsigned int plantY = p->getX();
            // Hitting
            if(hitting(zombieX, zombieY, plantX, plantY, 0.05f))
            {
                z->isAttacking(true);
                p->takeDmg(z->dealDmg());
                if(p->isDead())
                {
                    // if the plant is dead, remove it.
                    delete p;
                    board.erase(board.begin()+j);
                    j--;
                }
            }
        }
    }
    // Handle collisions Peas
    for(unsigned int i=0; i<numPeasTotal(); i++)
    {
        Pea* p = peas.at(i);
        float peaX = p->getX();
        float peaY = p->getY();

        if(peaX > numColumns()+1)
        {
            delete p;
            peas.erase(peas.begin()+i);
            i--;
        }

        // For each pea, check if its hitting a zombie.
        for(unsigned int j=0; j<numZombiesTotal(); j++)
        {
            Zombie* z = zombies.at(j);
            float zombieX = z->getX();
            float zombieY = z->getY();

            // Hitting
            if(hitting(peaX, peaY, zombieX, zombieY, 0.5f))
            {
                // Most peas take dmg from dealing, simply so you can make them
                // hit one or more targets.
                z->takeDmg(p->dealDmg());
                if(z->isDead())
                {
                    // if the zombie is dead, remove it and decrement the
                    // counter to continue nicely.
                    delete z;
                    zombies.erase(zombies.begin()+j);
                    j--;
                }
                if(p->isDead())
                {
                    // if the pea is dead, remove it and decrement the
                    // counter to continue nicely.
                    delete p;
                    peas.erase(peas.begin()+i);
                    i--;
                } 
            }
        }
    }
    //Update listeners
    for(unsigned int x=0; x<listeners.size(); x++)
    {
        listeners.at(x)->update();
    }
}

void Board::newGame()
{
    board.clear();
    zombies.clear();
    peas.clear();
}

unsigned int Board::numLines() const
{
    return y;
}


unsigned int Board::numColumns() const
{
    return x;
}

unsigned int Board::numPlantsTotal() const
{
    return board.size();
}

unsigned int Board::numPlants(unsigned int line) const
{
    unsigned int num_plants = 0;
    for(unsigned int x=0; x<numPlantsTotal(); x++)
    {
        if(board.at(x)->getY() == line)
        {
            num_plants++;
        }
    }
    return num_plants;
}

const std::vector<Plant*> Board::getPlantBoard() const
{
    return board;
}

const std::vector<Zombie*> Board::getZombieBoard() const
{
    return zombies;
}

const std::vector<Pea*> Board::getPeaBoard() const
{
    return peas;
}

const std::vector<Plant*> Board::getPlantLine(unsigned int line) const
{
    std::vector<Plant*> vec;
    for(unsigned int x=0; x<numPlantsTotal(); x++)
    {
        if(board.at(x)->getY() == line)
        {
            vec.push_back(board.at(x));
        }
    }
    return vec;
}

const Plant* Board::getPlant(unsigned int line, unsigned int id) const
{
    for(unsigned int x=0; x<numPlantsTotal(); x++)
    {
        Plant *p = board.at(x);
        if(p->getX() == id and p->getY() == line)
        {
            return p;
        }
    }
    return 0;
}

unsigned int Board::numZombiesTotal() const
{
    return zombies.size();
}

unsigned int Board::numZombies(unsigned int line) const
{
    unsigned int num_zombies = 0;
    for(unsigned int x=0; x<numZombiesTotal(); x++)
    {
        if(zombies.at(x)->getY() == line)
        {
            num_zombies++;
        }
    }
    return num_zombies;
}

unsigned int Board::numPeasTotal() const
{
    return peas.size();
}

unsigned int Board::numPeas(unsigned int line) const
{
    unsigned int num_peas = 0;
    for(unsigned int x=0; x<numPeasTotal(); x++)
    {
        if(peas.at(x)->getY() == line)
        {
            num_peas++;
        }
    }
    return num_peas;
}

bool Board::isGameOver()
{
    for(unsigned int x=0; x<numZombiesTotal(); x++)
    {
        bool is_killing = zombies.at(x)->isKilling();
        if(is_killing) // if a zombie is killing us, then the game is over
        {
            return true;
        }
    }
    return false;
}

int Board::regex_check_move(std::string s)
{
    if  ((s[0] >= 'a' and s[0] <= 'i') and
         (s[1] >= '0' and s[1] <= '5') and
         (s[2] == '-' and s[3] == '>'))
    {
        for(unsigned int x=0; x<valid_plants.size(); x++)
        {
            if(!(s.substr(4)).compare(valid_plants.at(x)->toString()))
                return x;
        }
    }
    return -1;
}

bool Board::parse_move(std::string s)
{
    if(regex_check_move(s) != -1)
    {
        return true;
    }
    return false;
}

bool Board::setPlant(Plant *p)
{
    for(unsigned int x=0; x<numPlantsTotal(); x++)
    {
        Plant *old_p = board.at(x);
        if(old_p->getX() == p->getX() and old_p->getY() == p->getY())
        {
            return false;
        }
    }
    board.push_back(p);
    return true;
}

bool Board::make_move(std::string s)
{
    int id = s[0] - 97;     //ASCII VALUE: MAP 'a' to 0
    int line = s[1] - 48;   //ASCII VALUE: MAP '0' to 0

    if(getPlant(line,id) == 0)
    {
        int plant_id = regex_check_move(s);

        // Set the square at 'line' and 'id' and seed these to the clone too
        // Clone is supposed to be id, line as its (x,y)
        if(setPlant(valid_plants.at(plant_id)->clone(id, line)))
        {
            return true;
        }
    }

    return false;
}

void Board::addValidPlant(Plant *p)
{
    valid_plants.push_back(p);
}

void Board::addZombie(Zombie *z)
{
    zombies.push_back(z);
}

void Board::addListener(Listener *l)
{
    listeners.push_back(l);
}
