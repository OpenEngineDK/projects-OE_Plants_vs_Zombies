#ifndef _OE_PLANTS_DAMAGEDEALER_H_
#define _OE_PLANTS_DAMAGEDEALER_H_

class DamageDealer
{
    //---------
    //Functions
    public:
        DamageDealer(unsigned int cooldown)
        : cooldown(cooldown), dmg_cooldown_counter(cooldown), dmg_cooldown(false)
        {}
        virtual ~DamageDealer() {}

        void tick_cooldown()
        {
            if(dmg_cooldown)
            {
                dmg_cooldown_counter++;
            }
            if(dmg_cooldown_counter == 5000)
            {
                dmg_cooldown_counter = 0;
                dmg_cooldown=false;
            }
        }

        bool isDamageOffCooldown()
        {
            return !dmg_cooldown;
        }

        virtual unsigned int dealDmg()
        {
            dmg_cooldown=true;
            return 0;
        }
    private:
    protected:
    //---------
    //Variables
    public:
    private:
    protected:
        const unsigned int cooldown;
        unsigned int dmg_cooldown_counter;
        bool dmg_cooldown;
};

#endif //_OE_PLANTS_DAMAGEABLE_H_



