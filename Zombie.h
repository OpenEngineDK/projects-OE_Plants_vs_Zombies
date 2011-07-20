#ifndef _OE_PLANTS_ZOMBIE_H_
#define _OE_PLANTS_ZOMBIE_H_

#include "Moveable.h"
#include "Damageable.h"
#include "DamageDealer.h"

class Zombie : public Moveable, public DamageAble, public DamageDealer
{
    //---------
    //Functions
    public:
        Zombie(float x, float y, float xspeed, unsigned int hp, unsigned int dmg_cooldown)
        : Moveable(x, y, xspeed, 0), DamageAble(hp), DamageDealer(dmg_cooldown), is_attacking(false)
        {}
        virtual ~Zombie() {}
        virtual char toChar() const = 0;
        virtual void update()
        {
            DamageDealer::tick_cooldown();
            if(isAttacking())
                return;

            x = x + xspeed;
            y = y + yspeed;
        }
        virtual bool isKilling() const
        {
            if(y < 0)
                return true;
            return false;
        }
        void isAttacking(bool attacking)
        {
            is_attacking = attacking;
        }
        bool isAttacking()
        {
            return is_attacking;
        }
    private:
    protected:
    //---------
    //Variables
    public:
    private:
    protected:
        bool is_attacking;
};

#endif //_OE_PLANTS_ZOMBIE_H_

