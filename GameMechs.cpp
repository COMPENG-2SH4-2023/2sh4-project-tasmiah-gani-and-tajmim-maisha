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

void GameMechs::generateFood(objPos *blockOff)
{

    //generate food on random x n y coordinates
    //make sure they are not game border or blockoff pos
    int randX = 0;
    int randY = 0;
    srand(time(NULL)); //seed the time 

    bool flag = false;
    while(!flag){
        randX = rand() % (getBoardSizeX()- 2)+ 1; // makes sure not on x border 
        randY = rand() % (getBoardSizeY()- 2)+ 1; //make sure not y border 
        if (randX == blockOff->x && randY == blockOff->y){
             flag = false;
        }
        else{
            flag = true;
        }
        if(flag)
        {
            foodPos.setObjPos(randX, randY, 'o');
        }

        //Figure out if we need to put the blockOff array thing 
    }
}

//Getter to get current food position
void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}



