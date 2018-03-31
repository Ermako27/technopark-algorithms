#include <iostream>
#include <assert.h>

/*
Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
Формат входных данных.
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”. 
Формат выходных данных.
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

3_1. Реализовать очередь с динамическим зацикленным буфером.
*/

class Queue {

public: 
	Queue();
	~Queue() { delete[] buffer; }
	void push(int elem);
	int pop();
private:
	int *buffer; // сам буфер
	int buffSize; // размер буфера
	int count; // реальное количество элементов
	int head; // первый в очереди 
	int tail; // последний

	void grow(); // увеличение буфера
};


Queue::Queue(): buffSize(8), count(0), head(0), tail(0)
{
	buffer = new int[buffSize];
}


void Queue::grow() 
{
    int i = 0;
    int *newbuffer = new int[buffSize * 2];
    
    for (int j = head; j < tail; j++) 
    {
        newbuffer[i] = buffer[j % buffSize];
        i++;
    }
    buffSize = buffSize * 2;
    head = 0; 
    tail = buffSize / 2;
    delete[] buffer;
    buffer = newbuffer;
    
}


void Queue::push(int b) 
{
    if (count == buffSize) // если количество элементов равно размеру буфера 
        grow();

    buffer[tail % buffSize] = b;
    tail++;
    count++;
}


int Queue::pop() 
{
    if (count == 0) 
        return -1;
    head++;
    count--;
    return buffer[(head - 1) % buffSize ];
}

int main()
{
	Queue qObj;

	int comand, value;

	int countComands;
	std::cin >> countComands;
	assert(countComands <= 1000000 && countComands > 0);

	for (int i = 0; i < countComands; i++)
	{
		std::cin >> comand >> value;
		if (comand == 2) // pop
		{
			if (qObj.pop() != value)
			{
				std::cout << "NO" << "\n";
				return 0;
			}
		}
		if (comand == 3) // push
			qObj.push(value);
	}

	std::cout << "YES" << "\n";
	return 0;
}
