#include "Game.h"
#include "ConwayEngine.h"
#include <iostream>
#include "raylib.h"

//Constructor of the Game class.
Game::Game() : m_engine(nullptr), m_screenWidth(800), m_screenHeight(600), m_gameRunning(true) 
{
    //Initialize Raylib
    InitWindow(m_screenWidth, m_screenHeight, "Conway's Game of Life");
    SetTargetFPS(60); //Set the target frame rate.
}

//Destructor of the Game class.
Game::~Game() 
{
    //Release resources.
    delete m_engine;
    CloseWindow(); //Close the Raylib window.
}

//Method to initialize the game.
void Game::initialize() 
{
    //Create a specific game engine (ConwayEngine).
    m_engine = new ConwayEngine();
    m_engine->setGame(this); //Set the pointer to the Game object in Engine.
    m_engine->initialize(m_screenWidth, m_screenHeight); //Initialize the engine.
}

//Method to update the game state.
void Game::update() 
{
    if (m_gameRunning) 
    {
        m_engine->update(); //Delegate update to the engine.
    }
}

//Method to draw the game state.
void Game::draw() 
{
    BeginDrawing();
    ClearBackground(BLACK); //Clear the background.
    m_engine->draw();   //Delegate drawing to the engine.
    EndDrawing();
}

void Game::restart() 
{
    delete m_engine;
    m_engine = new ConwayEngine();
    m_engine->setGame(this);
    m_engine->initialize(m_screenWidth, m_screenHeight);
}