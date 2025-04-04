#pragma once
#include "Engine.h" // Needed to use the Engine class
#include "raylib.h"

//Class Game, inherits from Engine and contains logic specific to a particular game.
class Game 
{
public:
    //Constructor.
    Game();

    //Destructor.
    ~Game();

    //Method to initialize the game.
    void initialize();

    //Method to update the game state.
    void update();

    //Method to draw the game state.
    void draw();

    //Method to restart the game.
    void restart();

private:
    //Pointer to the Engine object. Used to delegate update and draw logic.
    Engine* m_engine;
    int m_screenWidth;
    int m_screenHeight;
    bool m_gameRunning;
};

