#include "l-SystemInterpreterTest.h"
#include "l-SystemInterpreter/l-SystemModule.h"
#include "l-SystemInterpreter/l-SystemCondition.h"

#include <iostream>

int main()
{
    LSystemModule lSystemModuleRule('A', std::vector<char>{'x', 'y', 'z'});
    LSystemCondition lSystemCondition(std::string("2+54*3-29+8^3"));
    lSystemCondition.parseExpression(lSystemModuleRule);

    std::cout << "\ntest successfull" << std::endl;
    std::cin.get();
}
