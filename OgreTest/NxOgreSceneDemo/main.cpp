#include <iostream>

#include "Application.h"

int main( int argc, const char* argv )
{
	try
	{
		Application app;

		app.initialise();
		app.setup();
		app.update();
	}
	catch ( std::exception& e )
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}