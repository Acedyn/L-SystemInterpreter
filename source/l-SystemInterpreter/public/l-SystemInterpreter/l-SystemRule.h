# pragma once
#include "l-SystemInterpreter/l-SystemConcreteModule.h"
#include "l-SystemInterpreter/l-SystemExpression.h"

class LSystemRule
{
public:
    // Constructors / desctructors
    LSystemRule(LSystemConcreteModule _mainModule, class LSystemWord* _derivativeWord, LSystemExpression _mainCondition = LSystemExpression(), float _probabilityFactor = -1.0f);
    ~LSystemRule() { }

    // Setters / getters
    void setMainCondition(LSystemExpression _mainCondition);
    void setProbabilityFactor(float _probabilityFactor);
    void setLeftConditionModule(LSystemConcreteModule _leftConditionModule);
    void setRightConditionModule(LSystemConcreteModule _rightConditionModule);
    void setDerivativeWord(class LSystemWord* _derivativeWord);
    LSystemConcreteModule getMainModule() { return mainModule; }
    float getProbabilityFactor() { return probalitityFactor; }
    LSystemConcreteModule getLeftConditionModule() { return leftConditionModule; }
    LSystemConcreteModule getRightConditionModule() { return rightConditionModule; }
    LSystemWord* getDerivativeWord() { return derivativeWord; }
    
private:
    // Private variables
    LSystemConcreteModule mainModule;
    LSystemExpression mainCondition;
    LSystemConcreteModule leftConditionModule;
    LSystemConcreteModule rightConditionModule;
    class LSystemWord* derivativeWord = nullptr;
    float probalitityFactor = -1;
};
