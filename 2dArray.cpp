// 2d Array - CS 318
// Jason Jendro

#include <iomanip>
#include <fstream>
#include <iostream>

std::ifstream arrayFile;
std::ofstream dataOut;
const int	numRows = 15, // sorry for the globals, ideally this would be all wrapped in a class
			numCols = 15;
int count = 0;

void loadArray(int arr[][numCols], int &count) {
	arrayFile.open("TwoDim.txt");
	if (!arrayFile) {
		std::cerr << "There was a problem opening the input file!";
	}

	int x;
	int num = 1,
		row = 0,
		col = 0;

	while (arrayFile >> x) {
		arr[row][col] = x;
		if (num % numCols == 0) { // end of row, reset
			row++;
			num = 1;
			col = 0;
		}
		else { // not end of row, keep going	
			col++;
			num++;
		}
		++count;
	}

	// If it didn't fill the array up, fill the extra spots with zeros
	if (col + 1 != numCols){
		for (int i = col; i < numCols; i++) {
			arr[row][i] = 0;
		}
	}
	if (row + 1 != numRows){
		for (int r = row + 1; r < numRows; r++) {
			for (int c = 0; c < numCols; c++) {
				arr[r][c] = 0;
			}
		}
	}


	arrayFile.close();
}

void printArray(int arr[][numCols]) {
	dataOut << "CURRENT 2D ARRAY: " << std::endl;
	int lineCount = 0;

	for (int iRow = 0; iRow < numRows; iRow++) {
		for (int iCol = 0; iCol < numCols; iCol++) {
			++lineCount;
			if (lineCount > 0 && lineCount % numCols == 0) { dataOut << std::setw(5) << arr[iRow][iCol] << "\n"; }
			else { dataOut << std::setw(5) << arr[iRow][iCol] << " "; }
		}
	}
	dataOut << std::endl;
}

int getRowTotal (int arr[][numCols], int row) {
	int total = 0;
	
	for (int iCol = 0; iCol < numCols; iCol++) {
		total += arr[row][iCol];
	}

	return total;
}

int getColTotal(int arr[][numCols], int col) {
	int total = 0;

	for (int iRow = 0; iRow < numRows; iRow++) {
		total += arr[iRow][col];
	}

	return total;
}

int getHighestInRow(int arr[][numCols], int row) {
	int max = arr[row][0];
	for (int iCol = 1; iCol < numCols; iCol++) {
		if (max < arr[row][iCol]) {
			max = arr[row][iCol];
		}
	}
	return max;
}

int getLowestInRow(int arr[][numCols], int row) {
	int min = arr[row][0];
	for (int iCol = 1; iCol < numCols; iCol++) {
		if (min > arr[row][iCol]) {
			min = arr[row][iCol];
		}
	}
	return min;
}

int getHighestInCol(int arr[][numCols], int col) {
	int max = arr[0][col];
	for (int iRow = 1; iRow < numRows; iRow++) {
		if (max < arr[iRow][col]) {
			max = arr[iRow][col];
		}
	}
	return max;
}

int getLowestInCol(int arr[][numCols], int col) {
	int min = arr[0][col];
	for (int iRow = 1; iRow < numRows; iRow++) {
		if (min > arr[iRow][col]) {
			min = arr[iRow][col];
		}
	}
	return min;
}

int getMaxAdjacent(int arr[][numCols], int row, int col, int *loc, int allLocs[][2]){
	int moves[8][2] = { { -1, 0 }, { -1, -1 }, { 0, -1 }, { 1, -1 }, { 1, 0 }, { 1, 1 }, { 0, 1 }, { -1, 1 } }; // all possible moves in 8 directions
	int max = -10000;
	int r, c;
	
	for (int i = 0; i < 8; i++) {
		r = row,
		c = col;
		r += moves[i][0];
		c += moves[i][1];
		bool inBounds;
		bool nonDupe = true;

		if (r >= 0 && c >= 0 && r <= (numRows - 1) && c <= (numCols - 1)) { // Check for in bounds	
			inBounds = true;
		}
		else {
			inBounds = false;
		}
		
		for (int i = 0; i < 4; i++) { // check for previous locations so it doesn't track back to the same location multiple times
			int rCheck = allLocs[i][0];
			int cCheck = allLocs[i][1];

			if (rCheck == r && cCheck == c) { // found duplicate
				nonDupe = false; 
			}
		}

		if (inBounds && nonDupe) { // good cell, proceed
			int temp = arr[r][c];
			if (temp > max) { 
				max = temp;
				loc[0] = r;
				loc[1] = c;
			}
		}
	}
	return max;
}

void connectFour(int arr[][numCols], int &a, int &b, int &c, int &d) {
	int w, x, y, z; // a, b, c, d are the winning combo ... w, x, y, z are the temp comparison combo as the function walks through moves
	int tempTotal = 0,
		maxTotal = 0;
	int loc[2] = { -1 }; // current location tracker {row,col}


	for (int iRow = 0; iRow < numRows; iRow++) {
		for (int iCol = 0; iCol < numCols; iCol++) {
			int allLocs[4][2] = { -1 }; // cummulative location tracker for w, x, y, z
			w = arr[iRow][iCol];
			allLocs[0][0] = iRow;
			allLocs[0][1] = iCol;
			x = getMaxAdjacent(arr, iRow, iCol, loc, allLocs);
			allLocs[1][0] = loc[0];
			allLocs[1][1] = loc[1];
			y = getMaxAdjacent(arr, loc[0], loc[1], loc, allLocs);
			allLocs[2][0] = loc[0];
			allLocs[2][1] = loc[1];
			z = getMaxAdjacent(arr, loc[0], loc[1], loc, allLocs);
			allLocs[3][0] = loc[0];
			allLocs[3][1] = loc[1];

			tempTotal = w + x + y + z;

			std::cout << w << " -> " << x << " -> " << y << " -> " << z << " = " << w + x + y + z << std::endl; // Sanity check to console

			if (tempTotal > maxTotal) { // we have a new winner
				maxTotal = tempTotal;
				a = w;
				b = x;
				c = y;
				d = z;
			}
		}
	}
}

int main() {
	dataOut.open("2darray-output.txt");

	int grid[numRows][numCols];
	// Read in Data
	loadArray(grid, count);

	// Print entire array
	printArray(grid);
	
	// Compute and print array average
	double arrAvg;
	double arrSum = 0;
	for (int i = 0; i < numRows; i++){
		arrSum += getRowTotal(grid, i);
	}
	arrAvg = arrSum / count;
	dataOut << "Average of all values: " << arrAvg << std::endl;

	/* 
	
	BIG ASSUMPTION HERE SINCE IT WAS NOT STATED IN THE DIRECTIONS.... 
	When it is stated to print/sum/whatever rows/cols x thru x, it is assumed that we are counting from 0, not 1... we are referring to array indexes
	e.g. - "print rows 5 thru 10" means print rows with array indexes of 5 thru 10, not actual count of how many rows exist which would be array indexes of 4 thru 9
	All of the following are calculated with this assumption in mind
	
	*/

	// Compute and print totals for rows 5 thru 10
	for (int i = 5; i <= 10; i++) {
		dataOut << "Total sum of row " << i << " is: " << getRowTotal(grid, i) << std::endl;
	}

	// Compute and print totals for each column for cols 2 thru 8
	for (int i = 2; i <= 8; i++) {
		dataOut << "Total sum of column " << i << " is: " << getColTotal(grid, i) << std::endl;
	}

	// Find and print the biggest numbers in each odd numbered row ZERO IS EVEN
	for (int i = 1; i < numCols; i += 2) {
		dataOut << "Biggest number in Row " << i << " is: " << getHighestInRow(grid, i) << std::endl;
	}

	// Find and print the smallest numbers in each even numbered column ZERO IS EVEN
	for (int i = 0; i < numRows; i += 2) {
		dataOut << "Smallest number in Column " << i << " is: " << getLowestInCol(grid, i) << std::endl;
	}

	// Sum all the values for cols 7 thru 12 (one number answer)
	int colSum = 0;
	for (int i = 7; i <= 12; i++) {
		colSum += getColTotal(grid, i);
	}
	dataOut << "Total sum of columns 7 thru 12 is: " << colSum << std::endl;

	// Sum all the values for rows 10 thru 14 (one number answer)
	int rowSum = 0;
	for (int i = 10; i <= 14; i++) {
		rowSum += getRowTotal(grid, i);
	}
	dataOut << "Total sum of rows 10 thru 14 is: " << rowSum << std::endl;

	// Sum together the biggest numbers from each column 2 thru 8 (one number)
	int colBiggestSum = 0;
	for (int i = 2; i <= 8; i++) {
		colBiggestSum += getHighestInCol(grid, i);
	}
	dataOut << "Total sum of the biggest numbers in columns 2 thru 8 is: " << colBiggestSum << std::endl;

	// Sum together the lowest numbers from each rows 0 thru 6 (one number)
	int rowLowestSum = 0;
	for (int i = 0; i <= 6; i++) {
		rowLowestSum += getLowestInRow(grid, i);
	}
	dataOut << "Total sum of the smallest numbers in rows 0 thru 6 is: " << rowLowestSum << std::endl;

	// Find and print 4 adjacent
	int a, b, c, d;
	connectFour(grid, a, b, c, d);
	dataOut << "The four numbers that are adjacent in any of 8 directions that have the biggest sum in the 2d array are: \n" << a << ", " << b << ", " << c << ", " << d << std::endl;
	dataOut << "Their sum is: " << a + b + c + d << std::endl;

	dataOut.close();
	return 0;
}