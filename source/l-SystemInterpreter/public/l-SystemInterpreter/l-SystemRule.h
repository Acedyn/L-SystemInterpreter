# pragma once
#include "l-SystemInterpreter/l-SystemModule.h"
#include "l-SystemInterpreter/l-SystemExpression.h"

class LSystemRule
{
public:
    // Constructors / desctructors
    LSystemRule(LSystemModule _mainModule, class LSystemWord* _derivativeWord = nullptr, LSystemExpression _mainCondition = LSystemExpression(), float _probabilityFactor = -1.0f);
    ~LSystemRule() { }

    // Setters / getters
    void setMainCondition(LSystemExpression _mainCondition);
    void setProbabilityFactor(float _probabilityFactor);
    void setLeftConditionModule(LSystemModule _leftConditionModule);
    void setRightConditionModule(LSystemModule _rightConditionModule);
    void setDerivativeWord(class LSystemWord* _derivativeWord);
    LSystemModule getMainModule() { return mainModule; }
    float getProbabilityFactor() { return probalitityFactor; }
    LSystemModule getLeftConditionModule() { return leftConditionModule; }
    LSystemModule getRightConditionModule() { return rightConditionModule; }
    LSystemWord* getDerivativeWord() { return derivativeWord; }
    
private:
    // Private variables
    LSystemModule mainModule;
    LSystemExpression mainCondition;
    LSystemModule leftConditionModule;
    LSystemModule rightConditionModule;
    class LSystemWord* derivativeWord = nullptr;
    float probalitityFactor = -1;
};
