#ifndef GRAPHICSETTINGS_H
#define GRAPHICSETTINGS_H

#include <fstream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

#include "Config.h"

class GraphicSettings: public Config
{
	Config config;
	map<string, string> properties;
public:
	GraphicSettings( void );

	void reset( void );
	void retrieve( void );
	void save( void );

	bool getFullScreen();
	unsigned _int16 getHeight();
	unsigned _int16 getWidth();
	void setFullScreen( bool value );
	void setHeight( unsigned _int16 value );
	void setWidth( unsigned _int16 value );
};

#endif