#ifndef _GAME_H
#define _GAME_H

#include "SDL2/SDL.h"
#include <vector>

#define PLAY 0
#define EDIT 1

class Game
{
private:
  int state;

private:
  std::vector<std::vector<int>> map;
  int grid;

public:
  int mapWidthInTiles;
  int mapHeightInTiles;
  int mapAnchorX, mapAnchorY;
  int mapXOffset, mapYOffset;
  int tileWidth, tileHeight;

  Game();
  ~Game();

  void updateMapAnchor();
  void randomMap();
  void clearMap();
  void toggleGrid();
  void toggleState();

  void init();
  void update();
  void play();
  void edit();
  void render(SDL_Renderer *renderer);
  void quit();
};

#endif