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
		// bool filled = false; // аналог NIL если 0 то позиция пуста, если 1 то заполнена
	} elem_t;

	// хеш-таблица
	vector<elem_t> table;

	// две хеш функции для двойного хеширования 
	int hash_func( const string& word, int i );
	int h1( const string& word );
	int h2( const string& word );

	double count_of_elements;
	double size_of_table; // всегда степень двойки

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
}

// void Hash::resize(){
// 	int old_size = size_of_table;
// 	size_of_table = size_of_table * 2;
// 	vector<elem_t> old_table = move(table);
	
// 	vector<elem_t> table(size_of_table);
// 	for (int i = 0; i < old_size; i++){
// 		if (old_table[i].is_deleted != true)
// 			insert( old_table[i].elem );
// 	}

// }

// void Hash::resize(){
// 	int old_size = size_of_table;
// 	size_of_table = size_of_table * 2;
// 	vector<elem_t> old_table = table;
// 	vector<elem_t> new_table(size_of_table);
// 	table = new_table;
// 	for (int i = 0; i < old_size; i++){
// 		if (table[i].is_deleted != true){
// 			for (int j = 0; j < size_of_table; j++){ // пробегаем по массиву
// 				int position = hash_func( table[i].elem, j ); // находим позицию слова в массиве
// 				if ( new_table[position].is_deleted == true ){  // если позиция пуста
// 					new_table[position].elem = table[i].elem;
// 					new_table[position].is_deleted = false; // позиция занята
// 					continue;
// 				}
// 			}
// 		}
// 	}
// 	table = new_table;
// }

void Hash::resize(){
	int old_size = size_of_table;
	size_of_table = size_of_table * 2;
	vector<elem_t> old_table = table;
	vector<elem_t> new_table(size_of_table);
	table = new_table;
	for (int i = 0; i < old_size; i++){
		if (old_table[i].is_deleted != true){
			insert(old_table[i].elem);
			count_of_elements -= 1; // костыль чтобы перезаписанные эелменты не считались новыми
		}
	}
}















// 	int previus_size = size_of_table;
// 	vector<elem_t> previus_table = table;
// 	size_of_table = size_of_table * 2;
// 	// vector<elem_t> new_table(size_of_table)
// 	table(size_of_table);
// 	for (int i = 0; i < previus_size; i++){ // проходим по элементам старой таблицы
// 		if ( previus_table[i].is_deleted != true ){ // если не пустая позиция
// 			insert( previus_table[i].elem );
// 		}
// 	}
	
// }

// void Hash::resize

//////////////////////////////  ХЕШ-ФУНКИЦЯ //////////////////////////////////////

int Hash::h1( const string& word ){ // с конца строки
	// cout << 5 << '\n';
	int ln = word.length(); // берем длину строки
	// cout << "LEN "<< ln << '\n';
	// cout << 6 << '\n'; 
	int a = 127;
	// cout << 7 << '\n';
	int result = 0;
	// cout << 8 << '\n';
	for (int i = ln - 1; i >=0 ; --i){
		// cout << word[i] << '\n';
		// cout << 9 << '\n';
		// cout << "LETTER " << (word[i] - '0') << '\n';
		// cout << "SIZE " << size_of_table << '\n';
		result = (result * a + (word[i] - '0')) % (int)size_of_table;
		// cout << 10 << '\n';
	}
	// cout << "LETTER " << (word[i] - '0') << '\n'
	// cout << "RESULT 1 " << result << '\n';
	return result;
}

int Hash::h2( const string& word ){ // с начала строки
	int a = 127;
	int result = 0;
	for (auto x : word)
		result = (result * a + (x - '0')) % (int)size_of_table;
	// cout << "RESULT 2 " << result << '\n';
	return result;
}

int Hash::hash_func(const string& word, int i){
	int result = (h1(word) + i*h2( word )) % (int)size_of_table;
	// cout << "RESULT 3 " << result << '\n';
	return result;
}



///////////////////////////// МЕТОДЫ /////////////////////////////////////////////

bool Hash::insert( const string& word ){

	cout << 1 << '\n';
	if ( search(word) )
	{
		cout << "!!!!!!!!!1" << '\n';
		return false; // при попытке вставить повторяющийся элемент
	}
	cout << 3 << '\n';

	// cout << "COUNT " << count_of_elements <<'\n';
	// cout << "SIZEOF " << size_of_table <<'\n';
	// cout << "COUNT " << count_of_elements <<'\n';
	// cout << "SIZEOF " << size_of_table <<'\n';

	if ((double)(count_of_elements/size_of_table) >= 0.75) // если коэффициент заполнения больше 3/4 перехешируем
	{
		cout << "COUNT " << count_of_elements <<'\n';
		cout << "SIZEOF " << size_of_table <<'\n';
		cout << 4 << '\n';
		resize();
		cout << 5 << '\n';
		// cout << "COUNT " << count_of_elements <<'\n';
		// cout << "SIZEOF " << size_of_table <<'\n';
	}
		// resize();
		// cout << "&&&&&&&&&&&&&&&&7"<< '\n';

	for (int i = 0; i < size_of_table; i++){ // пробегаем по массиву
		cout << 4 << '\n';
		int position = hash_func( word, i ); // находим позицию слова в массиве
		cout << 5 << '\n';
		cout << "position" << position << '\n'; 
		if ( table[position].is_deleted == true ){  // если позиция пуста
			table[position].elem = word;
			cout << "word: " << table[position].elem << '\n';
			table[position].is_deleted = false; // позиция занята
			count_of_elements += 1;
			cout << "elements: " << count_of_elements << '\n';
			return true;
		}
	}
}

bool Hash::remove( const string& word ){
	// if (search(word) == false) // если удаляемого слова нет в таблице
	// 	return false;

	for (int i = 0; i < size_of_table; i++){ 
		int position = hash_func( word, i );

		if ( table[position].is_deleted == true) // если 
			return false;

		if ( table[position].elem == word ){
			// delete table[position].elem; // освободили память 
			table[position].is_deleted = true; // пометили элемент как удаленный
			count_of_elements -= 1;
			return true;
		}
	}
}


bool Hash::search( const string& word){
	// cout << 1 << '\n';
	for (int i = 0; i < size_of_table; i++){
		// cout << 2 << '\n';
		int position = hash_func( word, i );
		// cout << 3 << '\n';
		if ( table[position].is_deleted == true) // если удален
			continue;

		if ( table[position].elem == word )
			return true; // нашли слово
	}
	return false;
}

int main()
{

	Hash tb(8);
	string word1 = "google";
	string word2 = "mic";
	string word3 = "python";
	string word4 = "php";
	string word5 = "nginx";
	string word6 = "django";
	string word7 = "js";
	string word8 = "rust";

	tb.hash_print();
	tb.insert(word1);
	tb.hash_print();
	tb.insert(word2);
	tb.hash_print();
	tb.insert(word3);
	tb.hash_print();
	tb.insert(word4);
	tb.hash_print();
	tb.insert(word5);
	tb.hash_print();
	tb.insert(word6);
	tb.hash_print();
	tb.insert(word7);
	tb.hash_print();
	tb.insert(word8);
	tb.hash_print();



	// tb.insert(wor);
	// tb.hash_print();
	// tb.remove( word );
	// tb.hash_print();
	// cout << "^^^"<< tb.search(word) << '\n';


	return 0;
}

