#ifndef DEFENDER_H
#define DEFENDER_H

#include "player.h"

class Defender : public Player
{
public:
    Defender(bool host, QColor color);

    virtual void updateState(const Pitch* pitch);
};

#endif // DEFENDER_H
