#ifndef TEAM_H
#define TEAM_H
#include <vector>
#include "player.h"
#include "goalkeeper.h"
#include "defender.h"
#include "striker.h"

class Pitch;

class Team
{
public:
    Team(bool host,const Pitch* pitch);
    Team();
    ~Team();

    std::vector<Player*> players;
};

#endif // TEAM_H
