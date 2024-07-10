#include <iostream>
#include <cmath>

void compute_squares(int a[],  int b[], unsigned int n) {
	int *p;
	int *t;
	t = b;

	for (p = a; p<a+n; p++) {
		*t = pow(*p, 2);
		std::cout << *t << std::endl;

		t++;
	}
}

int main() {
	int a[5] = {1,2,3,4,5};
	int b[5] = {};
	compute_squares(a,b,5);

}