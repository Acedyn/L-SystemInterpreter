#include "l-SystemInterpreter/l-SystemConcreteModule.h"
#include "l-SystemInterpreter/l-SystemAbstractModule.h"
#include "l-SystemInterpreter/l-SystemParameters.h"
#include "l-SystemInterpreter/l-SystemWord.h"
#include "l-SystemInterpreter/l-SystemExpression.h"
#include "l-SystemInterpreter/l-SystemRule.h"
#include "l-SystemInterpreter/l-System.h"

#include <iostream>


int main()
{
    ////////////////////////////////////////
    // Testing classes individualy
    ////////////////////////////////////////

    std::cout << "########################################" << std::endl;
    std::cout << "TESTING classes : " << std::endl;
    
    // Test concrete module
    LSystemConcreteModule testConcreteModule1('A', "47, 75, aed, 4a8, 7.48, 7aza");
    std::cout << "Test module1 : " << testConcreteModule1 << std::endl;
    // Test parameters
    LSystemParameters testParameters1({"AD", "F", "AS"}, {5.0f, 47.4f, 40.8f});
    LSystemConcreteModule testConcreteModule2('B', "AD, AS, 5.4", &testParameters1);
    std::cout << "Test module2 : " << testConcreteModule2 << std::endl;
    // Test word
    LSystemWord testWord1("C(AD, 50, 3.5)X(AS, F)%R!!D()?(0.21)", &testParameters1);
    std::cout << "Test word1 : " << testWord1 << std::endl;
    // Test abstract module
    LSystemAbstractModule testAbstractModule1('B', "s, ot, 4er!");
    testAbstractModule1.setLinkedModule(&testConcreteModule2);
    testAbstractModule1.setLinkedModule(&testConcreteModule1);
    std::cout << "Test abstractModule1 : " << testAbstractModule1 << std::endl;
    // Test expressions
    LSystemExpression testExpression1("-7+8/2^2-er+AD", &testAbstractModule1, &testParameters1);
    std::cout << "Test expression1 : " 
        << testExpression1.getExpression() 
        << " = " 
        << testExpression1.parseDecimalExpression()
        << std::endl;
    // Test rule
    LSystemRule testRule1({'B', "a, b, c"}, {"A(1, 2, 3, AS)F!(8.1, AS)T(11))", &testParameters1}, LSystemExpression(), nullptr, 0.5);
    std::cout << "Test rule1 : " << testRule1 << std::endl;
    LSystemRule testRule2({'B', "a, b, c"}, {"A(1, 2, 3, AS)TY?(7,8.0)A(4, 5, 6, F)?T", &testParameters1}, LSystemExpression(), nullptr, 0.5);
    std::cout << "Test rule2 : " << testRule2 << std::endl;
    LSystemRule testRule3({'A', "a, b, c, d"}, {"PPPT(AD)PPP", &testParameters1}, {"d==AS"}, &testParameters1);
    std::cout << "Test rule3 : " << testRule3 << std::endl;
    // Test lSystem
    LSystem testLSystem1({"PRB(1, F, 0.5)?", &testParameters1}, {&testRule1, &testRule2, &testRule3});
    std::cout << "Test lSystem1 iteration 0 : " << *(testLSystem1.getOutputWord()) << std::endl;
    testLSystem1.iterate();
    std::cout << "Test lSystem1 iteration 1 : " << *(testLSystem1.getOutputWord()) << std::endl;
    testLSystem1.iterate();
    std::cout << "Test lSystem1 iteration 2 : " << *(testLSystem1.getOutputWord()) << std::endl;
    

    std::cout << std::endl << "Classes test COMPLETED" << std::endl << std::endl << std::endl;


    ////////////////////////////////////////
    // Testing Anabaena Catenula model
    ////////////////////////////////////////

    std::cout << "########################################" << std::endl;
    std::cout << "TESTING Anabaena Catenula model :" << std::endl;

    // Parameters
    LSystemParameters parameters({"A", "B", "W", "AS", "BS", "R", "L"}, {1.0f, 2.0f, 0.5f, 2.0f, 1.0f, 1.0f, -1.0f});

    // Axiom
    // LSystemWord axiom("!(0.5)F(1,2,1)");
    LSystemWord axiom("!(W)F(BS,B,R)", &parameters);

    // Rule 1
    // LSystemRule rule1(LSystemModule('F', "sto"), new LSystemWord("F(2,1,-1)F(1,2,1)"));
    LSystemRule rule1({'F', "sto"}, {"F(AS,A,L)F(BS,B,R)", &parameters});
    rule1.setMainCondition({"t==A&&o==R"}, &parameters);

    // Rule 2
    // LSystemRule rule2(LSystemModule('F', "sto"), new LSystemWord("F(1,2,-1)F(2,1,1)"));
    LSystemRule rule2({'F', "sto"}, {"F(BS,B,L)F(AS,A,R)", &parameters});
    rule2.setMainCondition({"t==A&&o==L"}, &parameters);

    // Rule 3
    // LSystemRule rule3(LSystemModule('F', "sto"), new LSystemWord("F(2,1,1)"));
    LSystemRule rule3({'F', "sto"}, {"F(AS,A,R)", &parameters});
    rule3.setMainCondition({"t==B&&o==R"}, &parameters);

    // Rule 4
    // LSystemRule rule4(LSystemModule('F', "sto"), new LSystemWord("F(2,1,-1)"));
    LSystemRule rule4({'F', "sto"}, {"F(AS,A,L)", &parameters});
    rule4.setMainCondition({"t==B&&o==L"}, &parameters);

    // LSystem
    LSystem anabaenaCatenulaModel(axiom, {&rule1, &rule2, &rule3, &rule4});

    std::cout << *(anabaenaCatenulaModel.getOutputWord()) << std::endl;
    for(int i = 0; i < 1; i++)
    {
        anabaenaCatenulaModel.iterate();
        std::cout << *(anabaenaCatenulaModel.getOutputWord()) << std::endl;
    }

    std::cout << std::endl << "Anabaena Catenula model test COMPLETED" << std::endl << std::endl << std::endl;

    std::cout << "\nTEST COMPLETED" << std::endl;
    std::cin.get();
}
