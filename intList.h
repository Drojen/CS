#ifndef __INTLIST_H__
#define __INTLIST_H__

// dependencies
#include <iostream>

class IntList { // I encapsulated the linked list code that was made for the previous linked list program so I could reuse it without globals. I also added a few things
private:
	struct node {
		int value;
		node *next;
		node *prev;
		node() : next(nullptr), prev(nullptr), value(0) {}
	};
	node *HEAD;
	node *TAIL;
	int SIZE;
public:
	IntList() {
		HEAD = nullptr;
		TAIL = nullptr;
		SIZE = 0;
	}
	~IntList();

	void insert(int);					// inserts value in ascending order
	void print(int);					// prints all values with cout
	void printReverse(int);				// reverse prints all values
	int getSize() { return SIZE; };		// returns size of list
	int getValueAt(int);				// returns value from list at index given like an array, cannot go out of bounds
};

#endif