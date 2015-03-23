// Fibonacci - CS 318

#include <iomanip>
#include <iostream>

void runFor(double spawns, int start, int reproPeriod) {
	int a = 0;
	int b = 0;
	int temp;
	int print = spawns - 10;
	std::cout << "------------------------ FOR Loop -----------------------------\n";
	for (int i = 0; i < spawns; i++){
		if (i == 0) {
			b = start;
		}
		else if (i == 1){
			a = b;
		}
		else {
			temp = a;
			a = b;
			b += temp;
		}
		if (i >= print){
			std::cout << i * reproPeriod << " Days = " << b << std::endl;
		}
	}
	std::cout << "\n\n";
}
void runWhile(double spawns, int start, int reproPeriod) {
	int a = 0;
	int b = 0;
	int temp; 
	int print = spawns - 10;
	int i = 0;
	std::cout << "------------------------ WHILE Loop ---------------------------\n";
	while (i < spawns) {
		if (i == 0) {
			b = start;
		}
		else if (i == 1){
			a = b;
		}
		else {
			temp = a;
			a = b;
			b += temp;
		}
		if (i >= print){
			std::cout << i * reproPeriod << " Days = " << b << std::endl;
		}
		++i;
	}
	std::cout << "\n\n";
}
void runDoWhile(double spawns, int start, int reproPeriod) {
	int a = 0;
	int b = 0;
	int temp;
	int print = spawns - 10;
	int i = 0;
	std::cout << "------------------------ DO WHILE Loop ------------------------\n";
	do {
		if (i == 0) {
			b = start;
		}
		else if (i == 1){
			a = b;
		}
		else {
			temp = a;
			a = b;
			b += temp;
		}
		if (i >= print){
			std::cout << i * reproPeriod << " Days = " << b << std::endl;
		}
		++i;
	} while (i < spawns);
	std::cout << "\n\n";
}

int main() {
	int		reproPeriod = 5,
			days = 205,
			start = 5;
	double	spawns = (days / reproPeriod) + 1;

	if (start <= 0) { start = 1; }

	runFor(spawns, start, reproPeriod);
	// runWhile(spawns, start, reproPeriod);
	// runDoWhile(spawns, start, reproPeriod);

	return 0;
}