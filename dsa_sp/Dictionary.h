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
	void GetWords(unsigned int);
	void AddTranslation(unsigned int);
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
	auto key = new DictionaryItem(word);
	int position = hash % size;
	if (dictionary[position] == nullptr)
		dictionary[position] = key;
	else //TOOD collision
		;
}

void Dictionary::GetWords(unsigned int hash) {
	int position = hash % size;
	if (dictionary[position] != nullptr) {
		auto word = dictionary[position]->words;
		while (word != nullptr)
		{
			std::cout << word->word << '\t';
			word = word->next;
		}
		std::cout << '\n';
	}
}