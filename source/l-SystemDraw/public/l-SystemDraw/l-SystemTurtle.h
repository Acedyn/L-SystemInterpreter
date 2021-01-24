#pragma once

#include <Imath/ImathMatrix.h>
#include <Imath/ImathColor.h>


namespace LSystem 
{
    class Turtle
    {
    public:
        // Constructors / Destructors
        Turtle(Imath::M44f _transform = Imath::M44f()) : transform(_transform) { }
        Turtle(
            Imath::M44f _transform, 
            Imath::C4f _color = Imath::C4f(1.0f, 1.0f, 1.0f, 1.0f), 
            float _width = 1.0f);
        Turtle(
            Imath::M44f _transform,
            float _width = 1.0f, 
            Imath::C4f _color = Imath::C4f(1.0f, 1.0f, 1.0f, 1.0f));
        ~Turtle();

        // Getters / Setters
        Imath::M44f getTransform() const { return transform; }
        void setTransform(Imath::M44f _transform) { transform = _transform; }
        Imath::C4f getColor() const { return color; }
        void setColor(Imath::C4f _color) { color = _color; }
        float getWidth() const { return width; }
        void setWidth(float _width) { width = _width; }
        float getMoveStep() const { return moveStep; }
        void setMoveStep(float _moveStep) { moveStep = _moveStep; }
        float getTurnStep() const { return turnStep; }
        void setTurnStep(float _turnStep) { turnStep = _turnStep; }
        float getPitchStep() const { return pitchStep; }
        void setPitchStep(float _pitchStep) { pitchStep = _pitchStep; }
        float getRollStep() const { return rollStep; }
        void setRollStep(float _rollStep) { rollStep = _rollStep; }

        // Movement
        void moveForward(float _moveStep);
        void moveForward();
        void jumpForward(float _moveStep);
        void jumpForward();
        void turnLeft(float _turnStep);
        void turnLeft();
        void turnRight(float _turnStep);
        void turnRight();
        void pitchUp(float _pitchStep);
        void pitchUp();
        void pitchDown(float _pitchStep);
        void pitchDown();
        void rollLeft(float _rollStep);
        void rollLeft();
        void rollRight(float _rollStep);
        void rollRight();
        void turnAround();

        // State stack
        void pushState();
        void popState();

        // Drawing
        void increaseColor(Imath::C4f _colorStep);
        void increaseColor();
        void decreaseColor(Imath::C4f _colorStep);
        void decreaseColor();
        void increaseWidth(float _widthStep);
        void increaseWidth();
        void decreaseWidth(float _widthStep);
        void decreaseWidth();
    
    private:
        Imath::M44f transform;
        Imath::C4f color;
        float width;

        float moveStep = 1.0f;
        float turnStep = 1.0f;
        float pitchStep = 1.0f;
        float rollStep = 1.0f;

        Imath::C4f colorStep;
        float widthStep = 0.1f;
    };
}
