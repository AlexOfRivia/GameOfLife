#pragma once
#include "Engine.h"
#include "raylib.h"
#include <vector>
#include <iostream>

//Class ConwayEngine inherits from Engine and implements the logic of Conway's Game of Life.
class ConwayEngine : public Engine 
{
public:
    //Constructor.
    ConwayEngine();

    //Implementation of the initialize method from the base class Engine.
    void initialize(int screenWidth, int screenHeight) override;

    //Implementation of the update method from the base class Engine.
    void update() override;

    //Implementation of the draw method from the base class Engine.
    void draw() override;

private:
    //Grid of cells representing the game state.
    bool* m_grid;
    bool* m_bufferGrid; //Buffer for calculations to avoid problems with updating neighbors.
    int m_gridWidth;  //Width of the grid in cells.
    int m_gridHeight; //Height of the grid in cells.
    int m_cellSize; //Size of a single cell in pixels.
    bool m_isPaused;    //Pause flag.
    float m_updateInterval; //Update interval for the game state.
    float m_lastUpdateTime; //Last update time.

    //Method to calculate the number of living neighbors for a given cell.
    int countLivingNeighbors(int x, int y);

    //Method to convert screen coordinates to grid index.
    int getIndex(int x, int y);

    //Method to clear the grid.
    void clearGrid();
};