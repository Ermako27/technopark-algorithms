/*
4_1. Жадина.
Вовочка ест фрукты из бабушкиной корзины. В корзине лежат фрукты разной массы. Вовочка может поднять не более K грамм. Каждый фрукт весит не более K грамм. За раз он выбирает несколько самых тяжелых фруктов, которые может поднять одновременно, откусывает от каждого половину и кладет огрызки обратно в корзину. Если фрукт весит нечетное число грамм, он откусывает большую половину. Фрукт массы 1гр он съедает полностью.
Определить за сколько подходов Вовочка съест все фрукты в корзине.
Формат входных данных. Вначале вводится n - количество фруктов и n строк с массами фруктов. Затем K - "грузоподъемность".
Формат выходных данных. Неотрицательное число - количество подходов к корзине.
*/

#include <iostream>
#include <assert.h>




class Hippo
{
public:

	int* heap;
	int heapSize;

	explicit Hippo(int size);
	~Hippo() {delete[] heap; };
	void siftUp(int* arr, int i);
	void siftDown(int* arr, int i);
	void buildheap(int* arr);
	void printHeap();
	int howManySteps(int* arr, int k);
	// void grow();
	// void addElement(int elem);
};

Hippo::Hippo(int size) // конструктор
{
	heapSize = size;
	heap = new int[heapSize];
}

void Hippo::printHeap()
{
	std::cout << "\n";
	for (int i = 0; i < heapSize; i++)
		std::cout << heap[i] << " |";
	std::cout << "\n";
}

void Hippo::siftUp(int* arr, int i) // просеивание вверх
{
	while (i > 0)
	{
		int dad = (i - 1) / 2;
		if (arr[i] <= arr[dad])
			return;
		std::swap(arr[i], arr[dad]);
		i = dad;

		std::cout << "\n\n";
		printHeap();
		std::cout << "\n\n";
	}
}

void Hippo::siftDown(int* arr, int i)
{
	int right = 2 * i + 2;
	int left = 2 * i + 1;

	int biggest = i;
	if (left < heapSize && arr[left] > arr[i])
		biggest = left;

	if (right < heapSize && arr[right] > arr[biggest])
		biggest = right;

	if (biggest != i)
	{
		std::swap(arr[i], arr[biggest]);
		siftDown(arr, biggest);
	}
}

void Hippo::buildheap(int* arr)
{
	for (int i = heapSize / 2 - 1; i >= 0; i--)
		siftDown(arr,i);
}

int Hippo::howManySteps(int* arr, int k)
{
	int steps = 0;
	int copyK = k;
	int count = 0;
	int countOfFruits = heapSize;
	// std::cout << "countOfFruits" << countOfFruits;
	// printHeap();
	while (countOfFruits != 0)
	{

		while(k >= arr[0] && countOfFruits && count != heapSize) // пока не кончится грузоподъемность 
		{
			// printHeap();
			k -= arr[0];
			if (arr[0] > 1)
				arr[0] = arr[0] / 2; 

			else if (arr[0] = 1) // если фрукт весит 1 то мы его съедаем полностью
			{
				countOfFruits -= 1;
				arr[0] = 0;
			}
			buildheap(arr); // строим кучу по новым данным
			// printHeap();
			count += 1;
		}
		steps += 1;
		// std::cout << k << "\n";
		k = copyK;
		count = 0;
		// printHeap();
	}
	return steps;
}


int main()
{	
	int size;
	int elem;
	int k; // грузоподъемность 
	int result;

	// std::cout << "Введите размер кучи: ";
	std::cin >>	size;

	Hippo hp(size); // объект кучи

	// std::cout << "\nВведите элементы кучи: ";
	for (int i = 0; i < size; i++)
	{
		std::cin >> elem;
		hp.heap[i] = elem;
	}

	hp.buildheap(hp.heap);

	// std::cout << "\nКучи: ";
	// hp.printHeap();

	// std::cout << "\nВведите грузоподъемность: ";
	std::cin >>	k;
	result = hp.howManySteps(hp.heap, k);
	std::cout << result;

	return 0;
}