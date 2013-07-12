#include "Menu.h"

Menu::Menu( void )
{
	state = MAIN;
}

ProgramState Menu::loop( void )
{
	switch( state )
	{
	case MAIN:
		// Main Menu
	case OPTIONS:
		// Options Menu
	case CREDITS:
		// Credits Menu
	default:
		// Error
		break;
	}

	return MENU;
}