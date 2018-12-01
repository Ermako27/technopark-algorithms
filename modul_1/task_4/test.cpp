#include <iostream>
#include <vector>
#include <ctime>
#include <assert.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>


///////////////////////////////  MY PROGRAMM //////////////////////////////////////////


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



/////////////////////////////// NOT MY //////////////////////////////////////////////

class CBinaryHeap {
public:
    CBinaryHeap();

    ~CBinaryHeap();

    CBinaryHeap(const CBinaryHeap &other);

    CBinaryHeap(std::vector<int> array);

    void Add(int element);

    int ExtractMax();

    bool IsEmpty();

    int SeeMax();

    void Print();

private:
    std::vector<int> array;

    void siftUp(int index);

    void siftDown(int index);
};

CBinaryHeap::CBinaryHeap() {
    //Init
}

CBinaryHeap::~CBinaryHeap() {
    //Delete
}

CBinaryHeap::CBinaryHeap(const CBinaryHeap &other) {
    //Copy
}

void CBinaryHeap::siftUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (array[index] <= array[parent])
            return;
        std::swap(array[index], array[parent]);
        index = parent;
    }
}

void CBinaryHeap::siftDown(int index) {
    int left = index * 2 + 1; //Элемент ниже ребра графа, слева
    int right = index * 2 + 2; //Тоже самое, справа
    int largest = index;
    assert(index < array.size());
    if (!(left < array.size() && array[left] > array[index]))
        left = index;
    if (!(right < array.size() && array[right] > array[index]))
        right = index;
    if (array[left] > array[right])
        largest = left;
    else largest = right;

    if (largest != index) {
        std::swap(array[index], array[largest]);
        siftDown(largest);
    }
}

CBinaryHeap::CBinaryHeap(std::vector<int> array) {
    this->array = array;
    for (int i = (int) (array.size() / 2 - 1); i >= 0; --i) {
        siftDown(i);
    }
}

void CBinaryHeap::Add(int element) {
    array.push_back(element);
    siftUp((int) (array.size() - 1));
}

int CBinaryHeap::ExtractMax() {
    assert(!array.empty());
    int result = array[0];
    array[0] = array.back();
    array.pop_back();

    if (!array.empty())
        siftDown(0);

    return result;
}

bool CBinaryHeap::IsEmpty() {
    return array.empty();
}

int CBinaryHeap::SeeMax() {
    assert(!IsEmpty());
    return array[0];
}

void CBinaryHeap::Print() {
    for(int i = 0; i < array.size(); i++)
        std::cout << array[i] << ' ';
    std::cout << '\n';
}

int getAccessCount(std::vector<int> fruitsArray, int maxCapacity /* Грузоподьемность */ ) {
    int count = 0;
    CBinaryHeap fruits(fruitsArray);
    while (!fruits.IsEmpty()) {
        int weightAviliable = maxCapacity;
        count++;
        std::vector<int> tmpVector;
        while (!fruits.IsEmpty() && fruits.SeeMax() <= weightAviliable) {
            weightAviliable -= fruits.SeeMax();
            tmpVector.push_back(fruits.ExtractMax());
        }

        int tmp;
        while(!tmpVector.empty()) {
            tmp = tmpVector.back();
            tmpVector.pop_back();
            if (tmp != 1)
                fruits.Add(tmp / 2);

        }
        //fruits.Print();
    }
    return count;
}

// ///////////////////// MY MAIN /////////////////////

// int main()
// {	
// 	int size;
// 	int elem;
// 	int k; // грузоподъемность 
// 	int result;

// 	// std::cout << "Введите размер кучи: ";
// 	std::cin >>	size;

// 	Hippo hp(size); // объект кучи

// 	// std::cout << "\nВведите элементы кучи: ";
// 	for (int i = 0; i < size; i++)
// 	{
// 		std::cin >> elem;
// 		hp.heap[i] = elem;
// 	}

// 	hp.buildheap(hp.heap);

// 	// std::cout << "\nКучи: ";
// 	// hp.printHeap();

// 	// std::cout << "\nВведите грузоподъемность: ";
// 	std::cin >>	k;
// 	result = hp.howManySteps(hp.heap, k);
// 	std::cout << result;

// 	return 0;
// }

// /////////////////////////// NOT MY MAIN /////////////////////////////

// int main() {
//     int n = 0;
//     std::cin >> n;

//     std::vector<int> fruits((unsigned long) n);
//     for (int i = 0; i < n; i++)
//         std::cin >> fruits[i];

//     int k = 0; // Грузоподьемность
//     std::cin >> k;

//     int result = getAccessCount(fruits, k);
//     std::cout << result;
//     return 0;
// }

int main()
{

    unsigned int start_time; // начальное время
    // здесь должен быть фрагмент кода, время выполнения которого нужно измерить
    unsigned int end_time;  // конечное время
    unsigned int search_time;



	////////// MY PART //////////
	int size;
	int elem;
	int k; // грузоподъемность 
	int myResult;
	///////// NOT MY PART ////////
	int n;
	int noMyResult;

	//////////////////////////////
	int m;

	srand(time(NULL));
	m = 1 + rand() % 2000 + 1; // размер хипа

	// srand(time(NULL));
	k = 1 + rand() % 1000 + 1; // рандомим грузоподъемность
	std::cout << "k: " << k << "\n";

	Hippo hp(m); // мой объект 
	std::vector<int> fruits((unsigned long) m); // не мой вектор

	for (int j = 0; j < m;j++) // заполняем массивы
	{
		// srand(time(NULL));
		int elem = 1 + rand() % k; // рандомим число от 1 до k включительно
		hp.heap[j] = elem;
		fruits[j] = elem;
		std::cout << elem << " |";
	}
	std::cout << "\n\n";

	start_time = clock();
	hp.buildheap(hp.heap); // создаем мою кучу
	myResult = hp.howManySteps(hp.heap, k);
	end_time = clock();
	unsigned int myTime = end_time - start_time;

	start_time = clock();
	noMyResult = getAccessCount(fruits, k);
	end_time = clock();
	unsigned int notMyTime = end_time - start_time;

	std::cout << "My result: " << myResult << " | " << myTime << "\n";
	std::cout << "True result: "  << noMyResult  << " | " << notMyTime<< "\n";






}