#ifndef _GAME_H
#define _GAME_H

#include "SDL2/SDL.h"

class Game
{
  private:
    enum
    {
        mapWidthInTiles = 10,
        mapHeightInTiles = 10,
    };
    int map[mapWidthInTiles][mapHeightInTiles];

  public:
    int mapXOffset, mapYOffset;
    int tileWidth, tileHeight;

    Game();
    ~Game();

    void init();
    void update();
    void render(SDL_Renderer *renderer);
    void quit();
};

#endif