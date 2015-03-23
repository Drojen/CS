// Q13 Currency - CS 318

#include <iomanip>
#include <iostream>

int main() {

	double	yenRate = 103.36,
			euroRate = 0.75,
			bpsRate = 0.6;
	
	double n;
	
	std::cout << std::showpoint << std::setprecision(2) << std::fixed;

	std::cout << "Please enter a US dollar amount to convert: ";
	std::cin >> n;

	std::cout << "Yen             = " << n*yenRate << std::endl;
	std::cout << "Euros           = " << n*euroRate << std::endl;
	std::cout << "British Pounds  = " << n*bpsRate << std::endl;

	return 0;
}