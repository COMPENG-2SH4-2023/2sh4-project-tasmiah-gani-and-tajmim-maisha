#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    boardSizeX = 30;      //default board size
    boardSizeY = 15;

}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
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


