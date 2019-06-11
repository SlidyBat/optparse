#include "optparse.h"

#include <iostream>

int main( int argc, char** argv )
{
	OptParse optparse;
	
	// Can either add arg option (option that can come with an argument) or a
	// flag option (a simple switch thats either there or not, doesn't have
	// any arguments

	// --longname, or -l are accepted
	// If user doesn't pass an argument then "defaultvalue" is used
	optparse.AddArgOption( "longname", 'l', "defaultvalue" );
	
	optparse.AddFlagOption( "dump", 'd' )
		.AddFlagOption( "test", 't' )
		.AddFlagOption( "test2", 's' );

	// Processes arguments
	optparse.Process( argc, argv );

	// operator[] is overloaded to return nullptr when the option doesn't exist,
	// or pointer the argument value if it does exist
	if( optparse["longname"] )
	{
		std::cout << "Longname: " << optparse["longname"] << '\n';
	}

	// For flag options it simply returns an empty string ("") if they exist
	if( optparse["dump"] )
	{
		std::cout << "Dump\n";
	}
	if( optparse["test"] )
	{
		std::cout << "Test\n";
	}
	if( optparse["test2"] )
	{
		std::cout << "Test2\n";
	}

	// Gets all arguments that aren't a part of the options strings
	// e.g. if user passes `--opt optarg arg`, arg would be stored
	//      as a regular argument and can be read back
	if( optparse.GetArgC() )
	{
		std::cout << "Strays: ";
		for( size_t i = 0; i < optparse.GetArgC(); i++ )
		{
			std::cout << optparse.GetArg( i ) << ' ';
		}
		std::cout << '\n';
	}

	return 0;
}