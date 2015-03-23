/*
CS318 - Random Walk
Jason Jendro
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>

int rng(int min, int max) // returns rand integer between min and max
{
	int rangeVal = (max - min) + 1;
	return (std::rand() % rangeVal) + min;
}

class Park
{
private:
	int _map[13][14];
public:
	void loadMap(int map[][14], int rows, int cols);
	int stepOn(int row, int col);
	void demolish(int row, int col);
	void print(int rows, int cols);
	Park() {}
};
void Park::print(int rows, int cols) {
	std::cout << "\n\nOle' Harv's Last Drunk Walk: " << std::endl;
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++){
			std::cout << std::setw(3) << _map[r][c];
			if (c == cols - 1) {
				std::cout << std::endl;
			}
		}
	}
}
void Park::loadMap(int map[][14], int rows, int cols) {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++){
			_map[r][c] = map[r][c];
		}
	}
}
int Park::stepOn(int row, int col) {
	if (_map[row][col] > 0 && _map[row][col] < 3) {
		demolish(row, col);
		return 5; // flower cost
	}
	else if (_map[row][col] < 0) {
		return -1;
	}
	else if (_map[row][col] == 3){
		return 3;
	}
	else {
		return 0;
	}

}
void Park::demolish(int row, int col) {
	_map[row][col] -= 1;
}

class Harvey
{
private:
	static int TOTAL_WALKS;
	static int TOTAL_COST;
	static int TOTAL_STEPS;
	static int TOTAL_WINS;
	static int TOTAL_BATHS;
	int _rowLoc, _colLoc;
	bool _stillWalking;
public:
	void walk(Park &map); // calls stepOn
	void success() { TOTAL_WINS += 1, _stillWalking = false; };
	void takeAbath() { TOTAL_BATHS += 1, _stillWalking = false; }
	int getBaths() { return TOTAL_BATHS; }
	int getWalks() { return TOTAL_WALKS; }
	int getCost() { return TOTAL_COST; }
	int getWins() { return TOTAL_WINS; }
	int getSteps() { return TOTAL_STEPS; }
	bool getStillWalking() { return _stillWalking; }
	Harvey(int row, int col) {
		_rowLoc = row;
		_colLoc = col;
		_stillWalking = true;
		TOTAL_WALKS += 1;
	}
};
int Harvey::TOTAL_WALKS = 0;
int Harvey::TOTAL_COST = 0;
int Harvey::TOTAL_STEPS = 0;
int Harvey::TOTAL_WINS = 0;
int Harvey::TOTAL_BATHS = 0;

void Harvey::walk(Park &map) {
	int cellValue = 0;

	// define moves { row, col }
	int forward[2] = { 0, 1 };
	int backward[2] = { 0, -1 };
	int right[2] = { 1, 0 };
	int left[2] = { -1, 0 };

	int rand = rng(0, 100);

	if (rand <= 10) { // backward
		_rowLoc += backward[0];
		_colLoc += backward[1];
		// std::cout << "Backward: " << _rowLoc << ", " << _colLoc;
	}
	else if (rand > 10 && rand <= 30) { // right
		_rowLoc += right[0];
		_colLoc += right[1];
		// std::cout << "Right: " << _rowLoc << ", " << _colLoc;
	}
	else if (rand > 30 && rand <= 55) { // left
		_rowLoc += left[0];
		_colLoc += left[1];
		// std::cout << "Left: " << _rowLoc << ", " << _colLoc;
	}
	else { // forward
		_rowLoc += forward[0];
		_colLoc += forward[1];
		// std::cout << "Forward: " << _rowLoc << ", " << _colLoc;
	}

	cellValue = map.stepOn(_rowLoc, _colLoc);
	TOTAL_STEPS += 1;

	if (cellValue == -1) {
		takeAbath();
	}
	else if (cellValue == 3) {
		success();
	}
	else if (cellValue != 3 && cellValue != -1) {
		TOTAL_COST += cellValue;
	}
}

int main() {
	std::srand(std::time(nullptr)); // random seed from time
	// std::srand(5); // controlled seed

	const int	numRows = 13,
		numCols = 14,
		trials = 1; // how many walks harvey takes

	int parkMap[numRows][numCols] = {
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }, // 0
		{ -1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -1 },				// 1
		{ -1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -1 },				// 2
		{ -1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -1 },				// 3	
		{ -1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -1 },				// 4
		{ -1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -1 },				// 5
		{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },				// 6
		{ -1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -1 },				// 7
		{ -1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -1 },				// 8
		{ -1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -1 },				// 9
		{ -1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -1 },				// 10
		{ -1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -1 },				// 11
		{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }  // 12
	};

	int times = 0;
	char yorn = 'y';

	while (yorn == 'y' || yorn == 'Y') {
		for (int i = 0; i < trials; i++) {
			Harvey harv(6, 1); // {6, 1} is the starting point on the island
			Park garden;
			garden.loadMap(parkMap, numRows, numCols);

			while (harv.getStillWalking()) {
				harv.walk(garden);
			}
			if (i == trials - 1) {
				garden.print(numRows, numCols);
			}
		}

		times++;
		Harvey results(6, 1);
		std::cout << std::setprecision(2) << std::fixed;
		std::cout << "\n\n------ Results from Harvey's " << std::setw(5) << trials * times << " walks ------ \n" << std::endl;
		std::cout << "Number of Total Steps:              " << std::setw(7) << std::right << results.getSteps() << std::endl;
		std::cout << "Average Number of Steps:            " << std::setw(7) << std::right << static_cast<double>(results.getSteps()) / (trials * times) << std::endl;
		std::cout << "Total Cost of All Walks:           $" << std::setw(7) << std::right << results.getCost() << std::endl;
		std::cout << "Average Cost per Walk:             $" << std::setw(7) << std::right << static_cast<double>(results.getCost()) / (trials * times) << std::endl;
		std::cout << "Number of Times Harvey Made it:     " << std::setw(7) << std::right << results.getWins() << std::endl;
		std::cout << "Number of Times Harvey Fell in:     " << std::setw(7) << std::right << results.getBaths() << std::endl;
		std::cout << "Percent of Times Harvey Fell in:   %" << std::setw(7) << std::right << (static_cast<double>(results.getBaths()) / (trials * times)) * 100 << std::endl;
		std::cout << "\n----------------------------------------------- \n" << std::endl;

		std::cout << "Go Again? Y/N? ";
		std::cin >> yorn;
	}

	return 0;
}