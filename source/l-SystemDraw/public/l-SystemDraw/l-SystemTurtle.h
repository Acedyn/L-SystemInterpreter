#pragma once

#include <Imath/ImathMatrix.h>


namespace LSystem {
    class Turtle
    {
    public:
        Turtle();
        ~Turtle();
    
    private:
        Imath::M44f transform;
    };
}
