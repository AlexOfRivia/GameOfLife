#include "ConwayEngine.h"
#include "Game.h" // Needed because ConwayEngine uses Game::restart()
#include <iostream>
#include "raylib.h"

//Constructor.
ConwayEngine::ConwayEngine() : m_grid(nullptr), m_bufferGrid(nullptr), m_cellSize(10), m_isPaused(true), m_updateInterval(0.5f), m_lastUpdateTime(0.0f) {}

//Implementation of the initialize method for the ConwayEngine class.
void ConwayEngine::initialize(int screenWidth, int screenHeight) 
{
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
    
    //Calculate grid dimensions based on window size and cell size.
    m_gridWidth = screenWidth / m_cellSize;
    m_gridHeight = screenHeight / m_cellSize;

    //Allocate memory for the grid and buffer.
    m_grid = new bool[m_gridWidth * m_gridHeight];
    m_bufferGrid = new bool[m_gridWidth * m_gridHeight];

    //Fill the grid with random values (initial game state).
    for (int i = 0; i < m_gridWidth * m_gridHeight; ++i) 
    {
        m_grid[i] = (rand() % 2 == 0); //Random value: true (alive) or false (dead).
        m_bufferGrid[i] = false;
    }
    ClearBackground(BLACK);
}

//Implementation of the update method for the ConwayEngine class.
void ConwayEngine::update() 
{
    //Handle keyboard events.
    if (IsKeyPressed(KEY_SPACE)) 
    {
        m_isPaused = !m_isPaused; //Pause/resume simulation.
    }
    if (IsKeyPressed(KEY_R)) 
    {
        m_game->restart(); //Call the restart method from the Game class.
    }
    if (IsKeyPressed(KEY_C)) 
    {
        clearGrid(); //Clearing the grid
    }
    if (IsKeyPressed(KEY_UP)) 
    {
        m_updateInterval = std::max(0.1f, m_updateInterval - 0.1f); //Increase speed.
    }
    if (IsKeyPressed(KEY_DOWN)) 
    {
        m_updateInterval += 0.1f; //Decrease speed.
    }

    //Handle mouse events.
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
    {
        Vector2 mousePosition = GetMousePosition();
        int x = static_cast<int>(mousePosition.x) / m_cellSize;
        int y = static_cast<int>(mousePosition.y) / m_cellSize;
        if (x >= 0 && x < m_gridWidth && y >= 0 && y < m_gridHeight)
        {
            int index = getIndex(x, y);
            m_grid[index] = !m_grid[index]; //Toggle cell state.
        }
    }

    if (!m_isPaused && (GetTime() - m_lastUpdateTime) >= m_updateInterval) 
    {
        //Update the game state only when it's not paused and the update interval has passed.
        for (int y = 0; y < m_gridHeight; ++y) 
        {
            for (int x = 0; x < m_gridWidth; ++x) 
            {
                int livingNeighbors = countLivingNeighbors(x, y);
                int index = getIndex(x, y);

                //Implementation of Conway's Game of Life rules.
                if (m_grid[index]) { //Alive cell.
                    if (livingNeighbors < 2 || livingNeighbors > 3) 
                    {
                        m_bufferGrid[index] = false; //Dies.
                    } else {
                        m_bufferGrid[index] = true; //Remains alive.
                    }
                } else { //Dead cell.
                    if (livingNeighbors == 3) 
                    {
                        m_bufferGrid[index] = true; //Born.
                    } else {
                        m_bufferGrid[index] = false; //Remains dead.
                    }
                }
            }
        }

        //Copy the state from the buffer to the main grid.
        for (int i = 0; i < m_gridWidth * m_gridHeight; ++i) 
        {
            m_grid[i] = m_bufferGrid[i];
        }

        m_lastUpdateTime = GetTime();
    }
}

//Implementation of the draw method for the ConwayEngine class.
void ConwayEngine::draw() 
{
    //Drawing the grid and cells.
    for (int y = 0; y < m_gridHeight; ++y) 
    {
        for (int x = 0; x < m_gridWidth; ++x) 
        {
            int index = getIndex(x, y);
            if (m_grid[index]) 
            {
                DrawRectangle(x * m_cellSize, y * m_cellSize, m_cellSize, m_cellSize, GREEN);
            } else {
                DrawRectangle(x * m_cellSize, y * m_cellSize, m_cellSize, m_cellSize, DARKGRAY);
            }
        }
    }
    if (m_isPaused) 
    {
        DrawText("Paused. Press Space to Continue.", 10, 10, 20, WHITE);
    }
}

//Implementation of the countLivingNeighbors method.
int ConwayEngine::countLivingNeighbors(int x, int y) 
{
    int count = 0;
    //Iterate through neighbors (including the cell itself).
    for (int i = -1; i <= 1; ++i) 
    {
        for (int j = -1; j <= 1; ++j) 
        {
            if (i == 0 && j == 0) continue; //Skip the cell itself.
            int nx = x + i;
            int ny = y + j;
            //Check if the neighbor is within the grid bounds.
            if (nx >= 0 && nx < m_gridWidth && ny >= 0 && ny < m_gridHeight) 
            {
                int neighborIndex = getIndex(nx, ny);
                if (m_grid[neighborIndex]) 
                {
                    count++; //Count the living neighbor.
                }
            }
        }
    }
    return count;
}

//Implementation of the getIndex method.
int ConwayEngine::getIndex(int x, int y) 
{
    return y * m_gridWidth + x;
}

void ConwayEngine::clearGrid() 
{
    for (int i = 0; i < m_gridWidth * m_gridHeight; ++i) 
    {
        m_grid[i] = false;
    }
}