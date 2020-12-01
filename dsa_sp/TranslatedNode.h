class TranslatedNode
{
public:
	~TranslatedNode();
	char* word;
	TranslatedNode* next;
};

TranslatedNode::~TranslatedNode() {
	delete[] word;
}