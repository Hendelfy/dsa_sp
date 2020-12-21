#pragma once
#include <cstring>
char* MakeACopy(char* source) {
	int size = strlen(source) + 1;
	char* copy = new char[size];
	copy[0] = toupper(source[0]);
	for (int i = 1; i < size; i++)
	{
		copy[i] = tolower(source[i]);
	}

	return copy;
}