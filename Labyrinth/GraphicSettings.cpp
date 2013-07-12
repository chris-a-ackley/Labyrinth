#include "GraphicSettings.h"

// Constants
#define FILE_NAME "graphics.cfg"
#define FULL_SCREEN "FullScreen"
#define HEIGHT "Height"
#define WIDTH "Width"

GraphicSettings::GraphicSettings( void )
{
	config = Config( FILE_NAME );
}

// Reset Settings to Default
void GraphicSettings::reset( void )
{
	config.reset();
	config.setBool( FULL_SCREEN, false );
	config.setInt( HEIGHT, 600 );
	config.setInt( WIDTH, 900 );
}

void GraphicSettings::retrieve( void )
{
	if( !config.fileExists() )
	{
		reset();
	}
	else
	{
		config.retrieve();
	}
}

void GraphicSettings::save( void )
{
	config.save();
}

bool GraphicSettings::getFullScreen( void )
{
	return config.getBool( FULL_SCREEN );
}

unsigned _int16 GraphicSettings::getHeight( void )
{
	return config.getInt( HEIGHT );
}

unsigned _int16 GraphicSettings::getWidth( void )
{
	return config.getInt( WIDTH );
}

void GraphicSettings::setFullScreen( bool value )
{
	config.setBool( FULL_SCREEN, true );
}

void GraphicSettings::setHeight( unsigned _int16 value )
{
	config.setInt( HEIGHT, value );
}

void GraphicSettings::setWidth( unsigned _int16 value )
{
	config.setInt( WIDTH, value );
}