#ifndef GOALKEEPER_H
#define GOALKEEPER_H

#include "player.h"

class Goalkeeper : public Player
{
public:
    Goalkeeper(bool host, QColor color);

    virtual void updateState(const Pitch* pitch);
};

#endif // GOALKEEPER_H
