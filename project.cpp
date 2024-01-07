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

    location getPosition()
    {
        return Position;
    }

    void SetPen()
    {
        Pen = !Pen;
    }

    void SetPen(bool value)
    {
        Pen = value;
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

    void WalkForwards(SDL_Renderer *renderer, int n)
    {
        location Old = Position;
        Position.x += (int)(n * sin(Direction * M_PI / 180));
        Position.y += (int)(n * cos(Direction * M_PI / 180));
        if (Pen)
        {
            SDL_SetRenderDrawColor(renderer, CurrentColour.r, CurrentColour.g, CurrentColour.b, 255);
            SDL_RenderDrawLineF(renderer, Old.x, Old.y, Position.x, Position.y);
        }
    }

    void RotateClockwise(int inDegrees)
    {
        Direction = (Direction + inDegrees) % 360;
    }
};

int DisplayMenu(char **Options, int optionCount)
{
    out("Please select from one of the following options:");
    for (int i = 0; i < optionCount; i++)
    {
        printf("                %i. %s\n", i + 1, Options[i]);
    }
    fflush(stdout);
    int output;
    scanf("%d", &output);
    fflush(stdin);
    return output;
}

void DrawBasicTriangle(Turtle *Steve, SDL_Renderer *renderer, int length)
{
    Steve->WalkForwards(renderer, length);
    Steve->RotateClockwise(120);
    Steve->WalkForwards(renderer, length);
    Steve->RotateClockwise(120);
    Steve->WalkForwards(renderer, length);
    Steve->RotateClockwise(120);
    log("Triangle Drawn");
}

void rTriangle(Turtle *Steve, SDL_Renderer *renderer, int startSize, int RecurseMax, int CurrentRecurse)
{
    log("entering new recursion");

    if (CurrentRecurse < RecurseMax)
    {
        rTriangle(Steve, renderer, startSize, RecurseMax, CurrentRecurse + 1);
        rTriangle(Steve, renderer, startSize, RecurseMax, CurrentRecurse + 1);
        rTriangle(Steve, renderer, startSize, RecurseMax, CurrentRecurse + 1);
    }
    Steve->SetPen();
    DrawBasicTriangle(Steve, renderer, startSize / pow(2, CurrentRecurse));
    Steve->SetPen();
    Steve->WalkForwards(renderer, (startSize / pow(2, CurrentRecurse)) * 2);
    Steve->RotateClockwise(120);
    Steve->SetPen();
    DrawBasicTriangle(Steve, renderer, startSize / pow(2, CurrentRecurse));
    Steve->SetPen();
    Steve->WalkForwards(renderer, (startSize / pow(2, CurrentRecurse)) * 2);
    Steve->RotateClockwise(120);
    Steve->SetPen();
    DrawBasicTriangle(Steve, renderer, startSize / pow(2, CurrentRecurse));
    Steve->SetPen();
    Steve->WalkForwards(renderer, (startSize / pow(2, CurrentRecurse)) * 2);
    Steve->RotateClockwise(120);
    Steve->WalkForwards(renderer, (startSize / pow(2, CurrentRecurse)) * 4);
    Steve->RotateClockwise(120);
    log("recurse completed");
}

void SierpinskiTriangle(Turtle *Steve, SDL_Renderer *renderer, int startSize, int RecurseAmount)
{
    Steve->SetPen(0);
    Steve->SetPosition(location(0, startSize));
    Steve->setDirection(90);
    rTriangle(Steve, renderer, startSize, RecurseAmount, 1);
}

colour EnterColour()
{
    colour output;
    out("enter colour in format R G B 255 255 255:\n");
    scanf("%d %d %d", &output.r, &output.g, &output.b);
    fflush(stdin);
    return output;
}

void DrawBackground(SDL_Renderer *renderer, colour in)
{
    SDL_SetRenderDrawColor(renderer, in.r, in.g, in.b, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    log("SDL Initialised");
    SDL_Window *window = SDL_CreateWindow("Jeremy", 20, 20, 2000, 2000, 0);
    log("Window Initialised");
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    log("Renderer Initialised");
    Turtle Steve = *new Turtle();
    log("Turtle Initialised");
    bool finished = 0;
    int i = 0;
    int angle = 0;
    int length = 0;
    colour Background = white;

    out("Press any key to begin");
    while (!finished)
    {
        SDL_Event Event;
        while (SDL_PollEvent(&Event))
        {
            switch (Event.type)
            {
            case SDL_QUIT:
                finished = 1;
                break;
            }
        }

        char **options = (char **)calloc(4, 30);
        options[0] = "Quit";
        options[1] = "Change Background Colour";
        options[2] = "Change Pen Colour";
        options[3] = "Draw Shape";
        switch (DisplayMenu(options, 4))
        {
        case 1:
            finished = 1;
            break;
        case 2:
            Background = EnterColour();
            DrawBackground(renderer, Background);
            break;
        case 3:
            Steve.SetColour(EnterColour());
            break;
        case 4:
            char **ShapeOptions = (char **)calloc(1, 10);
            ShapeOptions[0] = "Triangle";
            SDL_ShowWindow(window);
            SDL_SetRenderDrawColor(renderer, Background.r, Background.g, Background.b, 255);
            SDL_RenderClear(renderer);
            switch (DisplayMenu(ShapeOptions, 1))
            {
            case 1:
                out("Please enter a recursion number");
                int recurseNum;
                scanf("%d", &recurseNum);
                fflush(stdin);
                SierpinskiTriangle(&Steve, renderer, pow(2, recurseNum - 1) * 100, recurseNum);
                break;
            }
            SDL_RenderPresent(renderer);
            break;
        }
    }
    SDL_Quit();
    return 0;
}