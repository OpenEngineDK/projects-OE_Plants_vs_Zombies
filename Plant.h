#ifndef _OE_PLANTS_PLANT_H_
#define _OE_PLANTS_PLANT_H_

#include <string>
#include <vector>

#include "Pea.h"

#include "Damageable.h"

class Plant : public DamageAble
{
    //---------
    //Functions
    public:
        Plant(unsigned int x, unsigned int y, unsigned int hp)
        : DamageAble(hp), x(x), y(y)
        {}
        virtual ~Plant() {}
        virtual char toChar() const = 0;
        virtual std::string toString() const = 0;
        virtual std::vector<Pea*> update() = 0;
        virtual Plant* clone(unsigned int x, unsigned int y) = 0;
        unsigned int getX()
        {
            return x;
        }
        unsigned int getY()
        {
            return y;
        }
    private:
    protected:
    //---------
    //Variables
    public:
    private:
    protected:
        unsigned int x, y;
};

#endif //_OE_PLANTS_PLANT_H_
