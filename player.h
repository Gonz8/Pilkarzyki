#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "moveableitem.h"

class Player : public MoveableItem
{
public:
    std::string name;
    static const int maxSpeed = 5;
    static const int maxSkill = 100;
    static const int minSkill = 40;
    bool inPoss;
    float stamina;
    float strength;
    float skill; //techniczne umiejetnosci
    float overall;

    Player();
    virtual ~Player();

    virtual void updateState(const Pitch* pitch);
};

#endif // PLAYER_H
