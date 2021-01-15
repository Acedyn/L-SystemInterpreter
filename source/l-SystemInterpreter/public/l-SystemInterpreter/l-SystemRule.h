# pragma once
#include "l-SystemInterpreter/l-SystemAbstractModule.h"
#include "l-SystemInterpreter/l-SystemWord.h"
#include "l-SystemInterpreter/l-SystemExpression.h"

class LSystemRule
{
public:
    // Constructors / desctructors
    LSystemRule(
            LSystemAbstractModule _mainModule = LSystemAbstractModule(), 
            LSystemWord _derivativeWord = LSystemWord(), 
            LSystemExpression _mainCondition = LSystemExpression(), 
            float _probabilityFactor = -1.0f);
    ~LSystemRule() { }

    // Operators
    bool operator==(const LSystemRule& _other) const;
    bool operator!=(const LSystemRule& _other) const;
    friend std::ostream& operator<<(std::ostream& stream, const LSystemRule& _rule);

    // Main module
    void setMainModule(LSystemAbstractModule _mainModule);
    LSystemAbstractModule getMainModule() const { return mainModule; }

    // Derivative word
    void setDerivativeWord(class LSystemWord _derivativeWord);
    LSystemWord getDerivativeWord() const { return derivativeWord; }

    // Main condition
    void setMainCondition(LSystemExpression _mainCondition);
    LSystemExpression getMainCondition() const { return mainCondition; }

    // Condition modules
    void setLeftConditionModule(LSystemAbstractModule _leftConditionModule);
    LSystemAbstractModule getLeftConditionModule() const { return leftConditionModule; }
    void setRightConditionModule(LSystemAbstractModule _rightConditionModule);
    LSystemAbstractModule getRightConditionModule() const { return rightConditionModule; }

    // Derivative word
    void setProbabilityFactor(float _probabilityFactor);
    float getProbabilityFactor() { return probalitityFactor; }
    
private:
    // Private variables
    LSystemAbstractModule mainModule;
    LSystemWord derivativeWord;
    LSystemExpression mainCondition;
    LSystemAbstractModule leftConditionModule;
    LSystemAbstractModule rightConditionModule;
    float probalitityFactor = -1;
};
