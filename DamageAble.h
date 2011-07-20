#ifndef _OE_PLANTS_DAMAGEABLE_H_
#define _OE_PLANTS_DAMAGEABLE_H_

#include <algorithm>

class DamageAble
{
    //---------
    //Functions
    public:
        DamageAble(unsigned int hp)
        : health_points_max(hp), health_points(hp)
        {}
        virtual ~DamageAble() {}

        unsigned int getHealthPointsMax() const { return health_points_max; }
        unsigned int getHealthPointsLeft() const { return health_points; }
        bool isDead() const { return health_points == 0; }
        void takeDmg(unsigned int dmg_taken)  
        { 
            health_points = std::max((unsigned int)0, health_points-dmg_taken);
        }
    private:
    protected:
    //---------
    //Variables
    public:
    private:
    protected:
        unsigned int health_points_max;
        unsigned int health_points;
};

#endif //_OE_PLANTS_DAMAGEABLE_H_


