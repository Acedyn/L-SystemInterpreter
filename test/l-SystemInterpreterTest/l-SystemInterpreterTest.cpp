#include "l-SystemInterpreterTest.h"
#include "l-SystemInterpreter/l-SystemModule.h"
#include "l-SystemInterpreter/l-SystemCondition.h"

#include <iostream>

int main()
{
    LSystemModule lSystemModuleRule('A', std::vector<char>{'x', 'y', 'z'});
    LSystemCondition lSystemCondition(std::string("x<=y"));

    std::cout << "\ntest successfull" << std::endl;
    std::cin.get();
}
