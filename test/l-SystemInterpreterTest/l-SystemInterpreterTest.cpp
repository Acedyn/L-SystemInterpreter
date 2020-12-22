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
    LSystemCondition lSystemCondition(std::string("2+54*3-29+8^3"));
    lSystemCondition.parseExpression(lSystemModuleRule);
    LSystemRule lSystemRule(lSystemModuleRule);
    lSystemRule.setDerivativeWord(new LSystemWord(std::string("P(5)F(3, 6)")));
    LSystemWord lSystemWord("F(5884, 5)A^+=P(4,4410),R");
    LSystem lSystem(&lSystemWord);
    lSystem.appendRule(&lSystemRule);
    lSystem.iterate();

    LSystemWord* outputWord = lSystem.getOutputWord();
    for(LSystemWord::Iterator _outWordIterator = outputWord->begin(); _outWordIterator != outputWord->end(); _outWordIterator++)
    {
        std::cout << "Output module : " << (*_outWordIterator)->getName() << std::endl;
    }

    std::cout << "\ntest completed" << std::endl;
    std::cin.get();
}
