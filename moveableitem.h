#ifndef MOVEABLEITEM_H
#define MOVEABLEITEM_H

#include <QPointF>

class Pitch;
class MoveableItem
{
public: 
    float radius;

    MoveableItem();
    bool chance(float chance,int universe = 100);
    virtual void updateState(const Pitch* pitch) = 0;
    float distance(float x1, float y1, float x2, float y2);
    float getX() const;
    float getY() const;
    float getXVel() const;
    float getYVel() const;
    void setX(float value);
    void setY(float value);
protected:
    float x;
    float y;
    float xVel;
    float yVel;
};

#endif // MOVEABLEITEM_H
