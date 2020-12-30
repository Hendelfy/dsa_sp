#pragma once
#include "Dictionary.h"
#include <conio.h>

#include <fstream>
class Menu
{
private:
	Dictionary* dictionary;
public:
	Menu();

	Menu(std::string);
	~Menu();
	void FindTranslation();
	void DeleteWord();
	void AddCzechWord();
	void AddTranslation();
	void PrintAll();
	void ReadFile(std::string);
	void WriteToFile(std::string);
	void MenuSelection();
	void SaveToFile();
	void LoadFromFile();
};

Menu::Menu() : dictionary(new Dictionary) {}

Menu::Menu(std::string fileName) : Menu()
{
	ReadFile(fileName);
}

Menu::~Menu() { delete dictionary; }

void Menu::FindTranslation() {
	
	std::string buf;
	std::cout << "Write word you want to see: ";
	std::cin >> buf;
	if (dictionary->isWordInDictionary(buf))
		dictionary->PrintTranslatedWords(buf);
	else
		std::cout << "No word \"" << buf << "\" in dictionary" << std::endl;
}

void Menu::DeleteWord() {
	std::string buf;
	std::cout << "Write word you want to delete: ";
	std::cin >> buf;
	if (dictionary->isWordInDictionary(buf)) {
		dictionary->RemoveTranslation(buf);
		std::cout << "Removed successfuly" << std::endl;
	}
	else
		std::cout << "No word \"" << buf << "\" in dictionary" << std::endl;
}

void Menu::AddCzechWord()
{
	std::string buf;
	std::cout << "Write word you want to add: ";
	std::cin >> buf;
	std::cout << "Word \"" << buf << "\"";
	if (dictionary->isWordInDictionary(buf))
		std::cout << " already in dictionary!" << std::endl;
	else {
		dictionary->AddCzechWord(buf);
		std::cout << " successfuly added" << std::endl;
	}
}

void Menu::AddTranslation()
{
	std::string buf;
	std::cout << "Write word you want to translate: ";
	std::cin >> buf;
	if (dictionary->isWordInDictionary(buf)) {
		std::string word;
		std::cout << "Write a translation for word \"" << buf << "\": ";
		std::cin >> word;
		dictionary->AddTranslation(buf, word);
		std::cout << "Successfuly added" << std::endl;
	}
	else {
		std::cout << "No word \"" << buf << "\" in dictionary" << std::endl;
		std::cout << "Try again" << std::endl;
	}
}

void Menu::PrintAll()
{
	dictionary->PrintSortedDictionary();
}

void Menu::ReadFile(std::string file)
{
	std::ifstream In(file);
	if (!In.is_open()) {
		std::cout << "File doesn't exist" << std::endl;
		return;
	}
	In.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::string buf ;
	std::string word;
	bool nextWord;
	while (In)
	{
		try
		{
			In >> buf;
			if (!dictionary->isWordInDictionary(buf))
				dictionary->AddCzechWord(buf);
			else {
				std::cout << buf<<" already was in dictionary\n";
				In.ignore(100, '\n');
				continue;
			}
			In.ignore(3, '-');
			do
			{
				nextWord = false;
				In >> word;
				for (int i = 0; i < 20; i++)
				{
					if (word[i] == ',') {
						word[i] = '\0';
						nextWord = true;
						break;
					}
					if (word[i] == '\0')
						break;
				}
				dictionary->AddTranslation(buf, word);
			} while (nextWord);


		}
		catch (const std::exception&)
		{
			if (In) {
				In.clear();
				In.ignore(64, '\n');
			}
		}
	}
	In.close();
}

void Menu::WriteToFile(std::string file) {
	std::ofstream Out(file);
	Out << *dictionary;
	Out.close();
}

void Menu::MenuSelection()
{
	char c = ' ';
	while (c != 'q' && c != 'Q')
	{
		system("CLS");
		std::cout << "1 - Add czech word\n2 - Add translation\n3 - Delete word from dictionary\n4 - Translate word\n5 - Show full dictionary\n6 - Save to file\n7 - Load from file\nQ - Exit\n\n";
		
		c = _getch();
		system("CLS");
		switch (c)
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
		case '6':
			SaveToFile();
			break;
		case '7':
			LoadFromFile();
			break;
		}
		system("pause");

	}

}

void Menu::SaveToFile()
{
	std::cout << "Write file name to save: ";
	std::string buf;
	std::cin >> buf;
	WriteToFile(buf);
	std::cin.clear();
}

void Menu::LoadFromFile()
{
	std::cout << "Write file name to load: ";
	std::string buf;
	std::cin >> buf;
	ReadFile(buf);
	std::cin.clear();
}
