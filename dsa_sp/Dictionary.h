#include "DictionaryItem.h"
#include <iostream>
#include <algorithm>
constexpr auto BASESIZE = 52;

class Dictionary
{
public:
	Dictionary();
	~Dictionary();
	void AddCzechWord(std::string);
	void PrintTranslatedWords(std::string);
	void PrintDictionary();
	void AddTranslation(std::string, std::string);
	void RemoveTranslation(std::string);
	void PrintSortedDictionary();
	bool isWordInDictionary(std::string);
	friend std::ostream& operator<<(std::ostream& os, const Dictionary& dict);
	DictionaryItem** dictionary;
private:
	int size = BASESIZE;
	unsigned long Hash(std::string);
	void Resize();
	int GetPosition(std::string);
	DictionaryItem** GetSortedArray();
	void QuickSort(DictionaryItem**, int, int);
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

unsigned long Dictionary::Hash(std::string word) {
	return std::hash<std::string>{}(word);
}

int Dictionary::GetPosition(std::string key) {
	return Hash(key) % size;
}

void Dictionary::AddCzechWord(std::string key) {
	std::transform(key.begin(), key.end(), key.begin(), ::tolower);
	int position = GetPosition(key);
	if (dictionary[position] != nullptr) 
		while (dictionary[position] != nullptr)
			position++;

	dictionary[position] = new DictionaryItem(key);
	count++;

	if ((double)count / size >= 0.75)
		Resize();

}
bool Dictionary::isWordInDictionary(std::string key) {
	std::transform(key.begin(), key.end(), key.begin(), ::tolower);
	int position = GetPosition(key);
	while (dictionary[position] != nullptr && dictionary[position]->key != key)
		position++;
	return dictionary[position] != nullptr;
}

void Dictionary::PrintTranslatedWords(std::string key) {
	std::transform(key.begin(), key.end(), key.begin(), ::tolower);
	int position = GetPosition(key);
	while (dictionary[position]->key != key)
		position++;
	
	if (dictionary[position]->words != nullptr) {
		std::cout << "--------------------------" << std::endl;
		std::cout << *dictionary[position];
		std::cout << "--------------------------" << std::endl;
	}
	else
		std::cout << "No translation for word " << key << std::endl;
}

void Dictionary::AddTranslation(std::string key, std::string word) {
	std::transform(key.begin(), key.end(), key.begin(), ::tolower);
	std::transform(word.begin(), word.end(), word.begin(), ::tolower);
	int position = GetPosition(key);
	while (dictionary[position]->key != key)
		position++;
	dictionary[position]->AddWord(word);

}
void Dictionary::PrintDictionary() {
	std::cout << "--------------------------" << std::endl;
	std::cout << *this << std::endl;
	std::cout << "--------------------------" << std::endl;
	std::cout << "There is " << count << " elements in dictionary" << std::endl;
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

void Dictionary::RemoveTranslation(std::string key) {
	std::transform(key.begin(), key.end(), key.begin(), ::tolower);
	int position = GetPosition(key);
	while (dictionary[position]->key != key)
		position++;

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
			while (newDictionary[position] != nullptr)
			{
				position++;
			}
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
	QuickSort(arr, 0, count - 1);
	return arr;
}

void Dictionary::QuickSort(DictionaryItem** items, int left, int right) {

	int i, j;
	DictionaryItem* x;


	i = left;
	j = right;
	x = items[(left + right) / 2];

	do {
		while (items[i]->key < x->key && i < right) {
			i++;
		}
		while (items[j]->key > x->key && j > left) {
			j--;
		}
		if (i <= j) {
			std::swap(items[i], items[j]);
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