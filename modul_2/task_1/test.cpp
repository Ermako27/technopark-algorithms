#include <assert.h>
#include <iostream>
#include <string>
#include <vector>


int main()
{
	std::string s = "qwerty";
	for(auto x:s){
		std::cout << x - '0'<< "\n";
	}

	return 0;
}	