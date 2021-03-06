#include "l-SystemBase/l-System.h"
#include "l-SystemBase/l-SystemWord.h"
#include "l-SystemBase/l-SystemRule.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

////////////////////////////////////////
// Constructors / desctructors
////////////////////////////////////////
LSystem::LSystem(LSystemWord _axiom) : 
    axiom(_axiom) 
{  
    outputWord = new LSystemWord(_axiom);
}

LSystem::LSystem(LSystemWord _axiom, std::vector<LSystemRule*> _rules) : 
    axiom(_axiom),
    rules(_rules)
{  
    // Initialise the outputWord
    outputWord = new LSystemWord(_axiom);
}


////////////////////////////////////////
// Setters / getters
////////////////////////////////////////
void LSystem::appendRule(LSystemRule* _rule)
{
    // Add the rule to the list of rule
    rules.emplace_back(_rule);
}


////////////////////////////////////////
// Public functions
////////////////////////////////////////
void LSystem::iterate()
{
    // Increment the seed
    seed++;

    // Initialise an empty word that will replace the current outputWord
    LSystemWord* _newWord = new LSystemWord();

    int _iteration = 0;
    // Loop over all the modules of the current outputWord
    for(auto _wordIterator = outputWord->begin(); _wordIterator != outputWord->end(); _wordIterator++)
    {
        // Used to store the result of the comparison of the modules
        bool _match = false;

        // Store the previous module
        LSystemConcreteModule* _previousModule = _wordIterator == outputWord->begin() ? nullptr : &(*_wordIterator);
        // Store the next module
        LSystemConcreteModule* _nextModule = _wordIterator == outputWord->end()-- ? nullptr : &(*_wordIterator);
        
        // Create seed for time
        srand(static_cast<int>(time(NULL)) + _iteration + seed);
        // Compute random value in a range of 0 to 999
        float _random = static_cast<float>(rand() % 1000) / 1000;

        // Initialise the _ruleProbability for shocastic rules
        float _ruleProbability = 0.0f;
        // Compute probabilitySum
        float _probabilitySum = 0.0f;
        for(LSystemRule* _probabilityComputer : rules)
        {
            if(_probabilityComputer->getMainModule() == (*_wordIterator))
            {
                _probabilitySum += _probabilityComputer->getProbabilityFactor();
            }
        }

        // Loop over all the rules to test if it matches the current module
        for(LSystemRule* _rule : rules)
        {
            // Link the current module to the rule
            _rule->linkModules(&(*_wordIterator), _previousModule, _nextModule);

            // If the rule has a probabilityFactor
            if(_rule->getProbabilityFactor() >= 0 && _rule->getMainModule() == (*_wordIterator))
            {
                // Compute the ruleProbability
                _ruleProbability += _rule->getProbabilityFactor() / _probabilitySum;
            }

            // If the current module doesnt matches the rule's main module
            if((*_wordIterator) != _rule->getMainModule()) { continue; }
            // If the previous module matches the left condition module of the rule
            else if(_previousModule != nullptr && *_previousModule == _rule->getLeftConditionModule()) { continue; }
            // If the next module matches the right condition module of the rule
            else if(_nextModule != nullptr && *_nextModule == _rule->getRightConditionModule()) { continue; }
            // If there is a condition expression and its result is not true
            else if(_rule->getMainCondition().getExpression() != "" &&
                    !_rule->getMainCondition().parseBinaryExpression()) { continue; }
            // If the probabilityFactor is higher than the _ruleProbability
            else if(_rule->getProbabilityFactor() > 0.0f && _random > _ruleProbability) { continue; }
            // If the rule matches but derive to nothing
            else if(_rule->getDerivativeWord() == LSystemWord())
            {
                // Store the result
                _match = true;
                // Stop iterating over the rules for this module
                break;
            }
            // If the rule matches the current rule
            else
            {
                //Store the result
                _match = true;
                // Update the derivative word to get the right module parameters
                _rule->updateDerivativeWord();
                // Append the derivative word of the rule to the future outputWord
                _newWord->appendWord(_rule->getDerivativeWord());
                // Stop iterating over the rules for this module
                break;
            }
        }
        if(!_match)
        {
            _newWord->appendModule((*_wordIterator));
        }
        _iteration++;
    }
    outputWord = _newWord;
}
