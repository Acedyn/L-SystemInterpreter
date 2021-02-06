#include "l-SystemDraw/l-SystemTurtle.h"
#include "l-SystemDraw/l-SystemDrawBuffer.h"
#include "l-SystemDraw/l-SystemOutputUSD.h"
#include "l-SystemDraw/l-SystemReader.h"

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
    testTurtle1.turnLeft();
    std::cout << "Test turtle1 : " << testTurtle1 << std::endl;
    testTurtle1.moveForward();
    std::cout << "Test turtle1 : " << testTurtle1 << std::endl;
    testTurtle1.turnAround();
    std::cout << "Test turtle1 : " << testTurtle1 << std::endl;

    std::cout << std::endl << "Classes test COMPLETED" << std::endl << std::endl << std::endl;

    std::cout << "########################################" << std::endl;
    std::cout << "TESTING reader : " << std::endl;

    LSystemWord testWord1("F-F[-F]F^F");
    LSystem::Reader testReader1(testWord1);

    std::cout << std::endl << "Reader test COMPLETED" << std::endl << std::endl << std::endl;

    std::cout << "########################################" << std::endl;
    std::cout << "TESTING export : " << std::endl;

    LSystem::DrawBuffer buffer1 = LSystem::DrawBuffer();
    buffer1.setVertices({ {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f} });
    buffer1.setIndices({ 0, 3, 3, 2, 2, 1 });
    std::cout << "Test exportUSD1: " << buffer1.exportUSD("LSystem") << std::endl;

    std::cout << std::endl << "Export test COMPLETED" << std::endl << std::endl << std::endl;

    std::cout << "\nTEST COMPLETED" << std::endl;
    std::cin.get();
}
