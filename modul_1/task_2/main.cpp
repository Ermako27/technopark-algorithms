#include <iostream>


/*
Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию. A[0..n-1] и B[0..m-1]. n >> m. Найдите их пересечение. 
Требуемое время работы: O(m * log k), где k - позиция элемента B[m-1] в массиве A.
 В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1].
n, k ≤ 10000.

*/

int binarySearch(const double *arr, int count, double elem, int prevPos)
{
	int left = prevPos;
	int right = count - 1;
	int mid;
	int search = -1;
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
	int result;
	int prevPosition;

	std::cin >> n;
	double *nArr = new double[n];

	std::cin >> m;
	double *mArr = new double[m];

	for (int i = 0; i < n; i++)
		std::cin >> nArr[i];

	for (int i = 0; i < m; i++)
		std::cin >> mArr[i];

	for (int i = 0; i < m; i++)
	{	
		prevPosition = result;
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