#include "ChangeBlockButton.h"
#include <LogManager.h>

ChangeBlockButton::ChangeBlockButton()
{
	setDefaultColor(df::RED);
	setHighlightColor(df::YELLOW);

	setViewString("Block");
}

ChangeBlockButton::~ChangeBlockButton()
{
}

void ChangeBlockButton::callback()
{

	LM.writeLog("ButtonClicked");

}
