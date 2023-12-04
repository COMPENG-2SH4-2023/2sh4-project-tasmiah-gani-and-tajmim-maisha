#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    //
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,
                    mainGameMechsRef->getBoardSizeY()/2, '*');

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

}


Player::~Player()
{
    //no heap member yet-wait for iteration 3
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    //
    //


    char input = mainGameMechsRef->getInput();

    switch(input)
    {                      
       
        case ' ':  // exit
             mainGameMechsRef->setExitTrue(); //set exit flag to true when space inputted 
            break;

        
        //Movement inputs:
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
    objPos currentHead;        // holding the pos info of the current head
    playerPosList->getHeadElement(currentHead);             //-----------------------------------------

    switch(myDir) {

        case UP:
            currentHead.y--;               //move up array
            if (currentHead.y < 1) {       // when playerPos is out of bound at the top of the board,
                                         // character is moved to the bottom on the board (wraparound)
                currentHead.y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;

        case DOWN:
            currentHead.y++;               //move down array
            if (currentHead.y >= mainGameMechsRef->getBoardSizeY()) {
                currentHead.y = 1;
            }
            break;

        case LEFT:
            currentHead.x--;               //move left of array
            if (currentHead.x < 1) {
                currentHead.x = mainGameMechsRef->getBoardSizeX() - 2;
            }
            break;

        case RIGHT:
            currentHead.x++;               //move right of array
            if (currentHead.x >= mainGameMechsRef->getBoardSizeX()) {
                currentHead.x = 1;
            }
            break;

        case STOP:
        default:
            break;
    }
    // new current head should be inserted to the head of the list,
    playerPosList->insertHead(currentHead);
    
    // then, remove tail
    playerPosList->removeTail();

}


bool Player::selfCollision() {
    objPos head;
    playerPosList->getHeadElement(head);

    objPos tempBody;

    // Checks for collision by iterating through the body of the snake
    for(int i = 2; i < playerPosList->getSize(); i++){
        playerPosList->getElement(tempBody, i);

        // If yes, snake collides with body
        if(tempBody.isPosEqual(&head)) {
            return true;
        }
    }
    // If no, snake doesn't collide with body
    return false;

}