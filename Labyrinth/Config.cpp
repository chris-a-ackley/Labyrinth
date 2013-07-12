#include "Config.h"

Config::Config( void )
{
	fileName = "Config.cfg";
}

Config::Config( string fileName )
{
	this -> fileName = fileName;
}

// Save Settings to Config
bool Config::save( void )
{
	bool success = false;

	// Open the file for writing
	fstream file( fileName, ios::out | ios::trunc );

	if( file.is_open() )
	{	
		string key;
		string value;

		// Iterate through all properties in the map
		for( map<string, string>::iterator iter = properties.begin(); iter != properties.end(); iter++ )
		{		
			// Get the key/value pair
			key = iter -> first;
			value = iter -> second;

			// Write the property to file
			file << key + ":" + value + "\n";
		}

		success = true;
	}

	file.close();

	return success;
}

// Retrieve Settings from Config
bool Config::retrieve( void )
{
	bool success = false;

	fstream file( fileName, ios::in );

	if( file.is_open() )
	{		
		string line;
		string key;
		string value;

		while( file.good() )
		{
			line = "";
			getline( file, line, '\n' );

			if( line != "" )
			{
				istringstream lineS( line );

				getline( lineS, key, ':' );
				getline( lineS, value, ' ' );

				properties[key] = value;
			}
		}

		// Inform of success
		success = true;
	}

	file.close();

	return success;
}

bool Config::fileExists( void )
{
	fstream file( fileName.c_str() );
	return file.good();
}

void Config::reset( void )
{
	properties.clear();
}

bool Config::getBool( string key )
{
	return properties[key] != "0";
}

int Config::getInt( string key )
{
	return atoi( properties[key].c_str() );
}

string Config::getString( string key )
{
	return properties[key];
}

void Config::setBool( string key, bool value )
{
	if( value )
	{
		properties[key] = "1";
	} 
	else
	{
		properties[key] = "0";
	}
}

void Config::setInt( string key, int value )
{
	stringstream convertor;

	convertor << value;		
	properties[key] = convertor.str();
}

void Config::setString( string key, string value )
{
	properties[key] = value;
}