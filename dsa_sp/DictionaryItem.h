#include "TranslatedNode.h"
#include <sstream>
class DictionaryItem
{
public:
	DictionaryItem();
	DictionaryItem(std::string);
	~DictionaryItem();
//private:
	std::string key;
	TranslatedNode* words;
	void AddWord(std::string word);
	friend std::ostream& operator<<(std::ostream& os, const DictionaryItem& di);

};
DictionaryItem::DictionaryItem(std::string word) {
	key = word;
	words = nullptr;
	
}

DictionaryItem::DictionaryItem() {
	words = nullptr;

}
DictionaryItem::~DictionaryItem(){
	TranslatedNode* next;
	while (words != nullptr)
	{
		next = words->next;
		delete words;
		words = nullptr;
		words = next;
	}

}
void DictionaryItem::AddWord(std::string word)
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
