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
	// void addElement(int elem);
	void siftDown(int* arr, int i);
	void buildheap(int* arr);
	// void grow();
	void printHeap();

};

// void Hippo::grow()
// {
// 	int *newHeap = new int[heapSize * 2];
// 	for (int i = 0; i < heapSize; ++i)
// 		newHeap[i] = heap[i];
// 	heapSize *= 2;
// 	delete[] heap;
// 	heap = newHeap;
// }

Hippo::Hippo(int size)
{
	heapSize = size;
	heap = new int[heapSize];
	for (int i = 0; i < heapSize; i++)
		heap[i] = 0;
}

void Hippo::printHeap()
{
	for (int i = 0; i < heapSize; i++)
		std::cout << heap[i] << " |";
}

void Hippo::siftUp(int* arr, int i)
{
	// while (i > 0)
	// {
	// 	int dad = (i - 1) / 2;
	// 	if (arr[dad] <= arr[i])
	// 	{
	// 		std::swap(arr[dad], arr[i]);
	// 		i = dad;
	// 	}
	// 	else
	// 		return;
	// }
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

// void Hippo::addElement(int elem)
// {
// 	heap[count] = elem;
// 	count++;
// 	siftUp(heap, count - 1);
// }




int main()
{	
	int size;
	int elem;

	std::cout << "Введите размер кучи: ";
	std::cin >>	size;

	Hippo hp(size); // объект кучи

	std::cout << "\nВведите элементы кучи: ";
	for (int i = 0; i < size; i++)
	{
		std::cin >> elem;
		hp.heap[i] = elem;
	}

	hp.buildheap(hp.heap);

	std::cout << "\nКучи: ";
	hp.printHeap();





	return 0;
}