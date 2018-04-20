#include <stdio.h>
#include <string>
#include <vector>
#include <assert>

using namespace std;

class Hash
{
public:
	explicit Hash( int size );

	// добавление
	bool insert( const string& word );

	// удаление
	bool remove( const string& word );

	// поиск
	bool search( const string word );

private:

	// перехеширование
	void resize();

	// структура одного элемента
	typedef struct 
	{
		string word;
		size_t is_deleted = 0;
	} elem_t;

	// хеш-таблица
	vector<elem_t> table;

};

Hash::Hash( int size ) : table(size)
{}

