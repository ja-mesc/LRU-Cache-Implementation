#include "Header.h"
#include<iostream>

int main() {
	LRUCache cache(3);


	cache.put(1, 1);
	cache.put(2, 2);
	cache.put(3, 3); //now max capacity

	cache.get(1); //now 2 is the LRU

	cache.put(5, 5); //now 2 is evicted since capacity exceeded

	std::cout << cache.get(2) << "\n"; //should return -1

	std::cout << cache.get(1) << "\n"; //should return 1
	std::cout << cache.get(5) << "\n"; //return 5

}