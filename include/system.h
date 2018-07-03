#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "SDL2/SDL.h"
#include "game.h"

class System
{
  Game game;

private:
  int mouseAnchorX, mouseAnchorY, draggin;

  static SDL_Window *window;
  static SDL_Renderer *renderer;

public:
  static const int WIDTH, HEIGHT, FPS;
  static SDL_bool running;

  System();
  ~System();

  void init();
  void loop();
  void update();
  void render();
  void quit();

public:
  static void fillRect(int x, int y, int w, int h);
  static void drawRect(int x, int y, int w, int h);
  static void drawLine(int x1, int y1, int x2, int y2);
};

#endif