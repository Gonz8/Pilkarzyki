#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <QColor>
#include "moveableitem.h"

class Player : public MoveableItem
{
public:
    std::string name;
    static const int maxSpeed = 3;
    static const int maxSkill = 100;
    static const int minSkill = 40;
    bool up_side;
    QColor kitColor;
    bool inPoss;
    float stamina;
    float strength;
    float skill; //techniczne umiejetnosci
    float overall;

    Player(bool host, QColor color);
    virtual ~Player();
    float findBall(const Pitch *pitch);   //return speedRatio
    virtual void updateState(const Pitch* pitch);
};

#endif // PLAYER_H
