#include "l-SystemDraw/l-SystemTurtle.h"
#include "l-SystemDraw/l-SystemDrawBuffer.h"
#include "l-SystemDraw/l-SystemReader.h"

#ifdef pxr_FOUND
    #include "l-SystemDraw/l-SystemOutputUSD.h"
#endif

#include <iostream>

int main()
{
    ////////////////////////////////////////
    // Testing classes individualy
    ////////////////////////////////////////

    std::cout << "########################################" << std::endl;
    std::cout << "TESTING classes : " << std::endl << std::endl;

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
    std::cout << "TESTING reader : " << std::endl << std::endl;

    LSystemWord testWord1("^F[\\[+F+F]F]-FF");
    LSystem::Reader* testReader1 = new LSystem::Reader(testWord1);
    testReader1->parseWord();

    std::cout << std::endl << "Reader test COMPLETED" << std::endl << std::endl << std::endl;

    std::cout << "########################################" << std::endl;
    std::cout << "TESTING export : " << std::endl << std::endl;

    #ifdef pxr_FOUND
        std::cout << "Test exportUSD1: " << testReader1->getDrawBuffer().exportUSD("LSystem", "./l-SystemDrawTest.usda") << std::endl;
    #else
        std::cout << "USD not found" << std::endl;
    #endif

    std::cout << std::endl << "Export test COMPLETED" << std::endl << std::endl << std::endl;

    std::cout << "\nTEST COMPLETED" << std::endl;
    std::cin.get();
}
