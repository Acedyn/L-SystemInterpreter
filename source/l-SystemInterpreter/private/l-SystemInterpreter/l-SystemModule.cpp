#include "L-SystemInterpreter/l-SystemModule.h"

LSystemModule::LSystemModule(char _name, std::vector<char> _formalParameters)
{
    name = _name;
    formalParameters = _formalParameters;
}

bool LSystemModule::testCondition()
{
    return true;
}

bool LSystemModule::testSideCondition(LSystemModule sideModule)
{
    return true;
}
