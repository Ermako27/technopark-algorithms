#include <iostream>

int main()
{
	int n;
	int k;
	std::cin >> n >> k;
	int *ar = new int[n];
	if (ar == nullptr)
	{
		delete ar;
		return 0;
	}
	for (int i = 0; i < n; i++)
	{
		ar[i] = 1;
	}

	int curPos = 0;
	int i = 0;
	int nCopy = n;
	int result;
	while (n != 0)
	{
		if (ar[curPos % nCopy] != 0)
		{
			result = curPos % nCopy;
			i += 1;
			if (i == k)
			{
				ar[curPos % nCopy] = 0;
				i = 0;
				n -= 1;
			}
		}
		curPos += 1;
	}

	result += 1;
	std::cout << result;

    return 0;
}