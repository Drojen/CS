// CS-318 Recursion Stuff
// Jason Jendro

#include <iostream>
#include "intlist.h" // for linked list problems

// Gaddis problem #4 function
int recursiveArraySum(int arr[], int size) {
	size--;
	if (size < 0) {
		return 0;
	}
	else {
		return arr[size] + recursiveArraySum(arr, size);
	}
}

// Gaddis problem #5 function
int recursiveMultiply(int x, int y) {
	if (x <= 0) {
		return 0;
	}
	else {
		return y + recursiveMultiply(--x, y);
	}
}

// Gaddis problem #7 function
int sumOfNumbers(int x) {
	if (x == 1) {
		return 1;
	}
	else {
		return x + sumOfNumbers(x-1);
	}
}

// Rimes problem #1 function
int digitCount(int x) {
	if (x < 0) { // check for negative number, convert to positive if so
		return digitCount(-x);
	}
	if (x < 10) {
		return 1;
	}
	else {
		return  1 + digitCount(x / 10);
	}
}

// Rimes problem #2 function
int reverseNumber(int x) {
	int base = 1;
	while (x / (base * 10) >= 1 ) {
		base *= 10;
	}
	if (x <= 9) {
		return x;
	}
	else { 
		int digit = (x % 10) * base; 
		return reverseNumber(x / 10) + digit;
	}
}

// Rimes problem #3 function
void recursivePrint(int arr[], int size) {
	size--;
	if (size < 0) {
		return;
	}
	else {
		std::cout << arr[size] << " ";
		recursivePrint(arr, size);
		std::cout << arr[size] << " ";
	}
}

int main() {
	std::cout << "=================== Recursion Workout ===================\n\n";
	
	// Gaddis problem #4 driver
	const int sumArrSize = 9;
	int sumArr[sumArrSize] = { 33, 55, 77, 99, 88, 66, 44, 22, 11 };
	std::cout << "Gaddis Problem #4 - Sum an Array\n " << "Array Sum = " << recursiveArraySum(sumArr, sumArrSize) << "\n\n";

	// Gaddis problem #5 driver
	int x = 45,
		y = 23;
	std::cout << "Gaddis Problem #5 - Multiply Two Numbers\n " << x << " x " << y << " = " << recursiveMultiply(x, y) << "\n\n";

	// Gaddis problem #7 driver
	int numToSum = 100;
	std::cout << "Gaddis Problem #7 - Sum of Numbers\n " << "Sum of Numbers for " << numToSum << " = " << sumOfNumbers(numToSum) << "\n\n";

	// Rimes problem #1 driver
	int a = 123789,
		b = 405060,
		c = 87481398;
	std::cout << "Rimes Problem #1 - Digit Count\n";
	std::cout << " " << a << " has " << digitCount(a) << " digits\n";
	std::cout << " " << b << " has " << digitCount(b) << " digits\n";
	std::cout << " " << c << " has " << digitCount(c) << " digits\n\n";

	// Rimes problem #2 driver
	std::cout << "Rimes Problem #2 - Number in Reverse Order\n";
	std::cout << " " << a << " reversed is " << reverseNumber(a) << "\n";
	std::cout << " " << b << " reversed is " << reverseNumber(b) << "\n";
	std::cout << " " << c << " reversed is " << reverseNumber(c) << "\n\n";

	// Rimes problem #3 driver
	std::cout << "Rimes Problem #3 - Print Array Forwards and Backwards \n ";
	recursivePrint(sumArr, sumArrSize);
	std::cout << "\n\n";

	// See intList.h and intList.cpp for function declarations and definitions for the following problems...
	IntList list; // building the list, 9 items
	list.insert(99);
	list.insert(22);
	list.insert(33);
	list.insert(44);
	list.insert(66);
	list.insert(77);
	list.insert(88);
	list.insert(11);
	list.insert(55);

	// Rimes problem #4 driver
	std::cout << "Rimes Problem #4 - Count Nodes in a Linked List \n ";
	std::cout << list.countNodes(nullptr);
	std::cout << "\n\n";

	// Rimes problem #5 driver
	std::cout << "Rimes Problem #5 - Print a Linked List \n ";
	list.print(nullptr);
	std::cout << "\n\n";

	// Rimes problem #6 driver
	std::cout << "Rimes Problem #6 - Print a Linked List in Reverse \n ";
	list.printReverse(nullptr);
	std::cout << "\n\n";

	return 0;
}