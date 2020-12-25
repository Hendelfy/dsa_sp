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
	void PrintSortedDictionary();
	bool isKeyInDictionary(char*);
	friend std::ostream& operator<<(std::ostream& os, const Dictionary& dict);
	DictionaryItem** dictionary;
private:
	int size = BASESIZE;
	unsigned long Hash(char*);
	void Resize();
	int GetPosition(char*);
	DictionaryItem** GetSortedArray();
	void QuickSort(DictionaryItem**, int,int);
	int count;
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

	for (int i = 0; word[i]!='\0'; i++)
	{
		word[i] = tolower(word[i]);
	}
	return std::hash<std::string>{}(word);
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
	if (words != nullptr) {
		std::cout << "--------------------------" << std::endl;
		std::cout << *words;
		std::cout << "--------------------------" << std::endl;
	}
	else
		std::cout << "No translation for word " << key << std::endl;
}

void Dictionary::AddTranslation(char* key, char* word) {
	int position = GetPosition(key);
	dictionary[position]->AddWord(MakeACopy(word));	

}
void Dictionary::PrintDictionary() {
	std::cout << "--------------------------" << std::endl;
	std::cout << *this << std::endl;
	std::cout << "--------------------------" << std::endl;
	std::cout<< "There is " << count << " elements in dictionary" << std::endl;
	std::cout << "--------------------------" << std::endl;
};

void Dictionary::PrintSortedDictionary() {
	std::cout << "--------------------------" << std::endl;
	auto arr = GetSortedArray();
	for (int i = 0; i < count; i++)
	{
		std::cout << *arr[i];
		arr[i] = nullptr;
	}
	delete arr;
	std::cout << "There is " << count << " elements in dictionary" << std::endl;
	std::cout << "--------------------------" << std::endl;
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

DictionaryItem** Dictionary::GetSortedArray() {
	auto arr = new DictionaryItem * [count] {};
	for (int i = 0, k = 0; i < size && k < count; i++)
	{
		if (dictionary[i] != nullptr) {
			arr[k++] = dictionary[i];
		}
	}
	QuickSort(arr, 0, count-1);
	return arr;
}

void Dictionary::QuickSort(DictionaryItem** items, int left, int right) {

	int i, j;
	DictionaryItem* x;


	i = left;
	j = right;
	x = items[(left + right) / 2];

	auto swap = [](DictionaryItem** items, int i, int j) {auto temp = items[i]; items[i] = items[j]; items[j] = temp; };

	do {
		while ((strcmp(items[i]->key, x->key) < 0) && (i < right)) {
			i++;
		}
		while ((strcmp(items[j]->key, x->key) > 0) && (j > left)) {
			j--;
		}
		if (i <= j) {
			swap(items, i, j);
			i++;
			j--;
		}
	} while (i <= j);

	if (left < j) {
		QuickSort(items, left, j);
	}
	if (i < right) {
		QuickSort(items, i, right);
	}
}