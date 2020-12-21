#include "DictionaryItem.h"
#include <iostream>
#include "StrHelpers.h"
constexpr auto BASESIZE = 1000;
class Dictionary
{
public:
	Dictionary();
	~Dictionary();
	void AddCzechWord(char*);
	void PrintTranslatedWords(char*);
	void PrintDictionary();
	void AddTranslation(char*, char*);
	void RemoveTranslation(char*);
	bool isKeyInDictionary(char*);
	friend std::ostream& operator<<(std::ostream& os, const Dictionary& dict);
	DictionaryItem** dictionary;
	int count;
private:
	int size = BASESIZE;
	unsigned long Hash(char*);
	void Resize();
	int GetPosition(char*);
};

Dictionary::Dictionary() : count(0) {
	dictionary = new DictionaryItem * [size];
	for (int i = 0; i < size; i++)
	{
		dictionary[i] = nullptr;
	}
}

Dictionary::~Dictionary() {
	for (int i = 0; i < size; i++)
	{
		if (dictionary[i] != nullptr) {
			delete dictionary[i];
			dictionary[i] = nullptr;
		}
	}
	delete[] dictionary;
	dictionary = nullptr;
}

unsigned long Dictionary::Hash(char* word) {

	unsigned long hash = 5428;
	int c;
	while (c = *word++)
	{
		c = tolower(c);
		hash = ((hash << 5) + hash) + c;
	}
	return hash;
}

int Dictionary::GetPosition(char* key) {
	return Hash(key) % size;
}

void Dictionary::AddCzechWord(char* key) {
	int position = GetPosition(key);
	char* czechWord = MakeACopy(key);
	dictionary[position] = new DictionaryItem(czechWord);
	count++;
	if ((double)count / size >= 0.75)
		Resize();
}
bool Dictionary::isKeyInDictionary(char* key) {
	int position = GetPosition(key);
	return dictionary[position] != nullptr;
}

void Dictionary::PrintTranslatedWords(char* key) {
	auto words = dictionary[GetPosition(key)];
	if (words != nullptr)
		std::cout << *words;
	else
		std::cout << "No translation for word " << key << std::endl;
}

void Dictionary::AddTranslation(char* key, char* word) {
	int position = GetPosition(key);
	dictionary[position]->AddWord(MakeACopy(word));

}
void Dictionary::PrintDictionary() {
	std::cout << *this << std::endl << "There is " << count << " elements in dictionary" << std::endl;
};

void Dictionary::RemoveTranslation(char* key) {
	int position = GetPosition(key);
	delete dictionary[position];
	dictionary[position] = nullptr;
	count--;
}

void Dictionary::Resize() {
	size = size * 2;
	auto newDictionary = new DictionaryItem * [size];
	int position;
	for (int i = 0; i < size; i++)
	{
		newDictionary[i] = nullptr;
	}
	for (int i = 0; i < size / 2; i++)
	{
		if (dictionary[i] != nullptr) {
			position = GetPosition(dictionary[i]->key);
			newDictionary[position] = dictionary[i];
		}
		else {
			delete dictionary[i];
		}
		dictionary[i] = nullptr;
	}

	delete[] dictionary;
	dictionary = newDictionary;
}


std::ostream& operator<<(std::ostream& os, const Dictionary& dict)
{
	for (int i = 0, k = 0; i < dict.size && k < dict.count; i++)
	{
		if (dict.dictionary[i] != nullptr) {
			os << *dict.dictionary[i];
			k++;
		}
	}
	return os;
}
