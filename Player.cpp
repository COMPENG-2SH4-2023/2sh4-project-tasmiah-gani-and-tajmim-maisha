#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '*');
}


Player::~Player()
{
    //no heap member yet-wait for iteration 3
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic

    //where to get input?? How do I check for input
    //hint 1. not by calling MacUILib_getchar()
    //     2. coordinate eith teammeneber (GmaeMech class)
    //     3. there will be a method in GameM

    char input = mainGameMechsRef->getInput();

    switch(input)
    {                      
        // case ' ':  // exit
        //     exitFlag = 1;
        //     break;
        
        //Movement inputs
        case 'w':
        case 'W':
            if(myDir != UP && myDir != DOWN) {
                myDir = UP;
            }
            break;

        case 's':
        case 'S':
            if(myDir != UP && myDir != DOWN) {
                myDir = DOWN;
            }
            break;


        case 'a':
        case 'A':
            if(myDir != LEFT && myDir != RIGHT) {
                myDir = LEFT;
            }
            break;

        case 'd':
        case 'D':
            if(myDir != LEFT && myDir != RIGHT) {
                myDir = RIGHT;
            }
            break;
        
        default:
            break;
    }

}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    

    playerPos.setObjPos(playerPos.x, playerPos.y, '*');
    switch(myDir) {

        case STOP:
            break;

        case UP:
            playerPos.setObjPos(playerPos.x, playerPos.y-1, '*');
            // playerPos.y--;               //move up array
            // moveCount++;
            if (playerPos.y < 1) {       // when playerPos is out of bound at the top of the board,
                playerPos.y = 8;         // character is moved to the bottom on the board (wraparound)
            }
            break;

        case DOWN:
            playerPos.setObjPos(playerPos.x, playerPos.y+1, '*');
            // playerPos.y++;               //move down array
            // moveCount++;
            if (playerPos.y > 8) {
                playerPos.y = 1;
            }
            break;

        case LEFT:
            playerPos.setObjPos(playerPos.x-1, playerPos.y, '*');
            // playerPos.x--;               //move left of array
            // moveCount++;
            if (playerPos.x < 1) {
                playerPos.x = 18;
            }
            break;

        case RIGHT:
            playerPos.setObjPos(playerPos.x+1, playerPos.y, '*');
            // playerPos.x++;               //move right of array
            // moveCount++;
            if (playerPos.x > 18) {
                playerPos.x = 1;
            }
            break;
        
        default:
            break;
    }

}

