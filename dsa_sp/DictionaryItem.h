#include "TranslatedNode.h"
#include <sstream>
class DictionaryItem
{
public:
	DictionaryItem(char*);
	~DictionaryItem();
//private:
	char* key;
	TranslatedNode* words;
	void AddWord(char* word);
	friend std::ostream& operator<<(std::ostream& os, const DictionaryItem& di);

};
DictionaryItem::DictionaryItem(char* word) {
	key = word;
	words = nullptr;
	
}
DictionaryItem::~DictionaryItem(){
	delete[] key;
	key = nullptr;
	TranslatedNode* next;
	while (words != nullptr)
	{
		next = words->next;
		delete words;
		words = nullptr;
		words = next;
	}

}
void DictionaryItem::AddWord(char* word)
{
	if(words == nullptr)
		words = new TranslatedNode(word);
	else {
		auto current = words;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		current->next = new TranslatedNode(word);
	}
}
std::ostream& operator<<(std::ostream& os, const DictionaryItem& di)
{
	os << di.key << " - ";
	auto current = di.words;
	while (current != nullptr)
	{
		os << current->word;
		current = current->next;
		if (current != nullptr)
			os << ", ";
	}
	os << '\n';
	return os;
}

