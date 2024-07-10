#include <iostream>
#include <cmath>
#include <vector>

int count = 0;
int PathToOrigin(int x, int y) {
	if (x == 0 && y == 0) {
		count++;
	}
	if (abs(x-1) < abs(x)) {
		PathToOrigin(x-1,y);
	}
	//DO NOT PUT else in front of this condition 
	//It will ignore another path to be found
	if (abs(y-1) < abs(y)) {
		PathToOrigin(x,y-1);
	}
	return count;
}
int main() {
	int x = 15;
	int y = 10;
	std::cout << "x: " << x << std::endl;
	std::cout << "y: " << y << std::endl;
	int v = PathToOrigin(x,y);
	std::cout << "possible paths: " << v << std::endl;

}