#include "GameMechs.h"
#include "MacUILib.h"

//Think about where to seed the RNG

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = 30;      //default board size
    boardSizeY = 15;

    foodPos.setObjPos(-1, -1, 'o'); //initialize foodPos outside of board to not be displayed

    //generateFood(objPos(-1, -1, ' ')); // Generate initial food, leaving room for random gen 

}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = boardX;     //default board size
    boardSizeY = boardY;

}

// do you need a destructor?



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

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

/*/DEPENDS ON IF WE MAKE PROGRAM TO INCREMENT MORE THAN ONE AT A TIME
void GameMechs::incrementScore(int amount)
{
    score += amount;
}
*/

void GameMechs::clearInput()
{
    input = '\0';
}



void GameMechs::generateFood(objPos blockOff)
{

    //generate random x n y coord, and make sure they are not border or blockoff pos

    //check x and y against 0 and boardSize X/Y

    //remember, in objPos class you have an isPosEqual() method. Use this instead of comparing element-by-element
    //for your convenience



    int randX = 0;
    int randY = 0;
    srand(time(NULL)); //seed the time 

    bool flag = false;
    while(!flag){
        randX = rand() % (getBoardSizeX()- 2)+ 1; // makes sure not on x border 
        randY = rand() % (getBoardSizeY()- 2)+ 1; //make sure not y border 
        if (randX == blockOff.x && randY == blockOff.y){
             flag = false;
        }
        else{
            flag = true;
        }
        if(flag)
        {
            foodPos.setObjPos(randX, randY, 'o');
        }
    }
}

void GameMechs::getFoodPos(objPos &returnPos)
{
    foodPos.getObjPos(returnPos);
}



