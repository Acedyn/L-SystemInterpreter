#include "l-SystemInterpreterTest.h"
#include "l-SystemInterpreter/l-SystemModule.h"
#include "l-SystemInterpreter/l-SystemCondition.h"
#include "l-SystemInterpreter/l-SystemRule.h"
#include "l-SystemInterpreter/l-SystemWord.h"
#include "l-SystemInterpreter/l-System.h"

#include <iostream>

int main()
{
    LSystemModule lSystemModuleRule('A', std::vector<char>{'x', 'y', 'z'});
    LSystemCondition lSystemCondition(std::string("2+54*3-29+8^3"));
    lSystemCondition.parseExpression(lSystemModuleRule);
    LSystemRule lSystemRule(lSystemModuleRule);
    LSystemWord lSystemWord("F(5884, 5)A^+=P(4,4410),R");
    LSystem lSystem(&lSystemWord);

    std::vector<LSystemModule> wordModules = lSystemWord.getModules();
    for(LSystemModule wordModule : wordModules)
    {
        std::cout << wordModule.getName() << " ";
        std::vector<float> moduleParameters = wordModule.getParameterValues();
        for(float moduleParameter : moduleParameters)
        {
            std::cout << moduleParameter << " ";
        }
        std::cout << std::endl;
    }


    std::cout << "\ntest completed" << std::endl;
    std::cin.get();
}
