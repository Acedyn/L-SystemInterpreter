#include "l-SystemInterpreter/l-SystemRule.h"
#include "l-SystemInterpreter/l-SystemWord.h"

////////////////////////////////////////
// Constructors / desctructors
////////////////////////////////////////
LSystemRule::LSystemRule(LSystemConcreteModule _mainModule, LSystemWord* _derivativeWord, LSystemExpression _mainCondition, float _probabilityFactor) :
    mainModule(_mainModule),
    leftConditionModule(LSystemConcreteModule('\0')),
    rightConditionModule(LSystemConcreteModule('\0')),
    mainCondition(_mainCondition)
{
    setDerivativeWord(_derivativeWord);
    setProbabilityFactor(_probabilityFactor);
}


////////////////////////////////////////
// Setters / getters
////////////////////////////////////////
void LSystemRule::setMainCondition(LSystemExpression _mainCondition)
{
    mainCondition = _mainCondition;
}

void LSystemRule::setProbabilityFactor(float _probabilityFactor)
{
    probalitityFactor = _probabilityFactor;
}

void LSystemRule::setLeftConditionModule(LSystemConcreteModule _leftConditionModule)
{
    leftConditionModule = _leftConditionModule;
}

void LSystemRule::setRightConditionModule(LSystemConcreteModule _rightConditionModule)
{
    rightConditionModule = _rightConditionModule;
}

void LSystemRule::setDerivativeWord(LSystemWord* _derivativeWord)
{
    derivativeWord = _derivativeWord;
}
