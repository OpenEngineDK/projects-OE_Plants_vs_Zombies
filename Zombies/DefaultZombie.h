#ifndef _OE_PLANTS_ZOMBIE_DEFAULT_ZOMBIE_H_
#define _OE_PLANTS_ZOMBIE_DEFAULT_ZOMBIE_H_

class DefaultZombie : public Zombie
{
    //---------
    //Functions
    public:
        DefaultZombie(float x, float y, float xspeed, unsigned int hp)
        : Zombie(x, y, xspeed, hp, 5000)
        {}
        
        char toChar() const
        {
            return 'Z';
        }

        unsigned int dealDmg()
        {
            if(isDamageOffCooldown())
            {
                DamageDealer::dealDmg();
                return 1;
            }
            return 0;
        }
    private:
    protected:
    //---------
    //Variables
    public:
    private:
    protected:
};

#endif //_OE_PLANTS_ZOMBIE_DEFAULT_ZOMBIE_H_


