#include "team.h"
#include <pitch.h>
Team::Team(bool host, const Pitch *pitch)
{
    int width = pitch->sizeX;
    int height = pitch->sizeY;
    if(host) {
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
        players[3]->x = width/3;
        players[3]->y = 7*height/16;
        players[4]->x = 2*width/3;
        players[4]->y = 7*height/16;
    } else {
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
