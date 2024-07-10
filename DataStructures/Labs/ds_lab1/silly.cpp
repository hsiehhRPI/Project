#include <iostream>
int main(int argc, char* argv []){
	int product;
	product = 1;
	for(int i = 1;  i < argc; i++) {
		product *= atoi(argv[i]);
	}

	std::cout << "The product of integers: " << product << std::endl; 
}
	