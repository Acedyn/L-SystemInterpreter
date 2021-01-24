#include "l-SystemDraw/l-SystemTurtle.h"

#include <iostream>

int main()
{
    ////////////////////////////////////////
    // Testing classes individualy
    ////////////////////////////////////////

    std::cout << "########################################" << std::endl;
    std::cout << "TESTING classes : " << std::endl;

    LSystem::Turtle testTurtle1({1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0});
    testTurtle1.moveForward();
    std::cout << "Test turtle1 : " << testTurtle1.getTransform() << std::endl;

    std::cout << std::endl << "Classes test COMPLETED" << std::endl << std::endl << std::endl;


    std::cout << "\nTEST COMPLETED" << std::endl;
    std::cin.get();
}
