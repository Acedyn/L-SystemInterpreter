#include "l-SystemDraw/l-SystemTurtle.h"
#include "l-SystemDraw/l-SystemDrawBuffer.h"
#include "l-SystemDraw/l-SystemOutputUSD.h"

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
    std::cout << "Test turtle1 : " << testTurtle1 << std::endl;

    std::cout << std::endl << "Classes test COMPLETED" << std::endl << std::endl << std::endl;

    std::cout << "########################################" << std::endl;
    std::cout << "TESTING export : " << std::endl;

    LSystem::DrawBuffer buffer = LSystem::DrawBuffer();
    buffer.setVertices({ {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f} });
    buffer.setIndices({ 0, 3, 3, 2, 2, 1 });
    buffer.exportUSD("LSystem", ".l-SystemDrawTest.usda");

    std::cout << std::endl << "Export test COMPLETED" << std::endl << std::endl << std::endl;

    std::cout << "\nTEST COMPLETED" << std::endl;
    std::cin.get();
}
