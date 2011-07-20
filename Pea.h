#ifndef _OE_PLANTS_PEA_H_
#define _OE_PLANTS_PEA_H_

#include "Moveable.h"
#include "Damageable.h"
#include "DamageDealer.h"

class Pea : public Moveable, public DamageAble, public DamageDealer
{
    //---------
    //Functions
    public:
        Pea(float x, float y, float xspeed, float yspeed, unsigned int hp, unsigned int dmg_cooldown)
        : Moveable(x, y, xspeed, yspeed), DamageAble(hp), DamageDealer(dmg_cooldown)
        {
        }
        virtual char toChar() const = 0;
        virtual void update()
        {
            DamageDealer::tick_cooldown();
            x = x + xspeed;
            y = y + yspeed;
        }

    private:
    protected:
    //---------
    //Variables
    public:
    private:
    protected:
};

#endif //_OE_PLANTS_PEA_H_


