#include "l-SystemInterpreter/l-SystemRule.h"
#include "l-SystemInterpreter/l-SystemCondition.h"
#include "l-SystemInterpreter/l-SystemModule.h"

////////////////////////////////////////
// Constructors / desctructors
////////////////////////////////////////
LSystemRule::LSystemRule(LSystemModule* _mainModule)
{
    mainModule = _mainModule;
}

LSystemRule::LSystemRule(LSystemModule* _mainModule, LSystemCondition* _mainCondition)
{
    mainModule = _mainModule;
    setMainCondition(_mainCondition);
}

LSystemRule::LSystemRule(LSystemModule* _mainModule, float _probabilityFactor)
{
    mainModule = _mainModule;
    setProbabilityFactor(_probabilityFactor);
}

LSystemRule::LSystemRule(LSystemModule* _mainModule, LSystemCondition* _mainCondition, float _probabilityFactor)
{
    mainModule = _mainModule;
    setMainCondition(_mainCondition);
    setProbabilityFactor(_probabilityFactor);
}


////////////////////////////////////////
// Setters / getters
////////////////////////////////////////
void LSystemRule::setMainCondition(LSystemCondition* _mainCondition)
{
    mainCondition = _mainCondition;
}

void LSystemRule::setProbabilityFactor(float _probabilityFactor)
{
    probalitityFactor = _probabilityFactor;
}

void LSystemRule::setLeftConditionModule(LSystemModule* _leftConditionModule)
{
    leftConditionModule = _leftConditionModule;
}

void LSystemRule::setRightConditionModule(LSystemModule* _rightConditionModule)
{
    rightConditionModule = _rightConditionModule;
}
