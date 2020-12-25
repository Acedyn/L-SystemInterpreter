#include "l-SystemInterpreterTest.h"
#include "l-SystemInterpreter/l-SystemModule.h"
#include "l-SystemInterpreter/l-SystemCondition.h"
#include "l-SystemInterpreter/l-SystemRule.h"
#include "l-SystemInterpreter/l-SystemWord.h"
#include "l-SystemInterpreter/l-System.h"

#include <iostream>

int main()
{
    LSystemModule lSystemModuleRule('F', std::vector<char>{'x', 'y'});
    LSystemModule rule2MainModule('A');
    LSystemCondition lSystemCondition(std::string("2+54*3-29+8^3"));
    lSystemCondition.parseExpression(lSystemModuleRule);
    LSystemRule lSystemRule(lSystemModuleRule);
    lSystemRule.setProbabilityFactor(2.0f);
    LSystemRule rule2(lSystemModuleRule);
    LSystemRule rule3(rule2MainModule);
    rule2.setProbabilityFactor(6.0f);
    rule2.setDerivativeWord(new LSystemWord("AR^++"));
    rule3.setProbabilityFactor(6.0f);
    rule3.setDerivativeWord(new LSystemWord("D@&#"));
    lSystemRule.setDerivativeWord(new LSystemWord(std::string("F(3, 6)P(5)")));
    LSystemWord lSystemWord("F(5884, 5)A^+=P(4,4410),R");
    LSystem lSystem(&lSystemWord);
    lSystem.appendRule(&lSystemRule);
    lSystem.appendRule(&rule2);
    lSystem.appendRule(&rule3);
    lSystem.iterate();

    LSystemWord* outputWord = lSystem.getOutputWord();
    for(LSystemWord::Iterator _outWordIterator = outputWord->begin(); _outWordIterator != outputWord->end(); _outWordIterator++)
    {
        std::cout << "Output module : " << (*_outWordIterator)->getName() << std::endl;
    }
    std::cout << std::endl;

    // lSystem.iterate();
    outputWord = lSystem.getOutputWord();
    for(LSystemWord::Iterator _outWordIterator = outputWord->begin(); _outWordIterator != outputWord->end(); _outWordIterator++)
    {
        // std::cout << "Output module : " << (*_outWordIterator)->getName() << std::endl;
    }

    std::cout << "\ntest completed" << std::endl;
    std::cin.get();
}
