#include "l-SystemInterpreter/l-System.h"
#include "l-SystemInterpreter/l-SystemWord.h"
#include "l-SystemInterpreter/l-SystemRule.h"

#include <iostream>

////////////////////////////////////////
// Constructors / desctructors
////////////////////////////////////////
LSystem::LSystem(LSystemWord* _axiom) : 
    axiom(_axiom) 
{  
    outputWord = new LSystemWord(*_axiom);
}

LSystem::LSystem(LSystemWord* _axiom, std::vector<LSystemRule*> _rules) : 
    axiom(_axiom),
    rules(_rules) 
{  
    outputWord = new LSystemWord(*_axiom);
}


////////////////////////////////////////
// Setters / getters
////////////////////////////////////////
void LSystem::appendRule(LSystemRule* _rule)
{
    rules.emplace_back(_rule);
}


////////////////////////////////////////
// Public functions
////////////////////////////////////////
void LSystem::iterate()
{
    // Initialise an empty word that will replace the current outputWord
    LSystemWord* _newWord = new LSystemWord();
    // Loop over all the modules of the current outputWord
    for(LSystemWord::Iterator _wordIterator = outputWord->begin(); _wordIterator != outputWord->end(); _wordIterator++)
    {
        // Used to store the result of the comparison of the modules
        bool _match = false;

        // Store the previous module
        LSystemModule* _previousModule = _wordIterator-- == outputWord->begin() ? nullptr : *_wordIterator;
        // Replace the iterator
        _wordIterator++;
        // Store the next module
        LSystemModule* _nextModule = ++_wordIterator == outputWord->end() ? nullptr : *(_wordIterator);
        // Replace the iterator
        _wordIterator--;

        // Loop over all the rules to test if it matches the current module
        for(LSystemRule* rule : rules)
        {
            // If the current module doesnt matches the rule's main module
            if(*(*_wordIterator) != rule->getMainModule())
            {
                // Stop testing and go to the next rule
                continue;
            }
            // If the previous module matches the left condition module of the rule
            else if(_previousModule != nullptr && *_previousModule == rule->getLeftConditionModule())
            {
                // Stop testing and go to the next rule
                continue;
            }
            // If the next module matches the right condition module of the rule
            else if(_nextModule != nullptr && *_nextModule == rule->getRightConditionModule())
            {
                // Stop testing and go to the next rule
                continue;
            }
            // If the rule matches but derive to nothing
            else if(rule->getDerivativeWord() == nullptr)
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
                // Append the derivative word of the rule to the future outputWord
                _newWord->appendWord(*(rule->getDerivativeWord()));
                // Stop iterating over the rules for this module
                break;
            }
        }
        if(!_match)
        {
            _newWord->appendModule(*(*_wordIterator));
        }
    }
    outputWord = _newWord;
}
