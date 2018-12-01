#include <iostream>
#include <vector>
#include <list>
#include <utility>

int main()
{	
	int n = 5;
	std::vector<std::list<int>> vec_list;

	vec_list.resize(n);
	for (int i = 0; i < n; i++){
		vec_list[i].resize(n, 9);
	}

	for (auto l : vec_list){
		for (auto e : l){
			std::cout << e << " ";
		}
		std::cout << "\n";
	}

	std::cout << "\n";
	std::vector<std::list<std::pair<int, int>>> vec_pair;
	vec_pair.resize(n);
	for (int i = 0; i < n; i++){
		vec_pair[i].resize(n, std::make_pair(n-i,n));
	}

	for (auto l : vec_pair){
		for (auto e : l){
			std::cout << e.first << " " << e.second << " | ";
		}
		std::cout << "\n";
	}

	return 0;
}