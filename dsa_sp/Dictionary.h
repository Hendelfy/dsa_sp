#include "DictionaryItem.h"
#include <iostream>
class Dictionary
{
public:
	Dictionary();
	~Dictionary();
private:
	DictionaryItem** dictionary;
	int size=1000;
	int count;
	unsigned long Hash(char*);
	void AddCzechWord(char*);
	void GetTranslatedWords(unsigned int);
	void AddTranslation(unsigned int, char*);
	void PrintAll();
	void Resize();
};

Dictionary::Dictionary() : count(0){
	dictionary = new DictionaryItem*[size];
}

Dictionary::~Dictionary() {
	delete[] dictionary;
}

unsigned long Dictionary::Hash(char * word){
	unsigned long hash = 5428;
	int c;
	while (c = *word++)
	{
		hash = ((hash << 5) + hash) + c;
	}
	return hash;
}

void Dictionary::AddCzechWord(char* word) {
	auto hash = Hash(word);
	auto item = new DictionaryItem(word);
	int position = hash % size;
	count++;
	
	dictionary[position] = item;

	if ((double)count / size > 0.75)
		Resize();
}

void Dictionary::GetTranslatedWords(unsigned int hash) {
	int position = hash % size;
	if (dictionary[position] != nullptr) {
		auto current = dictionary[position]->words;
		while (current != nullptr)
		{
			std::cout << current->word;
			current = current->next;
			if (current != nullptr)
				std::cout << ", ";
		}
		std::cout << '\n';
	}
}

void Dictionary::AddTranslation(unsigned int hash, char* word){
	int position = hash % size;
	if (dictionary[hash] != nullptr) {
		auto current = dictionary[hash]->words;
		while (current!=nullptr)
		{
			current = current->next;
		}
		current = new TranslatedNode(word);
	}
}

void Dictionary::PrintAll() {
	for (int i = 0, k=0; i < size && k<count ; i++)
	{
		if (dictionary[i] != nullptr) {
			std::cout << dictionary[i]->key << " - ";
			auto current = dictionary[i]->words;
			while (current!=nullptr)
			{
				std::cout << current->word;
				current = current->next;
				if (current != nullptr)
					std::cout << ", ";
			}
			std::cout << '\n';
			k++;

		}
	}
}

void Dictionary::Resize() {
	size = size * 2;
	auto newDictionary = new DictionaryItem * [size];
	int position;
	unsigned long hash;
	for (int i = 0, k=0; i < size && k<count; i++)
	{
		if (dictionary[i] != nullptr) {
			hash = Hash(dictionary[i]->key);
			position = hash % size;
			newDictionary[position] = dictionary[i];
			k++;
		}
		else {
			delete dictionary[i];
		}
	}
	dictionary = newDictionary;
}
