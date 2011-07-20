#ifndef _OE_PLANTS_MOVEABLE_H_
#define _OE_PLANTS_MOVEABLE_H_

class Moveable
{
    //---------
    //Functions
    public:
        Moveable(float x, float y, float xspeed = 0, float yspeed = 0)
        : x(x), y(y), xspeed(xspeed), yspeed(yspeed) {}
        virtual ~Moveable() {}
        float getX() const { return x; }
        float getY() const { return y; }
        float getXSpeed() const  { return xspeed; }
        float getYSpeed() const  { return yspeed; }
    private:
    protected:
    //---------
    //Variables
    public:
    private:
    protected:
        float x, y;
        float xspeed, yspeed;
};

#endif //_OE_PLANTS_MOVEABLE_H_


