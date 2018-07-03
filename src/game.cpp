#include <iostream>

#include "game.h"
#include "System.h"

Game::Game() {}

Game::~Game() {}

void Game::updateMapAnchor()
{
    mapAnchorX = mapXOffset;
    mapAnchorY = mapYOffset;
}

void Game::init()
{
    mapAnchorX = 0;
    mapAnchorY = 0;
    mapXOffset = 0;
    mapYOffset = 0;

    tileWidth = 20;
    tileHeight = 20;

    setMap(map, 0);

    
}

void Game::update()
{
    setMap(buffer, 0);

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
                    {
                        std::cout << map[x][y];
                        continue;
                    }
                    int tgtx = (x + xx) % mapWidthInTiles;
                    int tgty = (y + yy) % mapHeightInTiles;
                    sum += map[tgtx][tgty];

                    std::cout << map[tgtx][tgty];
                }
                std::cout << std::endl;
            }
            int alive = buffer[x][y];
            if (sum < 2 && alive)
            {
                buffer[x][y] = 0;
            }
            else if (sum > 3 && alive)
            {
                buffer[x][y] = 0;
            }
            else if (sum == 3 && !alive)
            {
                buffer[x][y] = 1;
            }

            std::cin.get();
        }
    }

    bufferToMap();
}

void Game::render(SDL_Renderer *renderer)
{
    for (int y = 0; y < mapHeightInTiles; y++)
    {
        for (int x = 0; x < mapWidthInTiles; x++)
        {
            if (map[x][y] == 1)
            {
                System::fillRect(mapXOffset + x * tileWidth, mapYOffset + y * tileHeight, tileWidth, tileHeight);
            }
            else
            {
                System::drawRect(mapXOffset + x * tileWidth, mapYOffset + y * tileHeight, tileWidth, tileHeight);
            }
        }
    }
}

void Game::quit()
{
}

void Game::setMap(int m[mapWidthInTiles][mapHeightInTiles], int v)
{
    for (int y = 0; y < mapHeightInTiles; y++)
    {
        for (int x = 0; x < mapWidthInTiles; x++)
        {
            m[x][y] = v;
        }
    }
}

void Game::bufferToMap()
{
    for (int y = 0; y < mapHeightInTiles; y++)
    {
        for (int x = 0; x < mapWidthInTiles; x++)
        {
            map[x][y] = buffer[x][y];
        }
    }
}