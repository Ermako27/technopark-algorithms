#include <iostream>
#include <assert.h>

/*
Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию. A[0..n-1] и B[0..m-1]. n >> m. Найдите их пересечение. 
Требуемое время работы: O(m * log k), где k - позиция элемента B[m-1] в массиве A.
 В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1].
n, k ≤ 10000.

*/

void searchBorders(double *a, int n, double element, int &first, int &last) {
    int index = 1;

    if (index < first)
        index = first;

    while (index < n && a[index] < element)
    	index *= 2;

    if ((first < index/2))
        first = index / 2;

    last = index > n ? n : index;
}

int binarySearch(double *arr, int count, double elem, int prevPos)
{
	int left = prevPos;
	int right = count - 1;
	int mid;
	searchBorders(arr, count, elem, left, right);
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (arr[mid] < elem)
			left = mid + 1;
		else if (arr[mid] > elem)
			right = mid - 1;
		else if (arr[mid] == elem)
			return mid;
	}
	return -1;
}

int main()
{
	int n;
	int m;
	int result = 0;
	int prevPosition;

	std::cin >> n;
	assert(n <= 10000);
	double *nArr = new double[n];

	std::cin >> m;
	assert(m <= 10000);
	double *mArr = new double[m];

	// заполнение массивов
	for (int i = 0; i < n; i++)
		std::cin >> nArr[i];

	for (int i = 0; i < m; i++)
		std::cin >> mArr[i];


	for (int i = 0; i < m; i++)
	{	
		prevPosition = result; // сохраняем позицию предыдущего найденного элемента
		result = binarySearch(nArr, n, mArr[i], result);
		if (result != -1)
		{
			if (nArr[result] != mArr[m-1])
				std::cout << nArr[result] << " ";
			else 
				std::cout << nArr[result] << "\n";

		}
		else
			result = prevPosition;
	}

	delete[] nArr;
	delete[] mArr;

	return 0;
}