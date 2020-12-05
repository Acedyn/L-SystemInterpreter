#include "l-SystemInterpreter/l-SystemCondition.h"

LSystemCondition::LSystemCondition(const char* _condition) :
    condition(_condition) {  }

bool LSystemCondition::matchModule()
{
    return true;
}

bool LSystemCondition::operator==(const LSystemCondition& _other) const
{
    if(condition == _other.condition)
    {
        return true;
    }
    return false;
}
