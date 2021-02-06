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

LSystem::Turtle::Turtle(const LSystem::Turtle& _other) :
    transform(_other.getTransform()),
    color(_other.getColor()),
    width(_other.getWidth()),
    lastVertex(_other.getLastVertex()),
    moveStep(_other.getMoveStep()),
    turnStep(_other.getTurnStep()),
    pitchStep(_other.getPitchStep()),
    rollStep(_other.getRollStep()),
    colorStep(_other.getColorStep()),
    widthStep(_other.getWidthStep()),
    states(_other.getStates()) { }


////////////////////////////////////////
// Operators
////////////////////////////////////////

bool LSystem::Turtle::operator==(const Turtle& _other) const
{
    // Test if the transforms matches
    if(transform != _other.getTransform()) { return false; }
    // Test if the color matches
    if(color != _other.getColor()) { return false; }
    // Test if the width matches
    if(width != _other.getWidth()) { return false; }

    return true;
}

bool LSystem::Turtle::operator!=(const Turtle& _other) const
{
    // Test if the transforms matches
    if(transform != _other.getTransform()) { return true; }
    // Test if the color matches
    if(color != _other.getColor()) { return true; }
    // Test if the width matches
    if(width != _other.getWidth()) { return true; }

    return false;
}

std::ostream& operator<<(std::ostream& stream, const LSystem::Turtle& _turtle)
{
    // Print the transform
    stream << "Transform : " << _turtle.getTransform() << "\n";
    // Print the color
    stream << "Color : " << _turtle.getColor() << "\n";
    // Print the width
    stream << "Width : " << _turtle.getWidth() << std::endl;

    return stream;
}


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
    states.emplace_back(*this);
}

void LSystem::Turtle::popState()
{
    transform = states[states.size() - 1].getTransform();
    color = states[states.size() - 1].getColor();
    width = states[states.size() - 1].getWidth();
    lastVertex = states[states.size() - 1].getLastVertex();
    moveStep = states[states.size() - 1].getMoveStep();
    turnStep = states[states.size() - 1].getTurnStep();
    pitchStep = states[states.size() - 1].getPitchStep();
    rollStep = states[states.size() - 1].getRollStep();
    colorStep = states[states.size() - 1].getColorStep();
    widthStep = states[states.size() - 1].getWidthStep();

    states.pop_back();
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
