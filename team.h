#ifndef TEAM_H
#define TEAM_H
#include <vector>
#include <string>
#include <QColor>
#include "player.h"
#include "goalkeeper.h"
#include "defender.h"
#include "striker.h"

class Pitch;

class Team
{
public:
    std::string name;
    std::vector<Player*> players;
    QColor color;
    float coopSkill;
    int score;  //bramki zdobyte
    Team(bool host,const Pitch* pitch);
    Team();
    ~Team();
    bool getSide() const;
    void setSide(bool value);
    void setPlayersPos(bool up_side,bool withBall,const Pitch* pitch);

private:
    bool up_side; // zaczyna górna połowa (gospodarz)

};

#endif // TEAM_H
