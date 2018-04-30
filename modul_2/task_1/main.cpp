/*
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.

1_2. Для разрешения коллизий используйте двойное хеширование.


Формат входных данных
Каждая строка входных данных задает одну операцию над множеством. Запись операции состоит из типа операции и следующей за ним через пробел строки, над которой проводится операция.
Тип операции  – один из трех символов:
    +  означает добавление данной строки в множество; 
    -  означает удаление  строки из множества;  
    ?  означает проверку принадлежности данной строки множеству. 
При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве. При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.

stdin:

+ hello
+ bye
? bye
+ bye
- bye
? bye
? hello

stdout:

OK
OK
OK
FAIL
OK
FAIL
OK
*/

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

template<typename T>
class Hash
{
public:
	Hash(int size);
	// ~Hash();

	bool insert(const T& elem);
	bool remove(const T& elem);
	bool search(const T& elem);
	void show();
private:
	void rehash();
	struct HashNode 
	{
		explicit HashNode(T elem) : value(elem) {}
		T value;
		bool is_deleted = false;
	};

	int count_of_elements;
	int size_of_table;
	vector<HashNode*> table;

	// хешфункции
	int hash1( const T& word );
	int hash2( const T& word );
};


template<typename T>
int Hash<T>::hash1( const T& word ){ // с конца строки
	int ln = word.length(); // берем длину строки
	int a = 127;
	int result = 0;
	for (int i = ln - 1; i >=0 ; --i){
		result = (result * a + (word[i] - '0')) % size_of_table;
	}

	return result % size_of_table;
}

template<typename T>
void Hash<T>::show(){
	for (int i = 0; i < size_of_table; i++){
		if(table[i] != nullptr && !table[i]->is_deleted){
			cout << table[i]->value << " | ";
		}
		else
			cout << "NULL |";
	}
	cout << "\n";
}

template<typename T>
int Hash<T>::hash2( const T& word ){ // с начала строки, необходимо чтобы h2 была нечетна, а size_of_table был степенью 2 -> будут взаимно простыми
	int a = 237;
	int result = 0;
	for (auto x : word)
		result = (result * a + (x - '0')) % size_of_table;
	if (result % 2 == 0)
		return result+1;
	return result % size_of_table;
}



template<typename T>
Hash<T>::Hash(int size) : size_of_table(size), table(size_of_table, nullptr), count_of_elements(0)
{}

template<typename T>
void Hash<T>::rehash() {
	int old_size = size_of_table;
    size_of_table *= 2;
    vector<HashNode*> newTable;
    newTable.resize(size_of_table, nullptr);

    for (int i = 0; i < old_size; i++) {
        if (table[i] != nullptr && !table[i]->is_deleted) {
            int h1 = hash1(table[i]->value);
            int h2 = hash2(table[i]->value);

            int j = 0;
            while (newTable[h1] != nullptr && j < size_of_table) {
                h1 = (h1 + h2) % size_of_table;
                j++;
            }
            newTable[h1] = new HashNode(table[i]->value);
        }
    }

    table = newTable;
}




// void Hash<T>::resize(){
// 	int old_size = size_of_table;
// 	size_of_table *= 2;
// 	vector<HashNode*> new_table(size_of_table,nullptr);
// 	for (int i = 0; i < old_size; i++){
// 		if (table[i] != nullptr && !table[i]->is_deleted){
// 			cout << "VALUE: " << table[i]->value;
// 			int h1 = hash1(table[i]->value);
// 			int h2 = hash2(table[i]->value);
// 			int j = 0;
// 			// int h1 = (h1 + j * h2)% size_of_table;
// 			while(table[h1] != nullptr && j < size_of_table){
// 				// cout<< "CUR: " << table[h1]->value << "\n";
// 				h1 = (h1 + h2)% size_of_table;
// 				j++;
// 				// h1 = (h1 + j * h2)% size_of_table;
// 			}
// 			cout << "h1: " << h1 << "\n";
// 			new_table[h1] = new HashNode(table[i]->value);
// 		}
// 	}

// 	table = new_table;
// }


template<typename T>
bool Hash<T>::insert(const T& elem){
	double alpha  = (double)count_of_elements / (double)size_of_table;
	// cout << "BEFORE: ";
	// show();
	if (alpha >= 0.75){
		rehash();
		// cout << "BEFORE: ";
		// show();
	}

	int h1 = hash1(elem);
	int h2 = hash2(elem);

	int i = 0;
	int firstdeleted = -1;
	while (table[h1] != nullptr && i < size_of_table){
		if (table[h1]->value == elem && !table[h1]->is_deleted){
			return false;
		}
		if (table[h1]->is_deleted && firstdeleted < 0){
			firstdeleted = h1;
		}
			h1 = (h1 + h2)% size_of_table;
			i++;
	}

	if (firstdeleted < 0){
		table[h1] = new HashNode(elem);
	}
	else{
		table[firstdeleted]->value = elem;
		table[firstdeleted]->is_deleted = false;
	}
	count_of_elements++;
	// cout << "AFTER: ";
	// show();
	return true;
}

template<typename T>
bool Hash<T>::remove(const T& elem){
	int h1 = hash1(elem);
	int h2 = hash2(elem);

	int i = 0;
	while (table[h1] != nullptr && i < size_of_table){
		if(table[h1]->value == elem && !table[h1]->is_deleted){
			table[h1]->is_deleted = true;
			count_of_elements--;
			return true;
		}
		h1 = (h1 + h2)% size_of_table;
		i++;
	}
	return false;
}


template<typename T>
bool Hash<T>::search(const T& elem){
	int h1 = hash1(elem);
	int h2 = hash2(elem);

	int i = 0;
	while (table[h1] != nullptr && i < size_of_table){
		if (table[h1]->value == elem && !table[h1]->is_deleted){
			return true;
		}
		h1 = (h1 + h2)% size_of_table;
		i++;;
	}
	return false;
}


int main() {
    char c;
    string word;

    Hash<string> tb(8);

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
