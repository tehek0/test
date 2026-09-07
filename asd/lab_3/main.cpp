#include <iostream>
#include <cmath>

int main() {
	int x;
	std::cin >> x;


	for (int k = 0; k < log(x) / log(3) + 5; ++k) {
		int a = pow(3, k);
		for (int l = 0; l < log(x) / log(5) + 5; ++l) {
			int b = pow(5, l);
			for (int m = 0; m < log(x) / log(7) + 5; ++m) {
				int c = pow(7, m);
				c = a * b * c;
				if (c > x)
					break;
				std::cout << c << std::endl;
			}
		}
	}
}