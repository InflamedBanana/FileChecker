#include <iostream>
#include "application.h"
//#include "fileManipulator.h"
//#include "JsonParser.h"
//#include <rapidjson\document.h>
#include "settings.h"

using namespace std;

int main()
{
	if ( !Application::Start() )
	{
		std::cout << "Start Application Failed...";
		system("PAUSE");
		return -1;
	}

	return 0;
}