#include "GameMechs.h"
#include "MacUILib.h"

//Think about where to seed the RNG

GameMechs::GameMechs()
{
    //initializing imp variables of function 
    input = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = 30;      //default board size
    boardSizeY = 15;
    score = 0;
    foodPos.setObjPos(-1, -1, 'o'); //initialize foodPos outside of board, to not be displayed


}

GameMechs::GameMechs(int boardX, int boardY)
{
    
    //initializing imp variables of specialized constructor
    input = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = boardX;     //default board size
    boardSizeY = boardY;
    score = 0;

    foodPos.setObjPos(-1, -1, 'o'); //initialize foodPos outside of board, to not be displayed


}


GameMechs::~GameMechs()
{
    //commentt 
}

//Getters

bool GameMechs::getExitFlagStatus() 
{
    return exitFlag;

}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

char GameMechs::getInput()
{
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::incrementScore()
{
    score++;
}

void GameMechs::clearInput()
{
    input = '\0';
}

/*/DEPENDS ON IF WE MAKE PROGRAM TO INCREMENT MORE THAN ONE AT A TIME
void GameMechs::incrementScore(int amount)
{
    score += amount;
}
*/

//FOOD GENERATION PROCESSINGS:

void GameMechs::generateFood(objPosArrayList *blockOff)
{

    // //generate food on random x n y coordinates
    // //make sure they are not game border or blockoff pos
    // int randX = 0;
    // int randY = 0;

    
    // srand(time(NULL)); //seed the time 

    // bool flag = false;

    // while(!flag){
    //     randX = rand() % (getBoardSizeX()- 2)+ 1; // makes sure not on x border 
    //     randY = rand() % (getBoardSizeY()- 2)+ 1; //make sure not y border 
        
    //     if (randX == blockOff.x && randY == blockOff.y){
    //          flag = false;
    //     }
    //     else{
    //         flag = true;
    //     }
    //     if(flag)
    //     {
    //         foodPos.setObjPos(randX, randY, 'o');
    //     }

    //     //Figure out if we need to put the blockOff array thing 
    // }

    srand(time(NULL));
    /* Randomly generate x and y coord (make sure not barder or blockOff pos)
    generating number betwwen 0 - (cols-2 = 18) */
    foodPos.x = (rand() % (boardSizeX - 2)) + 1;
    foodPos.y = (rand() % (boardSizeY - 2)) + 1; 
    
    /* Loop through each item in blockOff array.
    Exit when the generated food doesn't overlap with the player body.*/
    objPos tempPos;
    for(int i = 0; i < blockOff->getSize(); i++){
        blockOff->getElement(tempPos, i);
        while(foodPos.isPosEqual(&tempPos)){
            // Regenerate new coordinates for the food object
            foodPos.x = (rand() % (boardSizeX - 2)) + 1;
            foodPos.y = (rand() % (boardSizeX - 2)) + 1;
        }
    }



}

//Getter to get current food position
void GameMechs::getFoodPos(objPos &returnFood)
{
    returnFood.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}



