#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Hash
{
public:
	explicit Hash( int size );

	// добавление true - элемент добавился
	bool insert( const string& word );

	// удаление true - элемент удалился
	bool remove( const string& word );

	// поиск true - элемент нашелся
	bool search( const string& word );

	void hash_print();

private:

	// перехеширование
	void resize();

	// структура одного элемента
	typedef struct 
	{
		string elem;
		bool is_deleted = true;
	} elem_t;

	// хеш-таблица
	vector<elem_t> table;

	// две хеш функции для двойного хеширования 
	int hash_func( const string& word, int i );
	int h1( const string& word );
	int h2( const string& word );

	int count_of_elements;
	int size_of_table; // всегда степень двойки

};



Hash::Hash( int size ) : size_of_table(size), table(size), count_of_elements(0)
{}

void Hash::hash_print(){
	for (int i = 0; i < size_of_table; i++){
		if (table[i].is_deleted == true)
			cout << "NULL |";
		else
			cout << table[i].elem << " | ";
	}
	cout << '\n';
}


void Hash::resize(){
	// hash_print();
	count_of_elements = 0;
	int old_size = size_of_table;
	size_of_table = size_of_table * 2;
	vector<elem_t> old_table = table;
	vector<elem_t> new_table(size_of_table);
	// hash_print();
	table = new_table;
	// hash_print();
	for (int i = 0; i < old_size; i++){
		if (old_table[i].is_deleted == false){
			insert(old_table[i].elem);
			// hash_print();
			// count_of_elements -= 1; // костыль чтобы перезаписанные эелменты не считались новыми
		}
	}
	// hash_print();
}


//////////////////////////////  ХЕШ-ФУНКИЦЯ //////////////////////////////////////

int Hash::h1( const string& word ){ // с конца строки
	int ln = word.length(); // берем длину строки
	int a = 127;
	int result = 0;
	for (int i = ln - 1; i >=0 ; --i){

		result = (result * a + (word[i] - '0')) % size_of_table;
	}

	return result;
}

int Hash::h2( const string& word ){ // с начала строки
	int a = 127;
	int result = 0;
	for (auto x : word)
		result = (result * a + (x - '0')) % size_of_table;
	if (result % 2 == 0)
		return result+1;
	// cout << "H2 " <<result << '\n';
	return result;
}

int Hash::hash_func(const string& word, int i){
	int result = (h1( word ) + i*h2( word )) % size_of_table;
	return result;
}



///////////////////////////// МЕТОДЫ /////////////////////////////////////////////

bool Hash::insert( const string& word ){

	if ( search(word) ){
		return false; // при попытке вставить повторяющийся элемент
	}

	double fill_coeff = (double)count_of_elements / (double)size_of_table;
	if (fill_coeff >= 0.75){ // если коэффициент заполнения больше 3/4 перехешируем
	
		resize();
	}


	for (int i = 0; i < size_of_table; i++){ // пробегаем по массиву
		int position = hash_func( word, i ); // находим позицию слова в массиве
		if ( table[position].is_deleted == true ){  // если позиция пуста
			table[position].elem = word;
			table[position].is_deleted = false; // позиция занята
			count_of_elements += 1;
			// hash_print();
			// cout << "count of elemnts: " << count_of_elements << '\n';

			return true;
		}
	}
	// hash_print();
}

bool Hash::remove( const string& word ){
	for (int i = 0; i < size_of_table; i++){ 
		int position = hash_func( word, i );

		if ( table[position].is_deleted == true) // если 
			return false;

		if ( table[position].elem == word ){
			table[position].is_deleted = true; // пометили элемент как удаленный
			count_of_elements -= 1;
			return true;
		}
	}
}


bool Hash::search( const string& word){
	for (int i = 0; i < size_of_table; i++){
		int position = hash_func( word, i );
		if ( table[position].is_deleted == true) // если удален
			continue;

		if ( table[position].elem == word )
			return true; // нашли слово
	}
	return false;
}

int main() {
    char c;
    string word;

    Hash tb(8);

    while (cin >> c >> word) {
        bool result;

        switch (c) {
        case '+':
            result = tb.insert(word);
            break;
        case '-':
            result = tb.remove(word);
            break;
        case '?':
            result = tb.search(word);
            break;
        default:
            result = false;
        }

        cout << ((result) ? "OK" : "FAIL") << "\n";
    }
    return 0;
}
