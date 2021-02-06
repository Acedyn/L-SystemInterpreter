#include "l-SystemDraw/l-SystemReader.h"


LSystem::Reader::Reader(LSystemWord _word) :
	word(_word) 
{
	wordIterator = word.begin();
	turtle = Turtle();
}


void LSystem::Reader::parseWord()
{
	while (wordIterator != word.end())
	{
		interpretModule(*wordIterator);
		wordIterator++;
	}
}

void LSystem::Reader::interpretModule(LSystemConcreteModule& _module)
{
	switch (_module.getName())
	{
	case 'F':
		turtle.moveForward();
		break;

	case 'f':
		turtle.jumpForward();
		break;

	case '+':
		turtle.turnLeft();
		break;

	case '-':
		turtle.turnRight();
		break;

	case '&':
		turtle.pitchDown();
		break;

	case '^':
		turtle.pitchUp();
		break;

	case '\\':
		turtle.rollLeft();
		break;

	case '/':
		turtle.rollRight();
		break;

	case '|':
		turtle.turnAround();
		break;

	case '[':
		turtle.pushState();
		break;

	case ']':
		turtle.popState();
		break;

	default:
		break;
	}
}