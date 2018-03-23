#include <iostream>

void printArray(double *arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		std::cout << " " << arr[i];
	}
}

int binarySearch(const double *arr, int count, double elem, int prevPos)
{
	int left = prevPos;
	int right = count - 1;
	int mid;
	int search = -1;
	while (left <= right)
	{
		mid = (left + right) / 2;
		// std::cout << "mid: " << mid;
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
	// int prePosition;
	// double object;
	std::cout << "введите размер массива N: ";
	std::cin >> n;
	double *nArr = new double[n];

	std::cout << "введите размер массива M: ";
	std::cin >> m;
	double *mArr = new double[m];

	std::cout << "заполните массив N: ";
	for (int i = 0; i < n; i++)
		std::cin >> nArr[i];

	// std::cout << "Что искать?: ";
	// std::cin >> object;

	std::cout << "\nзаполните массив M: ";
	for (int i = 0; i < m; i++)
		std::cin >> mArr[i];

	printArray(nArr, n);
	std::cout << "\n";
	printArray(mArr, m);

	std::cout << "\nпересечение массивов: ";

	for (int i = 0; i < m; i++)
	{
		result = binarySearch(nArr, n, mArr[i], result);
		if (result != -1)
			std::cout << nArr[result] << " ";
		else
			result = 0;

	}

	// result = binarySearch(nArr, n, object);
	// std::cout << "\nПозиция искомого элемента: " << result;

	return 0;
}