#ifndef TEAM_H
#define TEAM_H
#include <vector>
#include "player.h"

class Pitch;

class Team
{
public:
    Team(bool host,const Pitch* pitch);
    Team();


    std::vector<Player> players;
};

#endif // TEAM_H
