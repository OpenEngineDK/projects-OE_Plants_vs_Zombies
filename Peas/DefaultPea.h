#ifndef _OE_PLANTS_PEA_DEFAULT_PEA_H_
#define _OE_PLANTS_PEA_DEFAULT_PEA_H_

class DefaultPea : public Pea
{
    //---------
    //Functions
    public:
        DefaultPea(unsigned int x, unsigned int y, float xspeed, float yspeed = 0, unsigned int hp = 1)
        : Pea(x, y, xspeed, yspeed, hp, 5000)
        {
        }
        char toChar() const
        {
            return 'D';
        }
        void update()
        {
            Pea::update();
        }

        unsigned int dealDmg()
        {
            if(isDamageOffCooldown())
            {
                takeDmg(1);
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

#endif //_OE_PLANTS_PEA_DEFAULT_PEA_H_



