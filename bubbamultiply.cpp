// CS318 - Bubba Multiply
// Jason Jendro

#include <iostream>
#include <fstream>
#include <iomanip>

std::ifstream inFile;

void Shuffle(int arr[], int count, int arrSize) {
	int start = count - 1,
		i = arrSize - 1;
	if (start != arrSize) {
		while (start >= 0) {
			arr[i] = arr[start];
			start--;
			i--;
		}
		while (i >= 0) {
			arr[i] = 0;
			i--;
		}
	}
}

void PrintNumber(int arr[], int arrSize, bool printSign) {
	bool leadingZeros = true,
		printedSign = false;
	std::cout << std::right << "   ";
	for (int i = 0; i < arrSize; i++) {
		if (arr[i] != 0) {
			leadingZeros = false;
			if (!printedSign && printSign) {
				std::cout << "\b\bx ";
				printedSign = true;
			}
		}
		if (!leadingZeros) { std::cout << arr[i]; }
		else { std::cout << ' '; }
	}
	std::cout << std::endl;
}

void ReadIn(int arr[], int &count) {
	char a;
	int i = 0;
	a = inFile.get();
	while (a != '\n' && a != '\r' && a != ' ') {
		arr[i] = a - '0';
		i++;
		a = inFile.get();
	}
	count = i;
}

void BubbaAdd(int res[], int numOne[], int numTwo[], int size) { // arrays must be shuffled prior to use
	for (int i = size; i > 0; i--) {
		res[i] = numOne[i] + numTwo[i] + res[i];
		res[i - 1] = res[i] / 10;
		res[i] = res[i] % 10;
	}
}

void BubbaMultiply(int res[], int numOne[], int numTwo[], int size) { // arrays must be shuffled  prior to use
	for (int i = size - 1; i > 0; i--) {
		int k = i; // working location
		for (int j = size - 1; j > 0; j--) {
			res[k] += numOne[i] * numTwo[j];
			res[k - 1] += res[k] / 10;
			res[k] = res[k] % 10;
			if (k > 0) { // don't go out of bounds
				k--;
			}
		}
	}
}

int main() {
	inFile.open("BigNumbersV2.txt");
	if (!inFile) { std::cerr << "Oops, file didn't open..."; }

	const int	MAX_INPUT = 60, // size of arrays
				TOTAL_SETS = 7; // number of data sets

	std::cout << "   ______________________ Bubba Multiply ______________________\n\n";

	int sets = 0;

	while (sets < TOTAL_SETS) {

		int numOne[MAX_INPUT] = { 0 },
			numTwo[MAX_INPUT] = { 0 },
			res[MAX_INPUT] = { 0 },
			iOne,
			iTwo;

		// Read in numbers
		ReadIn(numOne, iOne);
		ReadIn(numTwo, iTwo);

		// Shuffle them back
		Shuffle(numOne, iOne, MAX_INPUT);
		Shuffle(numTwo, iTwo, MAX_INPUT);

		// Multiplication magic
		BubbaMultiply(res, numOne, numTwo, MAX_INPUT);

		// Print them
		PrintNumber(numOne, MAX_INPUT, false);
		PrintNumber(numTwo, MAX_INPUT, true);
		std::cout << std::right << std::setw(63) << "------------------------------------------------------------" << std::endl;
		PrintNumber(res, MAX_INPUT, false);
		std::cout << "\n\n";
		sets++;
	}

	inFile.close();
	return 0;
}