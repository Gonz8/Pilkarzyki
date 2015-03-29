#ifndef MOVEABLEITEM_H
#define MOVEABLEITEM_H

class Pitch;
class MoveableItem
{
public:
    MoveableItem();


    float x;
    float y;
    float xVelF;
    float yVelF;

    float radius;


    virtual void updateState(const Pitch* pitch) = 0;
};

#endif // MOVEABLEITEM_H
