#include <system_error>
#include "Menu.h"
int main(int argv, char* argc[])
{
	auto menu = new Menu();
	if (argv == 2) {
		menu->ReadFile(argc[1]);
	}
	system("pause");
	menu->MenuSelection();

	delete menu;
	_CrtDumpMemoryLeaks();//Test memory leaks
}
