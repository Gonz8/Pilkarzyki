#ifndef MOVEABLEITEM_H
#define MOVEABLEITEM_H

class Pitch;
class MoveableItem
{
public:
    MoveableItem();

    //pozniej protected
    float x;
    float y;
    float xVel;
    float yVel;

    float radius;

    bool chance(float chance,int universe = 100);
    virtual void updateState(const Pitch* pitch) = 0;
};

#endif // MOVEABLEITEM_H
