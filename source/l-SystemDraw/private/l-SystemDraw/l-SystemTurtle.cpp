#include "l-SystemDraw/l-SystemTurtle.h"

#include <cmath>

////////////////////////////////////////
// Constructors / Destructors
////////////////////////////////////////

LSystem::Turtle::Turtle(Imath::M44f _transform, Imath::C4f _color, float _width) :
    transform(_transform),
    color(_color),
    width(_width) { }

LSystem::Turtle::Turtle(Imath::M44f _transform, float _width, Imath::C4f _color) :
    transform(_transform),
    width(_width),
    color(_color) { }


////////////////////////////////////////
// Movement
////////////////////////////////////////

void LSystem::Turtle::moveForward(float _moveStep)
{
    transform.translate(Imath::V3f(0.0f, 0.0f, _moveStep));
}

void LSystem::Turtle::moveForward() { moveForward(moveStep); }

void LSystem::Turtle::jumpForward(float _moveStep)
{
    transform.translate(Imath::V3f(0.0f, 0.0f, _moveStep));
}

void LSystem::Turtle::jumpForward() { jumpForward(moveStep); }

void LSystem::Turtle::turnLeft(float _turnStep)
{
    transform.rotate(Imath::V3f(0.0f, _turnStep * (M_PI / 180), 0.0f));
}

void LSystem::Turtle::turnLeft() { turnLeft(turnStep); }

void LSystem::Turtle::turnRight(float _turnStep)
{
    transform.rotate(Imath::V3f(0.0f, - _turnStep * (M_PI / 180), 0.0f));
}

void LSystem::Turtle::turnRight() { turnRight(turnStep); }

void LSystem::Turtle::pitchUp(float _pitchStep)
{
    transform.rotate(Imath::V3f(_pitchStep * (M_PI / 180), 0.0f, 0.0f));
}

void LSystem::Turtle::pitchUp() { pitchUp(pitchStep); }

void LSystem::Turtle::pitchDown(float _pitchStep)
{
    transform.rotate(Imath::V3f(- _pitchStep * (M_PI / 180), 0.0f, 0.0f));
}

void LSystem::Turtle::pitchDown() { pitchDown(pitchStep); }

void LSystem::Turtle::rollLeft(float _rollStep)
{
    transform.rotate(Imath::V3f(0.0f, 0.0f, - _rollStep * (M_PI / 180)));
}

void LSystem::Turtle::rollLeft() { rollLeft(rollStep); }

void LSystem::Turtle::rollRight(float _rollStep)
{
    transform.rotate(Imath::V3f(0.0f, 0.0f, _rollStep * (M_PI / 180)));
}

void LSystem::Turtle::rollRight() { rollRight(rollStep); }

void LSystem::Turtle::turnAround() { turnLeft(180); }


////////////////////////////////////////
// State stack
////////////////////////////////////////

void LSystem::Turtle::pushState()
{

}

void LSystem::Turtle::popState()
{

}


////////////////////////////////////////
// Drawing
////////////////////////////////////////

void LSystem::Turtle::increaseColor(Imath::C4f _colorStep)
{
    setColor(color + _colorStep);
}

void LSystem::Turtle::increaseColor() { increaseColor(colorStep); }

void LSystem::Turtle::decreaseColor(Imath::C4f _colorStep)
{
    setColor(color - _colorStep);
}

void LSystem::Turtle::decreaseColor() { decreaseColor(colorStep); }

void LSystem::Turtle::increaseWidth(float _widthStep)
{
    setWidth(width + _widthStep);
}

void LSystem::Turtle::increaseWidth() { increaseWidth(widthStep); }

void LSystem::Turtle::decreaseWidth(float _widthStep)
{
    setWidth(width - _widthStep);
}

void LSystem::Turtle::decreaseWidth() { decreaseWidth(widthStep); }
