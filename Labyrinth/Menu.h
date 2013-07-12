#ifndef MENU_H
#define MENU_H

#include "MenuState.h"
#include "ProgramState.h"

class Menu
{
	MenuState state;
public:
	Menu( void );

	ProgramState loop( void );
};

#endif