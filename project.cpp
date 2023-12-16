#include <SDL2/SDL.h>
#include <stdio.h>
#include "../DrawingProject/window.h"
#include "../DrawingProject/colour.h"
#include "../DrawingProject/location.h"

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

    void setDirection(float inRadians)
    {
        
    }
};

int main()
{


    return 0;
}