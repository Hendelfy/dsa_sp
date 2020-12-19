#pragma once
#include "Dictionary.h"
#include <conio.h>
class Menu
{
private:
	Dictionary* dictionary;
public:
	Menu();

	Menu(char*);
	~Menu();
	void FindTranslation();
	void DeleteWord();
	void AddCzechWord();
	void AddTranslation();
	void PrintAll();
	void ReadFile(char*);
	void MenuSelection();
};

Menu::Menu() : dictionary(new Dictionary) {}

Menu::Menu(char* fileName) : Menu()
{
	ReadFile(fileName);
}

Menu::~Menu() { delete dictionary; }

void Menu::FindTranslation() {

	char* buf = new char[80];
	std::cout << "Write word you want to see: ";
	std::cin >> buf;
	if (dictionary->isKeyInDictionary(buf))
		dictionary->PrintTranslatedWords(buf);
	else
		std::cout << "No word \"" << buf << "\" in dictionary" << std::endl;
	delete[] buf;
}

void Menu::DeleteWord() {
	char* buf = new char[80];
	std::cout << "Write word you want to delete: ";
	std::cin >> buf;
	if (dictionary->isKeyInDictionary(buf)) {
		dictionary->RemoveTranslation(buf);
		std::cout<<"Removed successfuly"<<std::endl;
	}
	else
		std::cout << "No word \"" << buf << "\" in dictionary" << std::endl;
	delete[] buf;
}

void Menu::AddCzechWord()
{
	char* buf = new char[80];
	std::cout << "Write word you want to add: ";
	std::cin >> buf;
	std::cout << "Word \"" << buf << "\"";
	if (dictionary->isKeyInDictionary(buf))
		std::cout << " already in dictionary!" << std::endl;
	else {
		dictionary->AddCzechWord(buf);
		std::cout << " successfuly added" << std::endl;
	}
	delete[] buf;
}

void Menu::AddTranslation()
{
	char* buf = new char[80];
	std::cout << "Write word you want to translate: ";
	std::cin >> buf;
	if (dictionary->isKeyInDictionary(buf)) {
		char* word = new char[80];
		std::cout << "Write a translation for word \"" << buf << "\": ";
		std::cin >> word;
		dictionary->AddTranslation(buf, word);
		std::cout << "Successfuly added" << std::endl;
		delete[] word;
	}
	else {
		std::cout << "No word \"" << buf << "\" in dictionary" << std::endl;
		std::cout << "Try again" << std::endl;
	}
	delete[] buf;
}

void Menu::PrintAll()
{
	dictionary->PrintDictionary();
}

void Menu::ReadFile(char*)
{
}

void Menu::MenuSelection()
{
	char c = ' ';
	while (c != 'q' && c != 'Q')
	{
		system("CLS");
		std::cout << "1 - Add czech word\n2 - Add translation\n3 - Delete word from dictionary\n4 - Translate word\n5 - Show full dictionary\nQ - Exit\n\n";
		switch (c = _getch())
		{
		case '1':
			AddCzechWord();
			break;
		case '2':
			AddTranslation();
			break;
		case '3':
			DeleteWord();
			break;
		case '4':
			FindTranslation();
			break;
		case '5':
			PrintAll();
			break;
		}
		system("pause");

	}

}
