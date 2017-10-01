#include <iostream>
#include "application.h"
#include "fileManipulator.h"

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