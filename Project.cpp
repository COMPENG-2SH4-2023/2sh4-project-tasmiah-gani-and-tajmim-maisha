#include <iostream>
#include "MacUILib.h"
#include "objPos.h" //fundamental building block for project 
#include "GameMechs.h"



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
    myGM = new GameMechs(26, 13); //makes board size 26x13

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
    //clear input field in GM 
    myGM->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    


    MacUILib_printf("BoardSize: %dx%d", myGM->getBoardSizeX(), myGM->getBoardSizeY());
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
