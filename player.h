#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <QColor>
#include <QPointF>
#include "moveableitem.h"

class Player : public MoveableItem
{
public:
    std::string name;
    static const int maxSpeed = 3;
    static const int maxSkill = 100;
    static const int minSkill = 50;
    bool up_side;
    QColor kitColor;
    bool inPoss;
    //akcje
    bool kicking;
    bool passing;
    //umiejetnosci
    float stamina;
    float strength;
    float skill; //techniczne umiejetnosci
    float overall;

    Player *oppGoalkeeper;

    Player(bool host, QColor color);
    virtual ~Player();
    float findBall(const Pitch *pitch);   //return speedRatio
    float findBallDist(const Pitch *pitch);   //return distance
    QPointF findBallPt(const Pitch *pitch);   //return PointDiff
    QPointF findGoal(bool up, const Pitch *pitch);
    QPointF findMyGoal(bool up, const Pitch *pitch);
    Player* nearest(const Player *ja, const Pitch *pitch, bool myteam);
    void changePlayerPos(float x, float y);
    virtual void updateState(const Pitch* pitch);
    void shoot();
    void pass();
};

#endif // PLAYER_H
