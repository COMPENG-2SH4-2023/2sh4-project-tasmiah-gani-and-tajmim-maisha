#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);   // constructor
        ~Player();                      // deconstructor

        objPosArrayList* getPlayerPos();


        void updatePlayerDir();
        void movePlayer();
        //need more actions here
        // - after inserting the head but before removing the tail
        // - check if new head position collides with food
        // - If yes, increment the score in GM, and do not remove tail
        // otherwise, remove tail and move on.

        bool selfCollision();

    private:


        objPosArrayList *playerPosList;

        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif