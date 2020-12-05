#include "l-SystemInterpreter/l-SystemModule.h"
#include "l-SystemInterpreter/l-SystemCondition.h"

LSystemModule::LSystemModule(char _name, const char* _formalParameters) :
    name(_name),
    formalParameters(_formalParameters) {  }

bool LSystemModule::matchCondition(LSystemCondition _lSystemCondition)
{
    return true;
}

bool LSystemModule::operator==(const LSystemModule& _other) const
{
    if(name == _other.name && formalParameters == _other.formalParameters)
    {
        return true;
    }
    return false;
}
