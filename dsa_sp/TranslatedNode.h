#include <string>

class TranslatedNode
{
public:
	TranslatedNode(std::string);
	std::string word;
	TranslatedNode* next;
};
TranslatedNode::TranslatedNode(std::string word) {
	this->word = word;
	next = nullptr;
}