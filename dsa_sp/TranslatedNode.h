class TranslatedNode
{
public:
	TranslatedNode(char *);
	~TranslatedNode();
	char* word;
	TranslatedNode* next;
};
TranslatedNode::TranslatedNode(char *word) {
	this->word = word;
	next = nullptr;
}
TranslatedNode::~TranslatedNode() {
	delete[] word;
	word = nullptr;
}