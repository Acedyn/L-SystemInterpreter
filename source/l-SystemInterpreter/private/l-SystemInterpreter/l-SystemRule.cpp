#include "l-SystemInterpreter/l-SystemRule.h"
#include "l-SystemInterpreter/l-SystemWord.h"

////////////////////////////////////////
// Constructors / desctructors
////////////////////////////////////////
LSystemRule::LSystemRule(LSystemAbstractModule _mainModule, LSystemWord _derivativeWord, LSystemExpression _mainCondition, float _probabilityFactor) :
    mainModule(_mainModule),
    derivativeWord(_derivativeWord),
    leftConditionModule(LSystemAbstractModule()),
    rightConditionModule(LSystemAbstractModule()),
    mainCondition(_mainCondition),
    probalitityFactor(_probabilityFactor) { }


////////////////////////////////////////
// Operators
////////////////////////////////////////
bool LSystemRule::operator==(const LSystemRule& _other) const
{
    if(mainModule != _other.getMainModule()) { return false; }
    if(derivativeWord != _other.getDerivativeWord()) { return false; }
    if(mainCondition != _other.getMainCondition()) { return false; }
    if(leftConditionModule != _other.getLeftConditionModule()) { return false; }
    if(rightConditionModule != _other.getRightConditionModule()) { return false; }

    return true;
}

bool LSystemRule::operator!=(const LSystemRule& _other) const
{
    if(mainModule != _other.getMainModule()) { return true; }
    if(derivativeWord != _other.getDerivativeWord()) { return true; }
    if(mainCondition != _other.getMainCondition()) { return true; }
    if(leftConditionModule != _other.getLeftConditionModule()) { return true; }
    if(rightConditionModule != _other.getRightConditionModule()) { return true; }

    return false;
}

std::ostream& operator<<(std::ostream& stream, const LSystemRule& _rule)
{
    // If there is a left condition module, print it
    if(_rule.getLeftConditionModule() != LSystemAbstractModule())
    {
        stream << _rule.getLeftConditionModule() << " < ";
    }
    // If there is a main module print it
    if(_rule.getMainModule() != LSystemAbstractModule()) 
    {
        stream << _rule.getMainModule();
    }
    else
    {
        stream << "none";
    }
    // If there is a main condition print it
    if(_rule.getMainCondition() != LSystemExpression())
    {
        stream << " : " << _rule.getMainCondition().getExpression();
    }
    // If there is a right condition module print it
    if(_rule.getRightConditionModule() != LSystemAbstractModule())
    {
        stream << " > " << _rule.getRightConditionModule();
    }
    // If there is a derivative word print it
    if(_rule.getDerivativeWord() != LSystemWord())
    {
        stream << " -> " << _rule.getDerivativeWord();
    }

    return stream;
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

void LSystemRule::setLeftConditionModule(LSystemAbstractModule _leftConditionModule)
{
    leftConditionModule = _leftConditionModule;
}

void LSystemRule::setRightConditionModule(LSystemAbstractModule _rightConditionModule)
{
    rightConditionModule = _rightConditionModule;
}

void LSystemRule::setDerivativeWord(LSystemWord _derivativeWord)
{
    derivativeWord = _derivativeWord;
}
