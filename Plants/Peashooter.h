#ifndef _OE_PLANTS_PLANT_PEASHOOTER_H_
#define _OE_PLANTS_PLANT_PEASHOOTER_H_

#include "../Plant.h"
#include "../Pea.h"
#include "../Peas/DefaultPea.h"

class PeaShooter : public Plant
{
    //---------
    //Functions
    public:
        PeaShooter()
        : Plant(0,0,5), cooldown(500), updates(cooldown)
        {
        }

        PeaShooter(unsigned int x, unsigned int y)
        : Plant(x,y,5), cooldown(500), updates(cooldown)
        {
        }
        
        char toChar() const
        {
            return 'P';
        }
        
        std::string toString() const
        {
            return "PeaShooter";
        }
        std::vector<Pea*> update()
        {
            std::vector<Pea*> vec;

            updates++;
            if(updates >= cooldown)
            {
                vec.push_back(new DefaultPea(x, y, 0.01f));
                updates = 0;
            }

            return vec;
        }
        Plant* clone(unsigned int x, unsigned int y)
        {
            return new PeaShooter(x,y);
        }
    private:
    protected:
    //---------
    //Variables
    public:
    private:
        unsigned int cooldown;
        unsigned int updates;
    protected:
};

#endif //_OE_PLANTS_PLANT_PEASHOOTER_H_

