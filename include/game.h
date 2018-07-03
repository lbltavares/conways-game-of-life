#ifndef _GAME_H
#define _GAME_H

#include "SDL2/SDL.h"

class Game
{
  private:
    enum
    {
        mapWidthInTiles = 20,
        mapHeightInTiles = 15,
    };
    int map[mapWidthInTiles][mapHeightInTiles];
    int buffer[mapWidthInTiles][mapHeightInTiles];

  public:
    int mapAnchorX, mapAnchorY;
    int mapXOffset, mapYOffset;
    int tileWidth, tileHeight;

    Game();
    ~Game();

    void updateMapAnchor();
    void setMap(int m[mapWidthInTiles][mapHeightInTiles], int v);
    void bufferToMap();

    void init();
    void update();
    void render(SDL_Renderer *renderer);
    void quit();
};

#endif