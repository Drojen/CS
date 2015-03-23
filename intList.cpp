#include "intList.h"

IntList::~IntList() {
	node *c, *temp;
	c = HEAD;
	temp = HEAD;
	while (c != nullptr) {
		c = c->next;
		delete temp;
		temp = c;
	}
}

void IntList::insert(int v) { // values are inserted in ascending order by default
	node	*c = nullptr,
		*p = nullptr,
		*temp = nullptr;

	if (HEAD == nullptr) { // first item in list               
		HEAD = new node();
		TAIL = HEAD;
		HEAD->value = v;
		// increment list size, started the list
		SIZE++;
	}
	else {
		c = HEAD;
		while (c != nullptr && v > c->value) {
			p = c;
			c = c->next;
		}
		// increment list size, something is getting inserted
		SIZE++;
		// loop has fallen out, temp = address of new LListRec, p = the address to insert temp after, c = address to insert temp before
		if (c == HEAD) { // new item needed at the beggining of list, also HEAD needs to be reassigned
			temp = new node();
			temp->value = v;
			HEAD = temp;
			temp->next = c;
			c->prev = temp;
		}
		else if (c == nullptr) { // new item needed at end of list
			temp = new node();
			temp->value = v;
			p->next = temp;
			temp->prev = p;
			TAIL = temp;
		}
		else { // new item needed in between two items, link up between p and c
			temp = new node();
			temp->value = v;
			p->next = temp;
			temp->next = c;
			temp->prev = p;
			c->prev = temp;
		}
	}
}

void IntList::print(int perLine) {
	node *c = HEAD;
	int i = 1;
	while (c) {
		std::cout << c->value;
		if (i % perLine == 0) { std::cout << std::endl; }
		else { std::cout << " "; }
		c = c->next;
		i++;
	}
	std::cout << std::endl;
}

void IntList::printReverse(int perLine) {
	node *c = TAIL;
	int i = 1;
	while (c) {
		std::cout << c->value;
		if (i % perLine == 0) { std::cout << std::endl; }
		else { std::cout << " "; }
		c = c->prev;
		i++;
	}
	std::cout << std::endl;
}

int IntList::getValueAt(int index) {
	node *temp = HEAD;
	int i = 0;
	// includes out of bounds checks
	if (index > SIZE - 1) { // too high, return tail
		return TAIL->value;
	}
	else if (index < 0) { // too low, return head
		return HEAD->value;
	}
	else {
		while (i < index) {
			temp = temp->next;
			i++;
		}
		return temp->value;
	}
}