// CS318 - Linked Lists
// Jason Jendro

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>

class LListRec { // this is a double linked list, I added the prev field so I could figure out how to do it
	public:
		int value;
		int count;
		LListRec *next;
		LListRec *prev;
		LListRec() { // I added a default constructor so I didn't have to initialize in the newNode() function
			next = NULL;
			prev = NULL;
			value = 0;
			count = 1;
		}
};

typedef LListRec *Node; // Nodes are pointer variables to LListRec objects
Node LIST_HEAD;  // global for tracking list head

Node newNode() {
	return new LListRec();  // You have to use the struct name here and not the sugar
}

void insert(int v) { // inserts each value in order, does not increment counter
	Node	c = NULL,
			p = NULL, 
			temp = NULL;

	if (LIST_HEAD == NULL) { // first item in list               
		LIST_HEAD = newNode();
		LIST_HEAD->value = v;
	}
	else {
		c = LIST_HEAD;
		while (c != NULL && v > c->value) {
			p = c;
			c = c->next;
		} 
		// loop has fallen out, temp = address of new LListRec, p = the address to insert temp after, c = address to insert temp before
		if (c == LIST_HEAD) { // new item needed at the beggining of list, also LIST_HEAD needs to be reassigned
			temp = newNode();
			temp->value = v;
			LIST_HEAD = temp;
			temp->next = c;
			c->prev = temp;
		}
		else if (c == NULL) { // new item needed at end of list
			temp = newNode();
			temp->value = v;
			p->next = temp;
			temp->prev = p;
		}
		else { // new item needed in between two items, link up between p and c
			temp = newNode();
			temp->value = v;
			p->next = temp;
			temp->next = c;
			temp->prev = p;
			c->prev = temp;
		}
	}
}

void insertOrCount(int v) { // inserts only new values, if value is already present, does not create node, simply increments counter
	Node	c = NULL,
			p = NULL,
			temp = NULL,
			comp = LIST_HEAD; // used to check for duplicates
	bool insertThis = true;

	if (LIST_HEAD == NULL) { // first item in list               
		LIST_HEAD = newNode();
		LIST_HEAD->value = v;
	}
	else {
		c = LIST_HEAD;

		while (comp) { // check for any duplicates
			if (comp->value == v) {
				insertThis = false;
				comp->count++;
			}
			comp = comp->next;
		}

		while (c != NULL && v > c->value) {
			p = c;
			c = c->next;
		}

		// loop has fallen out, temp = address of new LListRec, p = the address to insert temp after, c = address to insert temp before
		if (c == LIST_HEAD && insertThis) { // new item needed at the beggining of list, also LIST_HEAD needs to be reassigned
			temp = newNode();
			temp->value = v;
			LIST_HEAD = temp;
			temp->next = c;
			c->prev = temp;
		}
		else if (c == NULL && insertThis) { // new item needed at end of list
			temp = newNode();
			temp->value = v;
			p->next = temp;
			temp->prev = p;
		}
		else { // new item needed in between two items, link up between p and c
			if (insertThis) {
				temp = newNode();
				temp->value = v;
				p->next = temp;
				temp->next = c;
				temp->prev = p;
				c->prev = temp;
			}
		}
	}
}

void printList() {
	Node c;
	c = LIST_HEAD;
	int i = 1;
	while (c) {
		std::cout << c->value << " - " << c->count;
		if (i % 5 == 0) { std::cout << std::endl; }
		else { std::cout << ", "; }
		c = c->next;
		i++;
	}
	std::cout << std::endl;
}

int rng(int min, int max) // returns rand integer between min and max
{
	int rangeVal = (max - min) + 1;
	return (rand() % rangeVal) + min;
}

int main() {
	std::ifstream inFile;
	inFile.open("LinkNbrs.dat");
	if (!inFile) { std::cout << "Error opening file..."; }
	int x; // integer to read in

	/*
	//For testing...
	srand(30);

	for (int i = 1; i <= 10000; i++) {
		int random = rng(0, 50);
		std::cout << random << " ";
		insertOrCount(random);	
	}
	*/
	
	while (inFile >> x) {
		insertOrCount(x);
	}

	std::cout << "Linked List Functions\n\n";
	printList();

	inFile.close();
	return 0;
}
