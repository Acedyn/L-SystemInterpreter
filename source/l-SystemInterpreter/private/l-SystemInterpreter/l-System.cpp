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
    LSystemWord* _newWord = new LSystemWord();
    for(LSystemWord::Iterator _wordIterator = outputWord->begin(); _wordIterator != outputWord->end(); _wordIterator++)
    {
        for(LSystemRule* rule : rules)
        {
            if(*(*_wordIterator) != rule->getMainModule())
            {
                _newWord->appendModule(*(*_wordIterator));
                continue;
            }
            if(rule->getDerivativeWord() == nullptr)
            {
                continue;
            }
                _newWord->appendWord(*(rule->getDerivativeWord()));
                std::cout << "Module " << (*_wordIterator)->getName() << " match" << std::endl;
        }
    }
    outputWord = _newWord;
}
