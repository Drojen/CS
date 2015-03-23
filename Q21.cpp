// Q21 How Many Pizzas? - CS 318

#include <iomanip>
#include <iostream>
#include <math.h>

int main() {

	const double AREA = 14.125;
	const double PI = 3.14159;
	double diameter, slicesPer, people, slicesNeeded, pizzasNeeded;
	char yorn = 'y';

	while (yorn == 'y' || yorn == 'Y') {

		std::cout << "\nEnter pizza diameter: ";
		std::cin >> diameter;
		std::cout << "Enter number of people: ";
		std::cin >> people;

		slicesPer = (std::pow((diameter / 2), 2) * PI) / AREA;
		slicesNeeded = people * 4;
		pizzasNeeded = slicesNeeded / slicesPer;

		std::cout << "Order " << std::ceil(pizzasNeeded) << " pizzas.";
		std::cout << "\n\nCalculate again? Y/N: ";
		std::cin >> yorn;

	}


	return 0;
}