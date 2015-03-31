#include "team.h"
#include <pitch.h>
Team::Team(bool host, const Pitch *pitch)
{
    int width = pitch->sizeX;
    int height = pitch->sizeY;
    up_side = host;
    if(host) {
        name = "Czerwoni";
        color = Qt::red;
        Player *newPlayer = new Goalkeeper();
        players.push_back(newPlayer);
        for(int i=0;i<2;i++) {
            Player *newPlayer = new Defender();
            players.push_back(newPlayer);
        }
        for(int i=0;i<2;i++) {
            Player *newPlayer = new Striker();
            players.push_back(newPlayer);
        }

        players[0]->x = width/2;
        players[0]->y = height/40;
        players[1]->x = width/3;
        players[1]->y = height/5;
        players[2]->x = 2*width/3;
        players[2]->y = height/5;
        players[3]->x = width/2;
        players[3]->y = height/2;
        players[4]->x = 9*width/16;
        players[4]->y = 15*height/32;
    } else {
        name = "Niebiescy";
        color = Qt::blue;
        Player *newPlayer = new Goalkeeper();
        players.push_back(newPlayer);
        for(int i=0;i<2;i++) {
            Player *newPlayer = new Defender();
            players.push_back(newPlayer);
        }
        for(int i=0;i<2;i++) {
            Player *newPlayer = new Striker();
            players.push_back(newPlayer);
        }

        players[0]->x = width/2;
        players[0]->y = 39*height/40;
        players[1]->x = width/3;
        players[1]->y = 4*height/5;
        players[2]->x = 2*width/3;
        players[2]->y = 4*height/5;
        players[3]->x = width/3;
        players[3]->y = 9*height/16;
        players[4]->x = 2*width/3;
        players[4]->y = 9*height/16;
    }
    int high = Player::maxSkill; int low = Player::minSkill;
    coopSkill = qrand() % ((high + 1) - low) + low;

}

Team::Team()
{

}

Team::~Team()
{
    foreach (Player *player, players) {
      delete player;
    }
}
bool Team::getSide() const
{
    return up_side;
}

void Team::setSide(bool value)
{
    up_side = value;
}

