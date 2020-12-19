#include "l-SystemInterpreterTest.h"
#include "l-SystemInterpreter/l-SystemModule.h"
#include "l-SystemInterpreter/l-SystemCondition.h"
#include "l-SystemInterpreter/l-SystemRule.h"
#include "l-SystemInterpreter/l-SystemWord.h"

#include <iostream>

int main()
{
    LSystemModule lSystemModuleRule('A', std::vector<char>{'x', 'y', 'z'});
    LSystemCondition lSystemCondition(std::string("2+54*3-29+8^3"));
    lSystemCondition.parseExpression(lSystemModuleRule);
    LSystemRule lSystemRule(&lSystemModuleRule);
    LSystemWord lSystemWord("F(5884, 5)A^+=P(4,4410),R");

    std::cout << "\ntest successfull" << std::endl;
    std::cin.get();
}
