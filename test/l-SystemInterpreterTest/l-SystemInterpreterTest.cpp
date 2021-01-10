#include "l-SystemInterpreterTest.h"

#include "l-SystemInterpreter/l-SystemModule.h"
// #include "l-SystemInterpreter/l-SystemWord.h"
// #include "l-SystemInterpreter/l-SystemExpression.h"
// #include "l-SystemInterpreter/l-SystemRule.h"
// #include "l-SystemInterpreter/l-System.h"

#include <iostream>


int main()
{
    ////////////////////////////////////////
    // Testing classes individualy
    ////////////////////////////////////////

    std::cout << "########################################" << std::endl;
    std::cout << "TESTING classes : " << std::endl;
    
    LSystemModule testModule1('A', "47, 75, aed, 4a8, 7.48, 7aza");
    std::cout << "Test module1 : " << testModule1 << std::endl;

    std::cout << std::endl << "Classes test completed" << std::endl << std::endl << std::endl;


    ////////////////////////////////////////
    // Testing Anabaena Catenula model
    ////////////////////////////////////////

    std::cout << "########################################" << std::endl;
    std::cout << "TESTING Anabaena Catenula model :" << std::endl;

    // Axiom
    // LSystemWord axiom("!(0.5)F(1,2,1)");
    // LSystemWord axiom("!(W)F(BS,B,R)");

    // Rule 1
    // LSystemRule rule1(LSystemModule('F', "sto"), new LSystemWord("F(2,1,-1)F(1,2,1)"));
    // LSystemRule rule1(LSystemModule('F', "sto"), new LSystemWord("F(AS,A,L)F(BS,B,R)"));
    // rule1.setMainCondition(LSystemExpression("t==A&&o==R"));

    // Rule 2
    // LSystemRule rule2(LSystemModule('F', "sto"), new LSystemWord("F(1,2,-1)F(2,1,1)"));
    // LSystemRule rule2(LSystemModule('F', "sto"), new LSystemWord("F(BS,B,L)F(AS,A,R)"));
    // rule2.setMainCondition(LSystemExpression("t==A&&o==L"));

    // Rule 3
    // LSystemRule rule3(LSystemModule('F', "sto"), new LSystemWord("F(2,1,1)"));
    // LSystemRule rule3(LSystemModule('F', "sto"), new LSystemWord("F(AS,A,R)"));
    // rule3.setMainCondition(LSystemExpression("t==B&&o==R"));

    // Rule 4
    // LSystemRule rule4(LSystemModule('F', "sto"), new LSystemWord("F(2,1,-1)"));
    // LSystemRule rule4(LSystemModule('F', "sto"), new LSystemWord("F(AS,A,L)"));
    // rule4.setMainCondition(LSystemExpression("t==B&&o==L"));

    // LSystem
    // LSystem anabaenaCatenulaModel(&axiom, {&rule1, &rule2, &rule3, &rule4});

    // anabaenaCatenulaModel.iterate();

    std::cout << std::endl << "Anabaena Catenula model test completed" << std::endl << std::endl << std::endl;

    std::cout << "\ntest completed" << std::endl;
    std::cin.get();
}
