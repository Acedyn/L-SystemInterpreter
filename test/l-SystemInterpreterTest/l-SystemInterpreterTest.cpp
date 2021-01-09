#include "l-SystemInterpreterTest.h"

#include "l-SystemInterpreter/l-SystemModule.h"
#include "l-SystemInterpreter/l-SystemWord.h"
#include "l-SystemInterpreter/l-SystemParameters.h"
// #include "l-SystemInterpreter/l-SystemExpression.h"
// #include "l-SystemInterpreter/l-SystemRule.h"
// #include "l-SystemInterpreter/l-System.h"

#include <iostream>

// Overloading of the ostream << operator to print the module
std::ostream& operator<<(std::ostream& stream, const LSystemModule& module)
{
    // Print the name of the module
    stream << module.getName() << "(";

    // Loop over all the parameters of the module
    std::vector<float> _moduleParameterValues = module.getParameterValues();
    for(auto _moduleParameterValue = _moduleParameterValues.begin(); _moduleParameterValue != _moduleParameterValues.end(); _moduleParameterValue++)
    {
        // Print the parameter value
        stream << *_moduleParameterValue;
        // If this is not the last parameter print a comma
        if(!(_moduleParameterValue != _moduleParameterValues.end()++))
        {
            stream << ",";
        }
    }

    // Print the closing braquet
    stream << ")";

   return stream;
}

int main()
{
    // LSystemModule lSystemModuleRule('F', std::vector<char>{'x', 'y'});
    // LSystemModule rule2MainModule('A');
    // LSystemExpression lSystemCondition(std::string("3/5+1-16"));
    // 3/5+1-4^2*5
    // float result = lSystemCondition.parseDecimalExpression(lSystemModuleRule);
    // std::cout << "Expression : " << lSystemCondition.getExpression() << std::endl;
    // std::cout << "Result : " << result << std::endl << std::endl;
    // LSystemRule lSystemRule(lSystemModuleRule);
    // lSystemRule.setProbabilityFactor(2.0f);
    // LSystemRule rule2(lSystemModuleRule);
    // LSystemRule rule3(rule2MainModule);
    // rule2.setProbabilityFactor(6.0f);
    // rule2.setDerivativeWord(new LSystemWord("AR^++"));
    // rule3.setProbabilityFactor(6.0f);
    // rule3.setDerivativeWord(new LSystemWord("D@&#"));
    // lSystemRule.setDerivativeWord(new LSystemWord(std::string("F(3, 6)P(5)")));
    // LSystemWord lSystemWord("F(5884, 5)A^+=P(4,4410),R");
    // LSystem lSystem(&lSystemWord);
    // lSystem.appendRule(&lSystemRule);
    // lSystem.appendRule(&rule2);
    // lSystem.appendRule(&rule3);
    // lSystem.iterate();

    // LSystemWord* outputWord = lSystem.getOutputWord();
    // for(LSystemWord::Iterator _outWordIterator = outputWord->begin(); _outWordIterator != outputWord->end(); _outWordIterator++)
    // {
        // std::cout << "Output module : " << (*_outWordIterator)->getName() << std::endl;
    // }
    // std::cout << std::endl;

    // lSystem.iterate();
    // outputWord = lSystem.getOutputWord();
    // for(LSystemWord::Iterator _outWordIterator = outputWord->begin(); _outWordIterator != outputWord->end(); _outWordIterator++)
    // {
        // std::cout << "Output module : " << (*_outWordIterator)->getName() << std::endl;
    // }

    ////////////////////////////////////////
    // Testing Anabaena Catenula model
    ////////////////////////////////////////

    std::cout << "Testing Anabaena Catenula model :" << std::endl;

    // Axiom
    // LSystemWord axiom("!(0.5)F(1,2,1)");
    LSystemWord axiom("!(W)F(BS,B,R)");

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

    std::cout << "\ntest completed" << std::endl;
    std::cin.get();
}
