// Q23 Geometry Calculator - CS 318

#include <iomanip>
#include <iostream>
#include <math.h>

void printMenu() {
	std::cout << "Geometry Calculator\n\n";
	std::cout << "     1. Calculate the Area of a Circle\n";
	std::cout << "     2. Calculate the Area of a Rectangle\n";
	std::cout << "     3. Calculate the Area of a Triangle\n";
	std::cout << "     4. Quit\n\n";
	std::cout << "Enter your choice (1-4):";
}

void geoCalc(int choice, bool &quit){
	
	double const PI = 3.14159;
	double rad;
	double length, width;
	double base, height;
	
	switch (choice){
	case 1: // circle
		
		std::cout << "\nPlease enter the radius: ";
		std::cin >> rad;
		std::cout << "\nArea = " << std::pow(rad, 2) * PI << "\n\n";

		break;
	case 2: // rectangle
		
		std::cout << "\nPlease enter the length: ";
		std::cin >> length;
		std::cout << "Please enter the width: ";
		std::cin >> width;
		std::cout << "\nArea = " << length * width << "\n\n";

		break;
	case 3: // triangle
				
		std::cout << "\nPlease enter the base: ";
		std::cin >> base;
		std::cout << "Please enter the height: ";
		std::cin >> height;
		std::cout << "\nArea = " << base * height * 0.5 << "\n\n";

		break;
	case 4: // quit
		quit = true;
		break;
	default:
		std::cout << "Bad input, quitting.\n";
		quit = true;
	}
}

int main() {

	int choice;
	bool quit = false;

	while (!quit){
		printMenu();
		std::cin >> choice;
		geoCalc(choice, quit);
	}
	
	return 0;
}