#include "l-SystemInterpreter/l-SystemCondition.h"
#include "l-SystemInterpreter/l-SystemModule.h"

////////////////////////////////////////
// Constructors / desctructors
////////////////////////////////////////
LSystemCondition::LSystemCondition(std::string _expression)
{
    setExpression(_expression);
}


////////////////////////////////////////
// Operators
////////////////////////////////////////
bool LSystemCondition::operator==(const LSystemCondition& _other) const
{
    if(expression == _other.getExpression())
    {
        return true;
    }
    return false;
}


////////////////////////////////////////
// Getters / setters
////////////////////////////////////////
void LSystemCondition::setExpression(std::string _expression)
{
    expression = _expression;
}


////////////////////////////////////////
// Public functions
////////////////////////////////////////
bool parseExpression(LSystemModule _module)
{
    return true;
}
