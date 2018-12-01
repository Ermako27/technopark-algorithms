
template<class T>
struct hashTableNode{
	T Key;
	hashTableNode* Next;

	hashTableNode() : Next(0) {}
	hashTableNode(const T& key, hashTableNode* next) : Key(key), Next(next) {}

};


int Hash(const string& data, int tableSize)
{
	int hash = 0;
	for(int i = 0; i < data.size(); i++)
	{
		hash = hash * 127 + data[i];
	}
	return hash;
}




template<class T>
class hashTable{
public:
	hashTable();
	~hashTable();

	bool has(const T& key);
	bool add(const T& key);
	bool delet(const T& key);

private:
	std::vector<hashTableNode*> table;
	int keysCount;
}


template<class T>
hashTable::hashTable(int size) : keysCount(0)
{
	assert(size > 0);
	table.resize(size, 0);
}

template<class T>
bool hashTable::has(const T& key)
{
	int hash = Hash(key, table.size())
	hashTable<T>* node = table[hash] // указатель начала списка
	while (node != 0 && node->Key != key)
		node = node->Next
	return node != 0;
}

template<class T>
bool hashTable::add(const T& key)
{
	if (has(key))
		return false;
	int hash = Hash(key);
	table[hash] = new hashTableNode(hash, table[hash]);
	
}