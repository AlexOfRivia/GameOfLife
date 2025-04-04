#include "Game.h"
#include "Engine.h"
#include "ConwayEngine.h"
#include "raylib.h"
#include <iostream>

//Main function of the program.
int main() 
{
    //Create a Game object.
    Game game;
    game.initialize(); //Initialize the game.

    // Main game loop.
    while (!WindowShouldClose()) 
    {
        game.update(); //Update the game state.
        game.draw();   //Draw the game state.
    }

    //The game will end automatically after exiting the loop (Game destructor will be called).
    return 0;
}