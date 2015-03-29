#ifndef PLAYER_H
#define PLAYER_H


#include "moveableitem.h"

class Player : public MoveableItem
{
public:
    Player();
    virtual ~Player();
    static const int maxSpeed = 5;
    virtual void updateState(const Pitch* pitch);
};

#endif // PLAYER_H
