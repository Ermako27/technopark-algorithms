#include <iostream>
#include <assert.h>
/*

“Считалочка”. В круг выстроено N человек, пронумерованных числами от 1 до N. 
Будем исключать каждого k-ого до тех пор, пока не уцелеет только один человек. 
(Например, если N=10, k=3, то сначала умрет 3-й, потом 6-й, затем 9-й, затем 2-й, затем 7-й, потом 1-й, потом 8-й, за ним - 5-й, и потом 10-й. 
Таким образом, уцелеет 4-й.) Необходимо определить номер уцелевшего.
N, k ≤ 10000.


*/
int schitalochka(int n, int k)
{
	int curPos = 0;
	for (int i = 1; i <= n; ++i)
		curPos = (curPos + k) % i;
	
	return ++curPos;
}

int main()
{
	int n;
	int k;
	std::cin >> n >> k;
	assert(n > 0 && n <= 10000 && k > 0 && k <= 10000);
    if (n == 1) 
    	std::cout << 1;
    else 
    	std::cout << schitalochka(n,k);
	return 0;
}
