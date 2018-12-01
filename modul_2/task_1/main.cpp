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

#include <iostream>
#include <vector>
#include <string>



template<typename T>
class HashTable {
public:

    HashTable(int size, const T& _del, const T _empty);
    ~HashTable(){}

    T empty;
    T del;

    bool has(const T& key);
    bool add(const T& key);
    bool remove(const T& key);

private:
    void reHash();

    std::vector<T> table;
    int count_of_elements;
    int size_of_table;

    int hash1( const T& word );
    int hash2( const T& word );

};

template<typename T>
HashTable<T>::HashTable(int size, T _del, T _empty){
    size_of_table = size;
    del = _del;
    empty = _empty;
    count_of_elements = 0;
    for (int i = 0; i < size_of_table; i++)
        table.push_back(empty);
}

/////////////// ХЕШ-ФУКНЦИИ /////////////////////
template<typename T>
int HashTable<T>::hash1( const T& word ){ // с конца строки
	int ln = word.length(); // берем длину строки
	int a = 127;
	int result = 0;
	for (int i = ln - 1; i >=0 ; --i){
		result = (result * a + (word[i] - '0')) % size_of_table;
	}

	return result % size_of_table;
}


template<typename T>
int HashTable<T>::hash2( const T& word ){ // с начала строки, необходимо чтобы h2 была нечетна, а size_of_table был степенью 2 -> будут взаимно простыми
	int a = 237;
	int result = 0;
	for (auto x : word)
		result = (result * a + (x - '0')) % size_of_table;
	if (result % 2 == 0)
		return result+1;
	return result % size_of_table;
}


//////////////////// МЕТОДЫ ///////////////////////////


template<typename T>
void HashTable<T>::reHash() {
    std::vector<T> newData;
    newData.resize(size_of_table*2, empty);

    for (int i = 0; i < size_of_table; i++) {
        if (table[i] != empty && table[i] != del) {
    		int h2 = hash2(table[i]);
    		int j = 0;
    		int h = hash1(table[i]);
    		while (newData[h] != empty && j < size_of_table * 2) {
        		i++;
        		h = (h + h2) % (size_of_table * 2);
    		}
    		newData[h] = table[i];
        }
    }
    table = newData;
    size_of_table *= 2;
}


template<typename T>
bool HashTable<T>::has(const T& key) {
    int i = 0;
    int h2 = hash2(key);
    int h = hash1(key);

    while (table[h] != empty && i < size_of_table) {
        if (table[h] == key) {
            return true;
        }
        i++;
        h = (h + h2) % size_of_table;
    }
    return false;
}

template<typename T>
bool HashTable<T>::add(const T& key) {
    if ((double)count_of_elements / size_of_table - (double)3/4 > 0.001) {
        reHash();
    }
    int i = 0;
    int h2 = hash2(key);
    int h = hash1(key);

    int firstDeleted = 0;
    bool findDeleted = false;
    while (table[h] != empty && i < size_of_table) {
        if (table[h] == key) {
            return false;
        }
        if (table[h] == del) {
            firstDeleted = h;
            findDeleted = true;
        }
        i++;
        h = (h + h2) % size_of_table;
    }
    if (table[h] != empty) {
        if (findDeleted) {
            table[firstDeleted] = key;
            count_of_elements++;
            return true;
        }
        return false;
    }
    table[h] = key;
    count_of_elements++;
    return true;
}


template<typename T>
bool HashTable<T>::remove(const T& key) {
    int i = 0;
    int h2 = hash2(key);
    int h = hash1(key);
    while (table[h] != key && i < size_of_table) {
        if (table[h] == empty) {
            return false;
        }
        i++;
        h = (h + h2) % size_of_table;
    }
    if (table[h] == key) {
        table[h] = del;
        count_of_elements--;
        return true;
    }
    return false;
}

int main(int argc, const char * argv[]) {
    HashTable<std::string> dict(8, "wqer09234", "wery345324");
    char c;
    std::string str, answ;

    while (std::cin.get(c)) {
        std::cin >> str;
        switch (c) {
            case '+':
                std::cout << (dict.add(str) ? "OK" : "FAIL") << std::endl;
                break;
            case '-':
                std::cout << (dict.remove(str) ? "OK" : "FAIL") << std::endl;
                break;
            case '?':
                std::cout << (dict.has(str) ? "OK" : "FAIL") << std::endl;
                break;
            default:
                break;
        }
        std::cin.get();
    }

    return 0;
}