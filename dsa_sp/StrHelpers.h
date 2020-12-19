#pragma once
#include <cstring>
char* MakeACopy(char* source) {
	int size = strlen(source) + 1;
	char* copy = new char[size];
	strcpy_s(copy, size, source);
	return copy;
}