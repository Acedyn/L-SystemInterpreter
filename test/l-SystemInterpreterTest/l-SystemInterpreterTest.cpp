#include "l-SystemInterpreterTest.h"
#include "l-SystemInterpreter/l-SystemModule.h"

#include <iostream>

int main()
{
    LSystemModule lSystemModule('A', "xyz");
    std::cout << "Module : " << lSystemModule.name << " formalParameters : " << lSystemModule.formalParameters << std::endl;

    std::cout << "\ntest successfull" << std::endl;
    std::cin.get();
}
