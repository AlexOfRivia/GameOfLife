#pragma once

//Base class Engine, containing common logic for different game variants.
#include "raylib.h"
#include <vector>
#include <iostream>

class Game;

class Engine 
{
public:
    //Virtual destructor is crucial for polymorphism.
    virtual ~Engine() = default;

    //Method to initialize the game engine. Takes window width and height.
    virtual void initialize(int screenWidth, int screenHeight) = 0;

    //Method to update the game state. Pure virtual, must be implemented in derived classes.
    virtual void update() = 0;

    //Method to draw the current game state. Pure virtual, must be implemented in derived classes.
    virtual void draw() = 0;

    //Method to set the pointer to the Game object.
    void setGame(Game* game) { m_game = game; }

protected:
    //Width and height of the game window.
    int m_screenWidth;
    int m_screenHeight;

    //Pointer to the Game object. Used to interact with game-specific logic.
    Game* m_game;
};