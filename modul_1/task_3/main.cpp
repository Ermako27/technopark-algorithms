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
	explicit Queue( int size );
	~Queue() { delete[] buffer; }
	void push(int elem);
	int pop();
	void grow(); // увеличение буфера
private:
	int *buffer; // сам буфер
	int buffSize; // размер буфера
	int count; // реальное количество элементов
	int head; // первый в очереди 
	int tail; // последний

};


Queue::Queue(int size): buffSize(size), count(0), head(0), tail(0)
{
	buffer = new int[size+1];
}

void Queue::grow()
{
	int newbuffSize = buffSize * 2;
	int *newbuffer = new int[newbuffSize+1];
	int i = 0;
	i += buffSize;
	for (int i = 0; i <= count; i++)
	{
		newbuffer[i] = buffer[i];
	}
	delete[] buffer;
	buffer = newbuffer;
	buffSize = newbuffSize;
	// std::cout << "i: " << i << "\n";
	tail = i;
	tail = (tail-1) % buffSize;
	head = 0;

}

void Queue::push(int elem)
{

	if ((tail + 1) % buffSize == head) // если следующий за последним - первый в очереди,то массив полон -> увеличить буфер
		grow();
	buffer[tail] = elem;
	tail = (tail + 1) % buffSize;
	count++; // увеличиваем счетчик количества элементов
}

int Queue::pop()
{
	int res;
	if (head == tail) // если позиции первого и последнего совпали, значит массив пуст
		return -1;
	res = buffer[head];
	head = (head + 1) % buffSize;
	count--; // уменьшаем счетчик количества элементов
	return res;
}

int main()
{
	Queue qObj(1000);

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
