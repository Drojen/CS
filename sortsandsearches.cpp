/*
CS318 - Sort and Search Evaluations
Jason Jendro
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <string>

int rng(int min, int max) // returns rand integer between min and max
{
	int rangeVal = (max - min) + 1;
	return (std::rand() % rangeVal) + min;
}

void randStrFill(std::string arr[], int strLen, int arrSize) { // generates random strings and fills an array with them
	
	char charset[52] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	
	for (int j = 0; j < arrSize; j++) {
		std::string temp;
		for (int i = 0; i < strLen; i++) {
			int random = rng(0, 51);
			temp += charset[random];
		}
		arr[j] = temp;
	}
}

void fillKeys(std::string keys[], std::string source[], int keySize, int sourceSize){
	for (int i = 0; i < keySize; i++) {
		int random = rng(0, sourceSize - 1);
		if (i < sourceSize) {
			keys[i] = source[random];
		}
	}
}

void printStrings(std::string arr[], int size) {
	for (int i = 0; i < size; i++){
		std::cout << i + 1 << ". " << arr[i] << std::endl;
	}

}

class Timer {
private:
	clock_t _startTime;
	clock_t _endTime;
public:
	void start() { _startTime = clock(); }
	void stop() { _endTime = clock(); }
	double report() {
		double totalTime = difftime(_endTime, _startTime); // in clock ticks
		return totalTime;
	}
	Timer() {}
};

void bubbleSort(std::string arr[], int size) {
	std::string temp;
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void selectionSort(std::string arr[], int size) {
	int min;
	std::string	temp;
	for (int i = 0; i < size - 1; i++) {
		min = i;
		for (int j = i + 1; j < size; j++){
			if (arr[j] < arr[min]){
				min = j;
			}
		}
		if (min != i){ // new min, swap
			temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
		}
	}
}

void quickSort(std::string arr[], int left, int right) {
	int i = left, j = right;
	std::string tmp;
	std::string pivot = arr[(left + right) / 2];

	// partition 
	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};

	// recursion
	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);
}

double linearSearch(std::string keys[], std::string source[], int sizeKeys, int sizeSource) {
	double totalProbes = 0;	

	for (int i = 0; i < sizeKeys; i++) {
		bool foundIt = false;
		int sourceIndex = 0;
		while (!foundIt && i < sizeSource) {
			if (keys[i] == source[sourceIndex]) {
				foundIt = true;
			}
			else {
				sourceIndex++;
			}
			totalProbes++;
		}
	}

	return totalProbes / sizeKeys;
}

double binarySearch(std::string keys[], std::string source[], int sizeKeys, int sizeSource) {
	double totalProbes = 0;

	for (int i = 0; i < sizeKeys; i++) {
		bool foundIt = false;
		int high = sizeSource - 1,
			low = 0;
		int mid;

		while (low <= high && !foundIt) {
			mid = (high + low) / 2;
			if (keys[i] == source[mid]) {
				foundIt = true;
			}
			else {
				if (source[mid] < keys[i]) {
					low = mid + 1;
				}
				else if (source[mid] > keys[i]) {
					high = mid - 1;
				}
			}
			totalProbes++;
		}
	}

	return totalProbes / sizeKeys;
}

int main() {

	std::srand(std::time(nullptr));
	// std::srand(85); // controlled seed

	int strLimit = 25;

	std::string oneK[1000];
	std::string twoK[2000];
	std::string threeK[3000];
	std::string fourK[4000];
	std::string fiveK[5000];
	std::string sixK[6000];
	std::string searchKeys[2000];

	// Random string fill 1 - for bubble sorts, all of these will be overwritten for selection sorts
	std::cout << "Filling arrays...";
	randStrFill(oneK, strLimit, 1000);
	randStrFill(twoK, strLimit, 2000);
	randStrFill(threeK, strLimit, 3000);
	randStrFill(fourK, strLimit, 4000);
	randStrFill(fiveK, strLimit, 5000);
	randStrFill(sixK, strLimit, 6000);
	std::cout << " done." << std::endl;

	std::cout << "Quick sorting 1k...";
	Timer bubbleTimerOneK;
	bubbleTimerOneK.start();
	quickSort(oneK, 0, 999);
	bubbleTimerOneK.stop();
	std::cout << " done." << std::endl;

	std::cout << "Quick sorting 2k...";
	Timer bubbleTimerTwoK;
	bubbleTimerTwoK.start();
	quickSort(twoK, 0, 1999);
	bubbleTimerTwoK.stop();
	std::cout << " done." << std::endl;

	std::cout << "Quick sorting 3k...";
	Timer bubbleTimerThreeK;
	bubbleTimerThreeK.start();
	quickSort(threeK, 0, 2999);
	bubbleTimerThreeK.stop();
	std::cout << " done." << std::endl;

	std::cout << "Quick sorting 4k...";
	Timer bubbleTimerFourK;
	bubbleTimerFourK.start();
	quickSort(fourK, 0, 3999);
	bubbleTimerFourK.stop();
	std::cout << " done." << std::endl;

	std::cout << "Quick sorting 5k...";
	Timer bubbleTimerFiveK;
	bubbleTimerFiveK.start();
	quickSort(fiveK, 0, 4999);
	bubbleTimerFiveK.stop();
	std::cout << " done." << std::endl;

	std::cout << "Quick sorting 6k...";
	Timer bubbleTimerSixK;
	bubbleTimerSixK.start();
	quickSort(sixK, 0, 5999);
	bubbleTimerSixK.stop();
	std::cout << " done." << std::endl;

	// Random string fill 2 - for selection sorts
	std::cout << "Re-filling arrays...";
	randStrFill(oneK, strLimit, 1000);
	randStrFill(twoK, strLimit, 2000);
	randStrFill(threeK, strLimit, 3000);
	randStrFill(fourK, strLimit, 4000);
	randStrFill(fiveK, strLimit, 5000);
	randStrFill(sixK, strLimit, 6000); // this will be the string array that will be used for search testing with searchKeys[]
	std::cout << " done." << std::endl;

	std::cout << "Selection sorting 1k...";
	Timer selectionTimerOneK;
	selectionTimerOneK.start();
	selectionSort(oneK, 1000);
	selectionTimerOneK.stop();
	std::cout << " done." << std::endl;

	std::cout << "Selection sorting 2k...";
	Timer selectionTimerTwoK;
	selectionTimerTwoK.start();
	selectionSort(twoK, 2000);
	selectionTimerTwoK.stop();
	std::cout << " done." << std::endl;

	std::cout << "Selection sorting 3k...";
	Timer selectionTimerThreeK;
	selectionTimerThreeK.start();
	selectionSort(threeK, 3000);
	selectionTimerThreeK.stop();
	std::cout << " done." << std::endl;

	std::cout << "Selection sorting 4k...";
	Timer selectionTimerFourK;
	selectionTimerFourK.start();
	selectionSort(fourK, 4000);
	selectionTimerFourK.stop();
	std::cout << " done." << std::endl;

	std::cout << "Selection sorting 5k...";
	Timer selectionTimerFiveK;
	selectionTimerFiveK.start();
	selectionSort(fiveK, 5000);
	selectionTimerFiveK.stop();
	std::cout << " done." << std::endl;

	std::cout << "Selection sorting 6k...";
	Timer selectionTimerSixK;
	selectionTimerSixK.start();
	selectionSort(sixK, 6000);
	selectionTimerSixK.stop();
	std::cout << " done." << std::endl;

	std::cout << "Filling search keys...";
	fillKeys(searchKeys, sixK, 2000, 6000); // searchKeys[] is now filled with 2000 randomly selected strings from sixK[]
	std::cout << " done." << std::endl;
	std::cout << "Linear searching...";
	Timer linearSearchTimer;
	linearSearchTimer.start();
	double linearProbeAvg = linearSearch(searchKeys, sixK, 2000, 6000);
	linearSearchTimer.stop();
	std::cout << " done." << std::endl;

	std::cout << "Re-filling search keys...";
	fillKeys(searchKeys, sixK, 2000, 6000); // searchKeys[] is now filled with 2000 randomly selected strings from sixK[]
	std::cout << " done." << std::endl;
	std::cout << "Binary searching...";
	Timer binarySearchTimer;
	binarySearchTimer.start();
	double binaryProbeAvg = binarySearch(searchKeys, sixK, 2000, 6000);
	binarySearchTimer.stop();
	std::cout << " done.\n" << std::endl;

	// Results Printing
	std::cout << "________________ Sorting Results _________________\n" << std::endl;
	std::cout << std::setw(12) << "Array Size" << "   " << std::setw(5) << "1k" << " " << std::setw(5) << "2k" << " " << std::setw(5) << "3k" << " " << std::setw(5) << "4k" << " " << std::setw(5) << "5k" << " " << std::setw(5) << "6k" << " " << std::endl;
	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << std::setw(12) << "Quick" << "   " << std::setw(5) << bubbleTimerOneK.report() << " " << std::setw(5) << bubbleTimerTwoK.report() << " " << std::setw(5) << bubbleTimerThreeK.report() << " " << std::setw(5) << bubbleTimerFourK.report() << " " << std::setw(5) << bubbleTimerFiveK.report() << " " << std::setw(5) << bubbleTimerSixK.report() << std::endl;
	std::cout << std::setw(12) << "Selection" << "   " << std::setw(5) << selectionTimerOneK.report() << " " << std::setw(5) << selectionTimerTwoK.report() << " " << std::setw(5) << selectionTimerThreeK.report() << " " << std::setw(5) << selectionTimerFourK.report() << " " << std::setw(5) << selectionTimerFiveK.report() << " " << std::setw(5) << selectionTimerSixK.report() << std::endl;
	std::cout << "\n______________________________ time in clock ticks" << std::endl;
	std::cout << "\n\n";
	std::cout << "________________ Search Results __________________\n" << std::endl;
	std::cout << "   Linear => Search time: " << linearSearchTimer.report() << std::endl;
	std::cout << "             Avg probes: " << linearProbeAvg << std::endl;
	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << "   Binary => Search time: " << binarySearchTimer.report() << std::endl;
	std::cout << "             Avg probes: " << binaryProbeAvg << std::endl;
	std::cout << "\n___________________________________ using 6k Array" << std::endl;
	std::cout << std::endl;

	return 0;
}