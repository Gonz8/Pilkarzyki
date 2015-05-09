#include "physicsengine.h"



///
/// \brief PhysicsEngine::PhysicsEngine this is class constructor
///
PhysicsEngine::PhysicsEngine()
{
}


///
/// \brief PhysicsEngine::updatePitch this
/// \param pitch
///
void PhysicsEngine::updatePitch(Pitch& pitch)
{
    for(auto& player: pitch.teamA->players){

        player->setX(player->getX() + player->getXVel());
        player->setY(player->getY() + player->getYVel());
        //player->y += player->yVel;
        if(player->getX() < 0)
            player->setX(0);
        if(player->getX() > pitch.sizeX)
            player->setX(pitch.sizeX);

        if(player->getY() < 0)
            player->setY(0);
        if(player->getY() > pitch.sizeY)
            player->setY(pitch.sizeY);

    }
    for(auto& player: pitch.teamB->players){
        player->setX(player->getX() + player->getXVel());
        player->setY(player->getY() + player->getYVel());
        //player->y += player->yVel;
        if(player->getX() < 0)
            player->setX(0);
        if(player->getX() > pitch.sizeX)
            player->setX(pitch.sizeX);

        if(player->getY() < 0)
            player->setY(0);
        if(player->getY() > pitch.sizeY)
            player->setY(pitch.sizeY);
    }

    pitch.ball->setX(pitch.ball->getX() + pitch.ball->getXVel());
    pitch.ball->setY(pitch.ball->getY() + pitch.ball->getYVel());
    //pitch.ball->y += pitch.ball->yVel;
    if(pitch.ball->getX() < 0)
        pitch.ball->setX(0);
    if(pitch.ball->getX() > pitch.sizeX)
        pitch.ball->setX(pitch.sizeX);

    if(pitch.ball->getY() < 0)
        pitch.ball->setY(0);
    if(pitch.ball->getY() > pitch.sizeY)
        pitch.ball->setY(pitch.sizeY);

//    if(pitch.ball->y == pitch.sizeY) {
//        pitch.teamA->score = 1;
//    }else if (pitch.ball->y == 0) {
//        pitch.teamB->score = 1;
//    }

    // Pilka ze nie moze wyjsc za boisko domyslnie
    pitch.update();
}
