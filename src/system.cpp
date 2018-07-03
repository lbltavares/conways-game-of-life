#include <iostream>
#include "system.h"

SDL_bool System::running = SDL_FALSE;

SDL_Window *System::window = NULL;
SDL_Renderer *System::renderer = NULL;

const int System::WIDTH = 640;
const int System::HEIGHT = 480;
const int System::FPS = 60;

System::System()
{
    std::cout << "Constructing..." << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(-1);
    }
    window = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WIDTH, HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        exit(-1);
    }
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        exit(-1);
    }
    mouseAnchorX = mouseAnchorY = draggin = 0;
}

System::~System()
{
    std::cout << "Destructing..." << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void System::init()
{
    game.init();
}

void System::loop()
{
    SDL_Event event;
    long time = SDL_GetTicks();
    running = SDL_TRUE;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = SDL_FALSE;
            }
            else if (event.type == SDL_MOUSEWHEEL)
            {
                if (event.wheel.y > 0) // scroll up
                {
                    game.tileWidth += 4;
                    game.tileHeight += 4;
                }
                else if (event.wheel.y < 0) // scroll down
                {
                    game.tileWidth -= 4;
                    game.tileHeight -= 4;
                }

                if (game.tileWidth < 4)
                    game.tileWidth = 4;
                if (game.tileWidth > 20)
                    game.tileWidth = 20;

                if (game.tileHeight < 4)
                    game.tileHeight = 4;
                if (game.tileHeight > 20)
                    game.tileHeight = 20;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                mouseAnchorX = event.motion.x;
                mouseAnchorY = event.motion.y;
                game.updateMapAnchor();
                draggin = 1;
            }
            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                draggin = 0;
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                if (draggin)
                {
                    int mx = event.motion.x;
                    int my = event.motion.y;
                    int dx = mx - mouseAnchorX;
                    int dy = my - mouseAnchorY;
                    game.mapXOffset = game.mapAnchorX + dx;
                    game.mapYOffset = game.mapAnchorY + dy;
                }
                else
                {
                }
            }
            else if (event.type == SDL_KEYUP)
            {
                if (event.key.keysym.sym == SDLK_g)
                {
                    game.toggleGrid();
                }
                else if (event.key.keysym.sym == SDLK_r)
                {
                    game.randomMap();
                }
                else if (event.key.keysym.sym == SDLK_SPACE)
                {
                    game.toggleState();
                }
                else if (event.key.keysym.sym == SDLK_c)
                {
                    game.clearMap();
                }
            }
        }
        if (time + FPS > SDL_GetTicks())
            continue;
        time = SDL_GetTicks();

        update();
        render();
    }
}

void System::update()
{
    game.update();
}

void System::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    game.render(renderer);
    SDL_RenderPresent(renderer);
}

void System::quit()
{
    game.quit();
}

void System::fillRect(int x, int y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderFillRect(renderer, &rect);
}

void System::drawRect(int x, int y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderDrawRect(renderer, &rect);
}

void System::drawLine(int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}