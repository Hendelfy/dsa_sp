#include <crtdbg.h>
#include "Menu.h"
int main(int argc, char* argv[])
{
	auto menu = new Menu();
	if (argc == 2) {//Load data from text file, which one defined by arguments
		menu->ReadFile(argv[1]);
		system("pause");
	}
	menu->MenuSelection();
	delete menu;
	_CrtDumpMemoryLeaks();//Test memory leaks
}
