#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib> //provides srand() and rand()
#include <time.h> //can be replaced by <ctime>
                  //provides time()


#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;

        objPos foodPos;
        
        int boardSizeX;
        int boardSizeY;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        
        bool getExitFlagStatus();
        bool getLoseFlagStatus();

        void setExitTrue();
        void setLoseFlag();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getScore();
        void incrementScore();

        int getBoardSizeX();
        int getBoardSizeY();

        void generateFood(objPos blockOff); //you need to upgrade this somehow...
        void getFoodPos(objPos &returnPos);
      

};

#endif