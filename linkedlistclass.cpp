// CS318 - Linked Lists
// Jason Jendro

#include <iostream>
#include "intList.h"

int rng(int min, int max) // returns rand integer between min and max
{
	int rangeVal = (max - min) + 1;
	return (rand() % rangeVal) + min;
}

int main() {
	IntList list;

	//For testing...
	srand(62);

	for (int i = 1; i <= 100; i++) {
		int random = rng(10, 99);
		// std::cout << random << " ";
		list.insert(random);
	}

	std::cout << "Linked List Functions\n\n";
	list.print(10);
	list.printReverse(10);
	std::cout << "\nSIZE: " << list.getSize() << "\n";
	std::cout << "VALUE: " << list.getValueAt(list.getSize()-2) << "\n";
	std::cout << "PRINT ARRAY STYLE: ";
	for (int i = 0, len = list.getSize(); i < len; i++) {
		std::cout << list.getValueAt(i) << " ";
	}
	for (int i = list.getSize() - 1; i >= 0; i--) {
		std::cout << list.getValueAt(i) << " ";
	}

	std::cout << "\n\n";

	return 0;
}



