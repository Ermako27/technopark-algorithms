#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>

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
	cout << "RESIZE\n";
	count_of_elements = 0;
	int old_size = size_of_table;
	size_of_table = size_of_table * 2;
	vector<elem_t> old_table = move(table);
	vector<elem_t> new_table(size_of_table);
	table = move(new_table);
	for (int i = 0; i < old_size; i++){
		if (old_table[i].is_deleted == false){
			insert(old_table[i].elem);
		}
	}
}


//////////////////////////////  ХЕШ-ФУНКЦИЯ //////////////////////////////////////

int Hash::h1( const string& word ){ // с конца строки
	int ln = word.length(); // берем длину строки
	int a = 127;
	int result = 0;
	for (int i = ln - 1; i >=0 ; --i){
		result = (result * a + (word[i] - '0')) % size_of_table;
	}

	return result;
}

int Hash::h2( const string& word ){ // с начала строки, необходимо чтобы h2 была нечетна, а size_of_table был степенью 2 -> будут взаимно простыми
	int a = 237;
	int result = 0;
	for (auto x : word)
		result = (result * a + (x - '0')) % size_of_table;
	if (result % 2 == 0)
		return result+1;
	return result;
}

int Hash::hash_func(const string& word, int i){ // необходимо чтобы h2 и size_of_table были взаимнопростыми
	int result = (h1(word) + i*h2( word )) % size_of_table;
	return result;
}



///////////////////////////// МЕТОДЫ /////////////////////////////////////////////

bool Hash::insert( const string& word ){
	double fill_coeff = (double)count_of_elements / (double)size_of_table;
	if (fill_coeff >= 0.75){ // если коэффициент заполнения больше 3/4 перехешируем
		resize();
	}

	if (search(word))
		return false;

	int position; 
	int hash1 = h1( word ); // находим позицию слова в массиве
	int hash2 = h2( word );
	for (int i = 0; i < size_of_table; i++){ // пробегаем по массиву
		position = (hash1 + i*hash2) % size_of_table;
		// if ( table[position].is_deleted == false && table[position].elem == word) // если слово не было удалено и слова совпадают
		// 	return false;

		if ( table[position].is_deleted == true ){  // если позиция пуста
			table[position].elem = word;
			table[position].is_deleted = false; // позиция занята
			count_of_elements += 1;
			return true;
		}
	}
}

bool Hash::remove( const string& word ){	
	int position; 
	int hash1 = h1( word ); // находим позицию слова в массиве
	int hash2 = h2( word );
	for (int i = 0; i < size_of_table; i++){ 
		position = (hash1 + i*hash2) % size_of_table;
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
	int position; 
	int hash1 = h1( word ); // находим позицию слова в массиве
	int hash2 = h2( word );

	for (int i = 0; i < size_of_table; i++){
		position = (hash1 + i*hash2) % size_of_table;
		if ( table[position].is_deleted == true) // если удален
			continue;

		if ( table[position].elem == word )
			return true; // нашли слово
	}
	return false;
}

int main() {
    unsigned int start_time; // начальное время
    // здесь должен быть фрагмент кода, время выполнения которого нужно измерить
    unsigned int end_time;  // конечное время
    unsigned int search_time;

    char c;
    string word;

    Hash tb(8);

    while (cin >> c >> word) {
        bool result;

        switch (c) {
        case '+':
        	// cout << "---------------------" << "\n";
        	// start_time = clock();
            result = tb.insert(word);
            // end_time = clock();
            // search_time = end_time - start_time;
            // cout << "in_time: " << search_time << "\n";
            break;
        case '-':
        	// cout << "---------------------" << "\n";
        	// start_time = clock();
            result = tb.remove(word);
            // end_time = clock();
            // search_time = end_time - start_time;
            // cout << "out_time: " << search_time << "\n";
            break;
        case '?':
        	// cout << "---------------------" << "\n";
        	// start_time = clock();
            result = tb.search(word);
            // end_time = clock();
            // search_time = end_time - start_time;
            // cout << "search_time: " << search_time << "\n";
        default:
           	result = false;
        }

        cout << ((result) ? "OK" : "FAIL") << "\n\n";
    }
    return 0;
}
