#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

enum AccessType{
	READ,
	WRITE
};

class Config
{
	string fileName;
	map<string, string> properties;
public:
	Config( void );
	Config( string fileName );

	bool retrieve( void );
	bool save( void );
	bool fileExists( void );
	void reset( void );

	bool getBool( string key );
	int getInt( string key );
	string getString( string key );
	void setBool( string key, bool value );
	void setInt( string key, int value );
	void setString( string key, string value );
};

#endif