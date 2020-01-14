#include "Engine.h"

int main()
{
	Engine* engine = new Engine();

	try
	{
		engine->Go();
	}
	catch (char* e)
	{
		throw "Could not start Engine";
	}
	return 0;
}
