#include "team.h"
#include <pitch.h>
Team::Team(bool host, const Pitch *pitch)
{
    int width = pitch->sizeX;
    int height = pitch->sizeY;
    up_side = host;
    score = 0;
    if(host) {
        name = "Czerwoni";
        color = Qt::red;
        Player *newPlayer = new Goalkeeper(host,color);
        players.push_back(newPlayer);
        for(int i=0;i<2;i++) {
            Player *newPlayer = new Defender(host,color);
            players.push_back(newPlayer);
        }
        for(int i=0;i<2;i++) {
            Player *newPlayer = new Striker(host,color);
            players.push_back(newPlayer);
        }

        players[0]->setX(width/2);
        players[0]->setY(height/40);
        players[1]->setX(width/3);
        players[1]->setY(height/5);
        players[2]->setX(2*width/3);
        players[2]->setY(height/5);
        players[3]->setX(width/2);
        players[3]->setY(height/2);
        players[4]->setX(9*width/16);
        players[4]->setY(15*height/32);
    } else {
        name = "Niebiescy";
        color = Qt::blue;
        Player *newPlayer = new Goalkeeper(host,color);
        players.push_back(newPlayer);
        for(int i=0;i<2;i++) {
            Player *newPlayer = new Defender(host,color);
            players.push_back(newPlayer);
        }
        for(int i=0;i<2;i++) {
            Player *newPlayer = new Striker(host,color);
            players.push_back(newPlayer);
        }

        players[0]->setX(width/2);
        players[0]->setY(39*height/40);
        players[1]->setX(width/3);
        players[1]->setY(4*height/5);
        players[2]->setX(2*width/3);
        players[2]->setY(4*height/5);
        players[3]->setX(width/3);
        players[3]->setY(9*height/16);
        players[4]->setX(2*width/3);
        players[4]->setY(9*height/16);
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

