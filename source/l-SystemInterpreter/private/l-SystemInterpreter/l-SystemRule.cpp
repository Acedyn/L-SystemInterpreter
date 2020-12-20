#include "l-SystemInterpreter/l-SystemRule.h"
#include "l-SystemInterpreter/l-SystemCondition.h"
#include "l-SystemInterpreter/l-SystemModule.h"
#include "l-SystemInterpreter/l-SystemWord.h"

////////////////////////////////////////
// Constructors / desctructors
////////////////////////////////////////
LSystemRule::LSystemRule(LSystemModule* _mainModule, LSystemWord* _derivativeWord, LSystemCondition* _mainCondition, float _probabilityFactor)
{
    mainModule = _mainModule;
    setDerivativeWord(_derivativeWord);
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

void LSystemRule::setDerivativeWord(LSystemWord* _derivativeWord)
{
    derivativeWord = _derivativeWord;
}
