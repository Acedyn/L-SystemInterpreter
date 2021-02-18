#include "l-SystemBase/l-SystemRule.h"
#include "l-SystemBase/l-SystemWord.h"

////////////////////////////////////////
// Constructors / desctructors
////////////////////////////////////////
LSystemRule::LSystemRule(
        LSystemAbstractModule _mainModule, 
        LSystemWord _derivativeWord, 
        LSystemExpression _mainCondition, 
        LSystemParameters* _globalParameters,
        float _probabilityFactor) :
    mainModule(_mainModule),
    derivativeWord(_derivativeWord),
    leftConditionModule(LSystemAbstractModule()),
    rightConditionModule(LSystemAbstractModule()),
    mainCondition(_mainCondition),
    probalitityFactor(_probabilityFactor) 
{
    setGlobalParameters(_globalParameters);
    derivativeWord.setModuleParameters({ &mainModule, &leftConditionModule, &rightConditionModule });
}


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
    if(_rule.getMainCondition().getExpression() != "")
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
    // If there is a probability factor
    if(_rule.getProbabilityFactor() > 0.0f)
    {
        stream << " : " << _rule.getProbabilityFactor();
    }

    return stream;
}


////////////////////////////////////////
// Main module
////////////////////////////////////////
void LSystemRule::setMainModule(LSystemAbstractModule _mainModule)
{
    mainModule = _mainModule;
}
void LSystemRule::linkMainModule(LSystemConcreteModule* _mainModuleLink)
{
    if (_mainModuleLink == nullptr) { return; }
    mainModule.setLinkedModule(_mainModuleLink);
    _mainModuleLink->setLinkedModule(&mainModule);
}

////////////////////////////////////////
// Derivative word
////////////////////////////////////////
void LSystemRule::setDerivativeWord(LSystemWord _derivativeWord)
{
    derivativeWord = _derivativeWord;
}

void LSystemRule::updateDerivativeWord()
{
    derivativeWord.reParseWord();
}

////////////////////////////////////////
// Main condition
////////////////////////////////////////
void LSystemRule::setMainCondition(LSystemExpression _mainCondition, LSystemParameters* _globalParameters)
{
    mainCondition = _mainCondition;
    setGlobalParameters(_globalParameters);
}

////////////////////////////////////////
// Condition modules
////////////////////////////////////////
void LSystemRule::setLeftConditionModule(LSystemAbstractModule _leftConditionModule)
{
    leftConditionModule = _leftConditionModule;
}

void LSystemRule::linkLeftModule(LSystemConcreteModule* _leftModuleLink)
{
    if (_leftModuleLink == nullptr) { return; }
    leftConditionModule.setLinkedModule(_leftModuleLink);
    _leftModuleLink->setLinkedModule(&leftConditionModule);
}

void LSystemRule::setRightConditionModule(LSystemAbstractModule _rightConditionModule)
{
    rightConditionModule = _rightConditionModule;
}

void LSystemRule::linkRightModule(LSystemConcreteModule* _rightModuleLink)
{
    if (_rightModuleLink == nullptr) { return; }
    rightConditionModule.setLinkedModule(_rightModuleLink);
    _rightModuleLink->setLinkedModule(&rightConditionModule);
}

////////////////////////////////////////
// Probability factor
////////////////////////////////////////
void LSystemRule::setProbabilityFactor(float _probabilityFactor)
{
    probalitityFactor = _probabilityFactor;
}

////////////////////////////////////////
// Global parameters
////////////////////////////////////////
void LSystemRule::setGlobalParameters(LSystemParameters* _globalParameters)
{
    mainCondition.setGlobalParameters(_globalParameters);
    mainCondition.setModuleParameters({ &mainModule, &leftConditionModule, &rightConditionModule });
}

LSystemParameters LSystemRule::getModuleParameters() const
{
    LSystemParameters _localParameters;
    _localParameters.append(mainModule.getParameters());
    _localParameters.append(leftConditionModule.getParameters());
    _localParameters.append(rightConditionModule.getParameters());

    return _localParameters;
}

////////////////////////////////////////
// Linked modules
////////////////////////////////////////
void LSystemRule::linkModules(
            LSystemConcreteModule* _mainModuleLink, 
            LSystemConcreteModule* _leftModuleLink, 
            LSystemConcreteModule* _rightModuleLink)
{
    linkMainModule(_mainModuleLink);
    linkLeftModule(_leftModuleLink);
    linkRightModule(_rightModuleLink);
}
