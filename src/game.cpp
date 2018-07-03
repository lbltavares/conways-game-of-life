#include "game.h"
#include "System.h"

Game::Game() {}

Game::~Game() {}

void Game::init()
{
    mapXOffset = 0;
    mapYOffset = 0;
    tileWidth = 30;
    tileHeight = 30;

    for (int y = 0; y < mapHeightInTiles; y++)
        for (int x = 0; x < mapWidthInTiles; x++)
            map[x][y] = 0;
}

void Game::update()
{
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