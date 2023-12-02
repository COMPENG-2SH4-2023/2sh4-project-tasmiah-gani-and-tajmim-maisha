#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000

// Global pointer to specific classes
GameMechs* myGM;

objPos myPos;
Player* myPlayer;


bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

char gameBoard[15][30];

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

    // Create a gameMechanics object on the heap and initialize its fields    
    myGM = new GameMechs(30, 15); //makes board size 30x15
    
    myPlayer = new Player(myGM);


}

void GetInput(void)
{

    //access correct info using getter method
    char input = myGM-> getInput();
    
    //collects input char 
    myGM-> setInput(input);


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

    // objPos tempPos;
    myPlayer->getPlayerPos(myPos);

    // MacUILib_printf("BoardSize: %dx%d, Player Pos: <%d, %d> + %c\n", 
    //                 myGM->getBoardSizeX(),
    //                 myGM->getBoardSizeY(),
    //                 tempPos.x, tempPos.y, tempPos.symbol);

    MacUILib_printf("BoardSize: %dx%d, Player Pos: <%d, %d> + %c\n", 
                    myGM->getBoardSizeX(),
                    myGM->getBoardSizeY(),
                    myPos.x, myPos.y, myPos.symbol);


    //Print board and moving character on screen
    for(int row = 0; row < myGM->getBoardSizeY(); row++) {
        for(int col = 0; col < myGM->getBoardSizeX(); col++) {

            //print game board
            if(0 == row || (myGM->getBoardSizeY()-1) == row || 0 == col || (myGM->getBoardSizeX()-1) == col) {
                gameBoard[row][col] = '#';
            }

            //print moving character
            else if(myPos.y == row && myPos.x == col) {
                gameBoard[row][col] = myPos.symbol;
            }

            //print empty space on board
            else {
                gameBoard[row][col] = ' ';
            }
            MacUILib_printf("%c", gameBoard[row][col]);
        }
        MacUILib_printf("\n");
    }



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
