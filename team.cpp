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

        this->setPlayersPos(this->up_side,true,pitch);

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

        this->setPlayersPos(this->up_side,false,pitch);

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
    foreach (Player *player, players) {
      player->up_side = value;
    }
}

void Team::setPlayersPos(bool up_side, bool withBall, const Pitch *pitch)
{
    int width = pitch->sizeX;
    int height = pitch->sizeY;
    if(up_side){
        if(withBall){
            players[0]->changePlayerPos(width/2,height/40);
            players[1]->changePlayerPos(width/3,height/5);
            players[2]->changePlayerPos(2*width/3,height/5);
            players[3]->changePlayerPos(width/2,height/2);
            players[4]->changePlayerPos(9*width/16,15*height/32);
        }
        else {
            players[0]->changePlayerPos(width/2,height/40);
            players[1]->changePlayerPos(width/3,height/5);
            players[2]->changePlayerPos(2*width/3,height/5);
            players[3]->changePlayerPos(width/3,7*height/16);
            players[4]->changePlayerPos(2*width/3,7*height/16);
        }
    }
    else {
        if(withBall){
            players[0]->changePlayerPos(width/2,39*height/40);
            players[1]->changePlayerPos(width/3,4*height/5);
            players[2]->changePlayerPos(2*width/3,4*height/5);
            players[3]->changePlayerPos(width/2,height/2);
            players[4]->changePlayerPos(9*width/16,17*height/32);
        }
        else {
            players[0]->changePlayerPos(width/2,39*height/40);
            players[1]->changePlayerPos(width/3,4*height/5);
            players[2]->changePlayerPos(2*width/3,4*height/5);
            players[3]->changePlayerPos(width/3,9*height/16);
            players[4]->changePlayerPos(2*width/3,9*height/16);
        }
    }
}


