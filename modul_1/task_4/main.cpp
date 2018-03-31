/*
4_1. Жадина.
Вовочка ест фрукты из бабушкиной корзины. В корзине лежат фрукты разной массы. Вовочка может поднять не более K грамм. Каждый фрукт весит не более K грамм. За раз он выбирает несколько самых тяжелых фруктов, которые может поднять одновременно, откусывает от каждого половину и кладет огрызки обратно в корзину. Если фрукт весит нечетное число грамм, он откусывает большую половину. Фрукт массы 1гр он съедает полностью.
Определить за сколько подходов Вовочка съест все фрукты в корзине.
Формат входных данных. Вначале вводится n - количество фруктов и n строк с массами фруктов. Затем K - "грузоподъемность".
Формат выходных данных. Неотрицательное число - количество подходов к корзине.
*/

#include <iostream>
#include <assert.h>
#include <vector>




class Hippo
{
public:

	Hippo(std::vector<int> array);

	~Hippo(){};


	void printHeap();

	void add(int elem);

	int extractMax();

	bool IsEmpty();

	int Max();

private:
	std::vector<int> heap;
	void siftUp(int i);

	void siftDown(int i);
};

void Hippo::printHeap() // функция печати
{
	std::cout << "\n";
	for (int i = 0; i < heap.size(); i++)
		std::cout << heap[i] << " |";
	std::cout << "\n";
}


Hippo::Hippo(std::vector<int> array) // конструктор
{
	this->heap = array;
	int start = heap.size() / 2 - 1;
	for (int i = start; i >= 0; i--)
		siftDown(i);
}

void Hippo::siftUp(int i)
{
	while(i > 0)
	{
		int parent = (i - 1) / 2;
		if (heap[parent] >= heap[i])
			return;
		std::swap(heap[parent],heap[i]);
		i = parent;
	}
}

void Hippo::siftDown(int i)
{
	int left = 2 * i + 1;
	int right = left + 1;

	int biggest = i;
	if (left < heap.size() && heap[left] > heap[i])
		biggest = left;

	if (right < heap.size() && heap[right] > heap[biggest])
		biggest = right;

	if (biggest != i)
	{
		std::swap(heap[i], heap[biggest]);
		siftDown(biggest);
	}
}

void Hippo::add(int elem) 
{	
	int s = heap.size(); // размер кучи
	heap.push_back(elem);
	siftUp(s-1);
}

int Hippo::extractMax()
{
	assert(!heap.empty());
	int max = heap[0]; // взяли максимальный элемент
	heap[0] = heap.back(); // последний элемент заносим в корень
	heap.pop_back(); // удаляем его из конца
	siftDown(0); // просеиваем вниз
	return max;
}

bool Hippo::IsEmpty() 
{
    return heap.empty();
}

int Hippo::Max() 
{
    return heap[0];
}



int howManySteps(std::vector<int> fruitsArray, int k)
{
	Hippo hp(fruitsArray);
	int steps = 0;
	int copyK = k;
	int tmp;
	int max;
	while(!hp.IsEmpty())
	{
		std::vector<int> tmpHeap; // временный массив для хранения надкусанных фруктов
		while(!hp.IsEmpty() && hp.Max() <= k) // пока есть фрукты и хватает грузоподъемности
		{
			k -= hp.Max();
			max = hp.extractMax(); // укусили фрукт
			tmpHeap.push_back(max); 
		}

		while(!tmpHeap.empty()) // пока есть надкусанные фрукты
		{
			tmp = tmpHeap.back();
			tmpHeap.pop_back();
			if (tmp != 1) // фрукты весом 1 съедаются
				hp.add(tmp / 2); // просеиваем половину их веса обратно в кучу(корзину)
		}
		steps++;
		k = copyK;
	}
	return steps;
}


int main()
{	
	int size;
	int elem;
	int k; // грузоподъемность 
	int result;
	std::cin >>	size;

	std::vector<int> array((unsigned int) size);
	for (int i = 0; i < size; i++)
	{
		std::cin >> elem;
		array[i] = elem;
	}

	std::cin >>	k;
	result = howManySteps(array, k);
	std::cout << result;

	return 0;
}