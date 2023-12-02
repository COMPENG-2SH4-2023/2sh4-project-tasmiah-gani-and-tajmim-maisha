#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000

// Global pointer to a gameMechanics class
GameMechs* myGM;

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

objPos myPos;
Player* myPlayer;
char game_board[15][30];

int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myPlayer = new Player(myGM);


    // Create a gameMechanics object on the heap and initialize its fields    
    myGM = new GameMechs(30, 15); //makes board size 30x15
    
}

void GetInput(void)
{

    //access correct info using getter method
    char input = myGM->getInput();
    
    //collects input char 
    myGM->setInput(input);


    // Debug: Press 'i' to increment the score
        if (input == 'i')
        {
            myGM->incrementScore();
            cout << "Debug: Score incremented. New score: " << myGM->getScore() << endl;
        }

        // Debug: Press 'l' to set the lose fla
        else if (input == 'l')
        {
            myGM->setLoseFlag();
            cout << "Debug: Lose flag set. Game will end with lose message." << endl;
        }

    
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();

    //clear input field in GM 
    myGM->clearInput();
}

void DrawScreen(void)
{

    MacUILib_clearScreen();

    objPos tempPos;
    myPlayer.getPlayerPos(tempPos);

    MacUILib_printf("BoardSize: %dx%d, Player Pos: <%d, %d> + %c\n", 
                    myGM->getBoardSizeX(),
                    myGM->getBoardSizeY(),
                    tempPos.x, tempPos.y, tempPos.symbol);


}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{

//delete GM object from heap
    delete myGM;
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
}
