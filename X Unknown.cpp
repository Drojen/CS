// X Unknown - CS 318

#include <iomanip>
#include <iostream>
#include <math.h>
#include <vector>
#include <limits>

void getValues(std::vector<int> &values) {
	bool stop = false;
	int current;

	while (!stop){
		std::cin >> current;
		if (std::cin.fail()) {
			stop = true;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			values.push_back(current);
		}
	}
}

void calcValues(const std::vector<int> &values) {
	int len = values.size();
	int sum = 0;
	int current;
	double avg;

	for (int i = 0; i < len; i++){
		current = values[i];
		sum += current;
	}

	avg = static_cast<double>(sum) / len;

	std::cout << std::setprecision(1) << std::fixed;
	std::cout << "\nNumber of values  = " << std::setw(8) << std::right << len << std::endl;
	std::cout << "Sum of values     = " << std::setw(8) << std::right << sum << std::endl;
	std::cout << "Average of values = " << std::setw(8) << std::right << avg << std::endl;
}

int main() {
	char yorn = 'y';
	std::vector<int> values;

	while (yorn == 'y' || yorn == 'Y') {
		std::cout << "Enter as many integers as you like. Enter any letter to quit:\n";
		getValues(values);
		calcValues(values);
		values.clear();
		std::cout << "\nContinue? Y/N: ";
		std::cin >> yorn;
		std::cout << "\n";
	}
	
	return 0;
}