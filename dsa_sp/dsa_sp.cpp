#include <system_error>
#include "Menu.h"
int main()
{
	auto menu = new Menu();
	menu->MenuSelection();

	delete menu;
	_CrtDumpMemoryLeaks();//Test memory leaks
}
