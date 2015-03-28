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
    static const int maxSpeed = 5;

    float radius;


    virtual void updateState(const Pitch* pitch) = 0;
};

#endif // MOVEABLEITEM_H
