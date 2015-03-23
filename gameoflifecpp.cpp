// CS-318 The Game of Life Modified to print to cout
// Jason Jendro

#include <iomanip>
#include <fstream>
#include <iostream>
#include <Windows.h>

std::ofstream dataOut;
const int	numRows = 40,
			numCols = 40;

void clear_screen() // causes flicker, clears screen
{
	DWORD n;                         /* Number of characters written */
	DWORD size;                      /* number of visible characters */
	COORD coord = { 0 };               /* Top left screen position */
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	/* Get a handle to the console */
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(h, &csbi);

	/* Find the number of characters to overwrite */
	size = csbi.dwSize.X * csbi.dwSize.Y;

	/* Overwrite the screen buffer with whitespace */
	FillConsoleOutputCharacter(h, TEXT(' '), size, coord, &n);
	GetConsoleScreenBufferInfo(h, &csbi);
	FillConsoleOutputAttribute(h, csbi.wAttributes, size, coord, &n);

	/* Reset the cursor to the top left position */
	SetConsoleCursorPosition(h, coord);
}

void resetScreen() // no flicker, just rewrites screen
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void printCritters(int arr[][numCols], int gen) {
	std::cout << "Generation " << gen + 1 << "\n\n";
	int lineCount = 0;
	char printThis;

	for (int iRow = 0; iRow < numRows; iRow++) {
		for (int iCol = 0; iCol < numCols; iCol++) {
			++lineCount;
			printThis = (arr[iRow][iCol] == 0) ? ' ' : '*';

			if (lineCount > 0 && lineCount % numCols == 0) { std::cout << printThis << "\n"; }
			else { std::cout << printThis << " "; }
		}
	}
	std::cout << "\n\n";
}

int getTotalNeighbors(int arr[][numCols], int row, int col) {
	int moves[8][2] = { { -1, 0 }, { -1, -1 }, { 0, -1 }, { 1, -1 }, { 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 1 } }; // all possible moves in 8 directions
	int total = 0;

	for (int i = 0; i < 8; i++) {
		int r = row,
			c = col;

		// apply move
		r += moves[i][0];
		c += moves[i][1];		

		int inBounds = (r >= 0 && c >= 0 && r <= (numRows - 1) && c <= (numCols - 1)) ? true : false; // Check for in bounds	

		if (inBounds) { // good cell, proceed
			int cell = arr[r][c];
			if (cell == 1) { // found life in adjacent cell, increment total
				total++;
			}
		}
	}

	return total;
}

void zeroOut(int arr[][numCols]) {
	for (int iRow = 0; iRow < numRows; iRow++) {
		for (int iCol = 0; iCol < numCols; iCol++) {
			arr[iRow][iCol] = 0;
		}
	}
}

void letThereBeCritters(int kirk[][numCols], int picard[][numCols]) {

	// zero out picard
	zeroOut(picard);

	for (int iRow = 0; iRow < numRows; iRow++) {
		for (int iCol = 0; iCol < numCols; iCol++) {
			int total = getTotalNeighbors(kirk, iRow, iCol);

			if (kirk[iRow][iCol] == 0 && total == 3) { // birth
				picard[iRow][iCol] = 1;
			}
			else if (total < 2 || total > 3) { // death
				picard[iRow][iCol] = 0;
			}
			else { // keep on keepin on
				picard[iRow][iCol] = kirk[iRow][iCol];
			}
		}
	}
}

int rng(int min, int max) // returns rand integer between min and max
{
	int rangeVal = (max - min) + 1;
	return (std::rand() % rangeVal) + min;
}

int main() {
	// dataOut.open("gameoflife-output.txt");
	int gen = 0; // generations counter

	srand(time(nullptr));

	/*
	int a[numRows][numCols] = { // filled per directions... or very close
		//0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
		{ 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 }, // 0
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1 }, // 1
		{ 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1 }, // 2
		{ 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1 }, // 3
		{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1 }, // 4
		{ 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1 }, // 5
		{ 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1 }, // 6
		{ 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 }, // 7
		{ 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, // 8
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // 9
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // 10
		{ 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, // 11
		{ 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1 }, // 12
		{ 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, // 13
		{ 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1 }, // 14
		{ 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1 }, // 15
		{ 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1 }, // 16
		{ 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1 }, // 17
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // 18
		{ 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 }  // 19
	};
	*/

	int a[numRows][numCols];

	// Fill a with random life
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			a[i][j] = rng(0, 1);
		}
	}

	int b[numRows][numCols] = { 0 }; // empty for swapping

	for (; gen < 500; gen++) {
		resetScreen();
		if (gen % 2 == 0) {
			letThereBeCritters(a, b); // gen 1
			printCritters(b, gen);
		}
		else {
			letThereBeCritters(b, a); // gen 2
			printCritters(a, gen);
		}
	}

	/*
	letThereBeCritters(a, b); // gen 1
	gen++;
	printCritters(b, gen);

	letThereBeCritters(b, a); // gen 2
	gen++;
	printCritters(a, gen);

	letThereBeCritters(a, b); // gen 3
	gen++;
	printCritters(b, gen);

	letThereBeCritters(b, a); // gen 4
	gen++;
	printCritters(a, gen);

	letThereBeCritters(a, b); // gen 5
	gen++;
	printCritters(b, gen);

	letThereBeCritters(b, a); // gen 6
	gen++;
	printCritters(a, gen);
	*/

	// std::cout << "Results have been printed to gameoflife-output.txt..." << std::endl;

	// dataOut.close();
	return 0;
}




