

#include <iostream>
#include <string>
#include <vector>
#include <time.h>

#define HASH_buffer_DEFAULT_BUFFER_SIZE 8
#define HASH_BUFFER_REHASH_RATIO 0.75
#define HASH_P1 17
#define HASH_P2 19

// хеш 1
int hash1(const std::string &key, int size) {
    int hash = 0;
    for(int i = key.size(); i >= 0; i--) {
        hash += (HASH_P1 * hash + key[i]) % size;
    }
    return hash % size;
}

// хеш 2
int hash2(const std::string &key, int size) {
    int hash = 0;
    for(int i = key.size(); i >= 0; i--) {
        hash += (HASH_P2 * hash + key[i]) % size;
    }
    return (2 * hash + 1) % size;
}

template<class T>
class HashTableNode {
private:
    std::string _key; // ключ
    bool _isDeleted; // удалён?
public:
    HashTableNode(const std::string &key): _key(key), _isDeleted(false) {}

    // возвращает ключ
    const std::string &getKey() const {
        return _key;
    }

    // сохраняет ключ
    void setKey(const std::string &key) {
        _key = key;
    }

    // удалён?
    bool isDeleted() const {
        return _isDeleted;
    }

    // помечаем как удаленную
    void setDeleted() {
        _isDeleted = true;
    }

    // помечаем как неудаленную
    void setNotDeleted() {
        _isDeleted = false;
    }
};

template<class T>
class HashTable {
private:
    std::vector<HashTableNode<T>*> _buffer; // буфер
    int _bufferSize; // размер буфера
    int _size; // реальное кол-во элементов

    // перехеширование
    void _rehash() {
        std:: cout << "RESIZE\n";
        int newBufferSize = _bufferSize * 2;
        std::vector<HashTableNode<T>*> newBuffer(newBufferSize, NULL);

        for(int i = 0; i < _bufferSize; i++) {
            if(_buffer[i] != NULL && !_buffer[i]->isDeleted()) {
                int h1 = hash1(_buffer[i]->getKey(), newBufferSize),
                    h2 = hash2(_buffer[i]->getKey(), newBufferSize);

                int j = 0;
                while(newBuffer[h1] != NULL && j < newBufferSize) {
                    h1 = (h1 + h2) % newBufferSize;
                    j++;
                }

                newBuffer[h1] = _buffer[i];
            }
            else
            {
                delete _buffer[i];
            }
            _buffer[i] = NULL;
        }

        _buffer = newBuffer;
        _bufferSize = newBufferSize;
    }

public:
    HashTable(): _buffer(HASH_buffer_DEFAULT_BUFFER_SIZE, NULL), _bufferSize(HASH_buffer_DEFAULT_BUFFER_SIZE), _size(0) {
    }

    ~HashTable() {
        for(int i = 0; i < _buffer.size(); i++) {
            delete _buffer[i];
        }
    }

    // вывод содержимого
    void show() {
        std::cout << "[[" << std::endl;
        for(int i = 0; i < _bufferSize; i++) {
            if(_buffer[i] != NULL && !_buffer[i]->isDeleted()) {
                std::cout << "[" << i << "] " << _buffer[i]->getKey() << std::endl;
            }
        }
        std::cout << "]]" << std::endl;
    }

    // добавление
    bool add(const std::string &key) {
        if( ((double) _size / (double) _bufferSize) >= HASH_BUFFER_REHASH_RATIO) {
            _rehash();
        }

        int h1 = hash1(key, _bufferSize),
            h2 = hash2(key, _bufferSize);

        int i = 0,
            firstDeleted = -1;
        while(_buffer[h1] != NULL && i < _bufferSize) {
            if(_buffer[h1]->getKey() == key && !_buffer[h1]->isDeleted()) {
                // уже есть такой ключ
                return false;
            }

            if(_buffer[h1]->isDeleted() && firstDeleted < 0) {
                // сохраняем номер первого удалённого
                firstDeleted = h1;
            }

            h1 = (h1 + h2) % _bufferSize;
            i++;
        }

        if(firstDeleted < 0) {
            // вставляем новый ключ
            _buffer[h1] = new HashTableNode<T>(key);
        }
        else
        {
            // вставляем на место удалённой
            _buffer[firstDeleted]->setKey(key);
            _buffer[firstDeleted]->setNotDeleted();
        }
        _size++;

        return true;
    }

    // удаление
    bool remove(const std::string &key) {
        int h1 = hash1(key, _bufferSize),
            h2 = hash2(key, _bufferSize);
        int i = 0;
        while(_buffer[h1] != NULL && i < _bufferSize) {
            if(_buffer[h1]->getKey() == key && !_buffer[h1]->isDeleted()) {
                // нашли
                _buffer[h1]->setDeleted();
                _size--;
                return true;
            }

            h1 = (h1 + h2) % _bufferSize;
            i++;
        }

        return false;
    }

    // проверка наличия ключа
    bool has(const std::string &key) const {
        int h1 = hash1(key, _bufferSize),
            h2 = hash2(key, _bufferSize);
        int i = 0;
        while(_buffer[h1] != NULL && i < _bufferSize) {
            if(_buffer[h1]->getKey() == key && !_buffer[h1]->isDeleted()) {
                // нашли
                return true;
            }

            h1 = (h1 + h2) % _bufferSize;
            i++;
        }

        return false;
    }
};

int main() {
    unsigned int start_time; // начальное время
    // здесь должен быть фрагмент кода, время выполнения которого нужно измерить
    unsigned int end_time;  // конечное время
    unsigned int search_time;
    HashTable<int> map;

    char command = '\0';
    std::string key("");

    bool result = false;
    // while(std::cin >> command >> key) {
    //     switch(command) {
    //         case '+':
    //             tmpRes = map.add(key);
    //             break;
    //         case '?':
    //             tmpRes = map.has(key);
    //             break;
    //         case '-':
    //             tmpRes = map.remove(key);
    //             break;
    //         default:
    //             continue;
    //     }

    //     std::cout << (tmpRes ? "OK" : "FAIL") << std::endl;
    // }
    while (std::cin >> command >> key) {

        switch (command) {
        case '+':
            std::cout << "---------------------" << "\n";
            start_time = clock();
            result = map.add(key);
            end_time = clock();
            search_time = end_time - start_time;
            std::cout << "in_time: " << search_time << "\n";
            break;
        case '-':
            std::cout << "---------------------" << "\n";
            start_time = clock();
            result = map.remove(key);
            end_time = clock();
            search_time = end_time - start_time;
            std::cout << "out_time: " << search_time << "\n";
            break;
        case '?':
            std::cout << "---------------------" << "\n";
            start_time = clock();
            result = map.has(key);
            end_time = clock();
            search_time = end_time - start_time;
            std::cout << "search_time: " << search_time << "\n";
        default:
            continue;
        }

        std::cout << ((result) ? "OK" : "FAIL") << "\n\n";
    }

    return 0;
}