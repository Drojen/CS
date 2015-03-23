// CS318 - Pointer Workout
// Jason Jendro

#include <iostream>
#include <iomanip>
using namespace std;

void table_fill(int *const p_arr, int size, int num) {
	int *i_ptr = p_arr;
	int *end_ptr = p_arr + size;

	for (; i_ptr < end_ptr; i_ptr++) {
		*i_ptr = num;
	}
}

void table_print(int *const p_arr, int size) {
	int *i_ptr = p_arr;
	int *end_ptr = p_arr + size;

	for (; i_ptr < end_ptr; i_ptr++) {
		cout << *i_ptr;
		if (i_ptr + 1 == end_ptr) { cout << " "; }
		else { cout << ", "; }
	}
}

void table_print_rev(int *const p_arr, int size) {
	int *i_ptr = p_arr + (size - 1);
	int *end_ptr = p_arr;

	for (; i_ptr >= end_ptr; i_ptr--) {
		cout << *i_ptr;
		if (i_ptr == end_ptr) { cout << " "; }
		else { cout << ", "; }
	}
}

void table_add1(int *const p_arr, int size) {
	int *i_ptr = p_arr;
	int *end_ptr = p_arr + size;

	for (; i_ptr < end_ptr; i_ptr++) {
		*i_ptr += 1;
	}
}

void table_addv(int *const p_arr, int size, int val) {
	int *i_ptr = p_arr;
	int *end_ptr = p_arr + size;

	for (; i_ptr < end_ptr; i_ptr++) {
		*i_ptr += val;
	}
}

int table_max(int *const p_arr, int size) {
	int *i_ptr = p_arr;
	int *end_ptr = p_arr + size;
	int max = *i_ptr;

	for (; i_ptr < end_ptr; i_ptr++) {
		max = (*i_ptr > max) ? *i_ptr : max;
	}

	return max;
}

int table_min(int *const p_arr, int size) {
	int *i_ptr = p_arr;
	int *end_ptr = p_arr + size;
	int min = *i_ptr;

	for (; i_ptr < end_ptr; i_ptr++) {
		min = (*i_ptr < min) ? *i_ptr : min;
	}

	return min;
}

float table_avg(int *const p_arr, int size) {
	int *i_ptr = p_arr;
	int *end_ptr = p_arr + size;
	float total = 0.0;

	for (; i_ptr < end_ptr; i_ptr++) {
		total += *i_ptr;
	}

	return total / size;
}

int table_find(int *const p_arr, int size, int val) {
	int *i_ptr = p_arr;
	int *end_ptr = p_arr + size;
	int index = 0;

	for (; i_ptr < end_ptr; i_ptr++) {
		if (*i_ptr == val) {
			return index;
		}
		index++;
	}

	return -1;
}

int main()
{
	const int Max = 20;
	int ary[Max];
	int bry[Max];
	int *p, *s, *tp;

	p = &ary[0];
	s = &bry[0];

	table_fill(p, Max, 20);
	cout << endl << "Fill array with 20s " << endl;
	table_print(p, Max);  cout << endl << endl;

	
	cout << endl << "Add 1 to first 10 elements " << endl;
	table_add1(p, 10);
	table_print(p, Max);  cout << endl << endl;

	tp = s;   // save pointer
	for (int i = 1; i <= Max; i++)
	{
		table_fill(s, 1, i);
		s++;
	}
	cout << endl << "Fill array with 1 to 20 " << endl;
	s = tp;   // restore pointer
	table_print(s, Max);  cout << endl << endl;

	cout << endl << "Print reverse order " << endl;
	table_print_rev(s, Max);  cout << endl << endl;

	table_fill(p, Max, 0);
	cout << endl << "Zero out array " << endl;
	table_print(p, Max);  cout << endl << endl;



	s = tp;        // What's happening here? Answer p1: s is back at the beginning of bry[]
	for (int i = Max; i >= 0; i--) // Answer p2: The array starts out 1 thur 20. This is effectively adding one to element 20, 2 to 19, 3 to 18 ... till it adds 20 to element 1, making everything 21
	{
		table_add1(s, i);
	}

	cout << endl << "Fill array with ???? " << endl;
	table_print(s, Max);  cout << endl << endl;

	cout << endl << "Print reverse order " << endl;
	table_print_rev(s, Max);  cout << endl << endl;

	for (int i = 0; i<Max / 2; i++)
	{
		tp = p + 10 + i;
		table_fill(tp, 1, i * 2);
		tp = p + 10 - i;
		table_fill(tp, 1, i * 3);
	}

	cout << endl << "Fill array with <-> " << endl;
	tp = p + 1;
	table_print(p, Max);  cout << endl << endl;



	cout << endl << "Min for previous table " << table_min(p, 12);
	cout << endl << "Max for previous table " << table_max(p + 10, 9);
	cout << endl << "Max for previous table " << table_max(p + 10, 3);
	cout << endl << "Average for previous table " << table_avg(p, Max);
	cout << endl << "Average for previous table " << table_avg(p, 10);
	cout << endl << "Average for previous table " << table_avg(p + 10, 10);
	cout << endl << endl;

	s = &ary[0];
	p = &bry[0];
	tp = s;             // save pointer
	for (int i = 1; i <= Max; i++)
	{
		table_fill(s, 1, i);
		table_fill(p, 1, i);
		s++; p++;
	}
	s = &ary[0];
	p = &bry[0];
	cout << " new p & s array " << endl;
	table_print(p, Max);  cout << endl << endl;
	table_print(s, Max);  cout << endl << endl;


	s = tp;
	for (int i = 1; i <= Max; i++)
	{
		tp = s + i - 1;
		table_fill(tp, 1, table_find(s, Max, i) * 100);
	}
	table_print(s, Max);  cout << endl << endl;

	p = &bry[0];
	for (int i = 0; i<Max; i++)
	{
		table_addv(p, 1, rand() % 33);
		p++;
	}

	cout << endl << "Add Val array with a val? " << endl;
	p = &bry[0];
	table_print(p, Max);  cout << endl << endl;

	cout << "   That's all Folks " << endl;


	return 0;

}