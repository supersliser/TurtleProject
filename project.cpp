#include "../DrawingProject/colour.h"
#include "../DrawingProject/location.h"
#include <SDL2/SDL.h>
#include "../DrawingProject/log.h"

class Turtle
{
protected:
    colour CurrentColour;
    location Position;
    bool Pen;
    int Direction;

public:
    Turtle()
    {
        CurrentColour = black;
        Position = location(0, 0);
        Pen = false;
        Direction = 0;
    }

    void SetPen()
    {
        Pen = !Pen;
    }

    void SetColour(colour inColour)
    {
        CurrentColour = inColour;
    }

    void SetPosition(location inPosition)
    {
        Position = inPosition;
    }

    void setDirection(int inDegrees)
    {
        Direction = inDegrees;
    }

    void WalkForwards(SDL_Renderer *renderer, int n, size WindowSize)
    {
        int opposite = n * sin(Direction * M_PI / 180);
        int adjacent = n * cos(Direction * M_PI / 180);
        SDL_SetRenderDrawColor(renderer, CurrentColour.r, CurrentColour.g, CurrentColour.b, 255);
        SDL_RenderDrawLine(renderer, Position.x, Position.y, opposite + Position.x, adjacent + Position.y);
    }
};

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    log("SDL Initialised");
    SDL_Window *window = SDL_CreateWindow("Jeremy", 20, 20, 800, 800, 0);
    log("Window Initialised");
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    log("Renderer Initialised");
    Turtle turtle = *new Turtle();
    log("Turtle Initialised");
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    log("Renderer Cleared");
    turtle.SetPosition(location(400, 400));
    turtle.SetPen();
    bool finished = 0;
    int i = 0;
    int angle = 0;
    int length = 0;
    while (!finished)
    {

        SDL_Event Event;
        scanf("%d", &angle);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        turtle.setDirection(angle);
        turtle.WalkForwards(renderer, 200, size(800, 800));
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&Event))
        {
            switch (Event.type)
            {
            case SDL_QUIT:
                finished = 1;
            }
        }
    }
    SDL_Quit();
    return 0;
}