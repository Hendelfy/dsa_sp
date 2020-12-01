#define _CRT_SECURE_NO_WARNINGS
#include "TranslatedNode.h"
#include <string>
class DictionaryItem
{
public:
	DictionaryItem(char*);
	~DictionaryItem();
//private:
	char* key;
	TranslatedNode* words;

};
DictionaryItem::DictionaryItem(char* word) : words(nullptr){
	strcpy(key, word);
	
}
DictionaryItem::~DictionaryItem(){
	delete[] key;
	TranslatedNode* next;
	while (words != nullptr)
	{
		next = words->next;
		delete words;
		words = next;
	}

}
