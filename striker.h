#ifndef STRIKER_H
#define STRIKER_H

#include "player.h"

class Striker : public Player
{
public:
    Striker(bool host, QColor color);

    virtual void updateState(const Pitch* pitch);
};

#endif // STRIKER_H
