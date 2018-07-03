#include <iostream>
#include <vector>

#include <ctime>

#include "game.h"
#include "System.h"

Game::Game() {}

Game::~Game() {}

void Game::updateMapAnchor()
{
    mapAnchorX = mapXOffset;
    mapAnchorY = mapYOffset;
}

void Game::toggleGrid()
{
    grid = !grid;
}

void Game::toggleState()
{
    state = !state;
}

void Game::clearMap()
{
    for (int x = 0; x < mapWidthInTiles; x++)
    {
        for (int y = 0; y < mapHeightInTiles; y++)
        {
            map[x][y] = 0;
        }
    }
}

void Game::init()
{
    mapAnchorX = 0;
    mapAnchorY = 0;
    mapXOffset = 0;
    mapYOffset = 0;
    grid = 1;
    state = PLAY;

    mapWidthInTiles = 150;
    mapHeightInTiles = 100;

    tileWidth = 20;
    tileHeight = 20;

    srand(time(NULL));
    for (int x = 0; x < mapWidthInTiles; x++)
    {
        std::vector<int> row;
        for (int y = 0; y < mapHeightInTiles; y++)
        {
            row.push_back(0);
        }
        map.push_back(row);
    }
}

void Game::randomMap()
{
    for (int x = 0; x < mapWidthInTiles; x++)
    {
        for (int y = 0; y < mapHeightInTiles; y++)
        {
            if (rand() % 20 == 1)
                map[x][y] = 1;
            else
                map[x][y] = 0;
        }
    }
}

void Game::update()
{
    if (state == PLAY)
    {
        play();
    }
    else if (state == EDIT)
    {
        edit();
    }
}

void Game::play()
{
    std::vector<std::vector<int>> buffer;
    for (int x = 0; x < mapWidthInTiles; x++)
    {
        std::vector<int> row;
        for (int y = 0; y < mapHeightInTiles; y++)
        {
            row.push_back(0);
        }
        buffer.push_back(row);
    }

    for (int y = 0; y < mapHeightInTiles; y++)
    {
        for (int x = 0; x < mapWidthInTiles; x++)
        {
            int sum = 0;
            for (int yy = -1; yy <= 1; yy++)
            {
                for (int xx = -1; xx <= 1; xx++)
                {
                    if (xx == 0 && yy == 0)
                        continue;

                    int tx = (((x + xx) % mapWidthInTiles) + mapWidthInTiles) % mapWidthInTiles;
                    int ty = (((y + yy) % mapHeightInTiles) + mapHeightInTiles) % mapHeightInTiles;
                    sum += map[tx][ty];
                }
            }

            int alive = map[x][y];
            if (alive)
            {
                if (sum == 2 || sum == 3)
                    buffer[x][y] = 1;
                else
                    buffer[x][y] = 0;
            }
            else
            {
                if (sum == 3)
                    buffer[x][y] = 1;
            }
        }
    }

    for (int x = 0; x < mapWidthInTiles; x++)
    {
        for (int y = 0; y < mapHeightInTiles; y++)
        {
            map[x][y] = buffer[x][y];
        }
    }
}

void Game::edit()
{
}

void Game::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 0);
    System::drawRect(mapXOffset, mapYOffset, tileWidth * mapWidthInTiles, tileHeight * mapHeightInTiles);

    for (int y = 0; y < mapHeightInTiles; y++)
    {
        for (int x = 0; x < mapWidthInTiles; x++)
        {
            if (grid)
            {
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 20);
                System::drawRect(mapXOffset + x * tileWidth, mapYOffset + y * tileHeight, tileWidth, tileHeight);
            }
            if (map[x][y] == 1)
            {
                SDL_SetRenderDrawColor(renderer, 150, 150, 150, 20);
                System::fillRect(mapXOffset + x * tileWidth, mapYOffset + y * tileHeight, tileWidth, tileHeight);
            }
        }
    }
}

void Game::quit()
{
}