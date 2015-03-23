// CS318 - Binary Tree
// Jason Jendro

#include <iostream>
#include <fstream>
#include <string>

class IntTree {
	public:
		struct node {
			int value;
			int level;
			node *left;     // less than 
			node *right;	// greater than
			node(int val, int level) : right(nullptr), left(nullptr), value(val), level(level) {}
		};
		node *ROOT;
		int totalNodes;																		// total nodes in the tree
		int totalOfNodes;																	// sum of all node values in the tree
		int totalLevels;																	// total levels in the tree
		IntTree() : ROOT(nullptr), totalNodes(0), totalOfNodes(0), totalLevels(0) {}		// constructor
		~IntTree();																			// destructor
		void insert(int);																	// inserts values in order to form a binary search tree
		void printInOrder(node *);															// in-order printing
		void printPreOrder(node *);															// pre-order printing
		void printPostOrder(node *);														// post-order printing
		void deleteAllNodes(node *);														// called by destructor, uses post-order traversing to delete all nodes from memory
		int getLeaves(node *);																// returns the number of nodes with no children (leaves)
		int getNodesCount(node *);															// recursively counts all nodes in the tree
		int getNodesWithOneChild(node *);													// returns the number of nodes with only one child
		IntTree::node* getDeepestNode(node *, node *);										// returns the address of one node on the deepest level
		void printDeepestNodes(node *);														// prints all values and levels of the node(s) on the deepest level
		void setTotalLevels(int level) {													// updates the totalLevels parameter of the tree if a deeper level was just created
			if (totalLevels < level) {	totalLevels = level; }
		}
		double getAvgOfNodes() {															// returns the average of all the node values in the tree
			return static_cast<double>(totalOfNodes) / totalNodes;
		}
};

IntTree::~IntTree() { 
	deleteAllNodes(ROOT);
}

void IntTree::deleteAllNodes(node *root) { 
	if (root == nullptr) {
		return;
	}
	else {
		deleteAllNodes(root->left);
		deleteAllNodes(root->right);
		delete root;
	}
}

void IntTree::insert(int v) { // values are inserted in ascending order by default
	node	*c = nullptr, // current node
			*p = nullptr; // previous node

	if (ROOT == nullptr) { // first item in list               
		ROOT = new node(v, 1);
		totalNodes++;
		totalOfNodes += v;
		setTotalLevels(1);
	}
	else {
		c = ROOT;
		while (c != nullptr) {
			p = c;
			if (v > c->value) {			// branch right
				c = c->right;
			}
			else if (v < c->value) {	// branch left
				c = c->left;
			}
			else {						// duplicate value, stop, don't add anything
				c = nullptr;
			}
		}
		// out of loop, p should be sitting at the correct parent node to create a leaf now... determine which direction to go
		if (v > p->value) {					// branch right
			p->right = new node(v, p->level + 1);
			setTotalLevels(p->level + 1);
			totalNodes++;					
			totalOfNodes += v;
		}
		else if (v < p->value) {			// branch left
			p->left = new node(v, p->level + 1);
			setTotalLevels(p->level + 1);
			totalNodes++;
			totalOfNodes += v;				
		}
	}
}

void IntTree::printInOrder(node *root) {
	if (root == nullptr) {
		return;
	}
	else {
		printInOrder(root->left);
		std::cout << root->value << " ";
		printInOrder(root->right);
	}
}

void IntTree::printPreOrder(node *root) {
	if (root == nullptr) {
		return;
	}
	else {
		std::cout << root->value << " ";
		printPreOrder(root->left);
		printPreOrder(root->right);
	}
}

void IntTree::printPostOrder(node *root) {
	if (root == nullptr) {
		return;
	}
	else {
		printPostOrder(root->left);
		printPostOrder(root->right);
		std::cout << root->value << " ";
	}
}

void IntTree::printDeepestNodes(node *root) {
	if (root == nullptr) {
		return;
	}
	else {
		printDeepestNodes(root->left);
		printDeepestNodes(root->right);
		if (root->level == totalLevels) {
			std::cout << root->value << " at level " << root->level << "\n";
		}
	}
}

int IntTree::getLeaves(node *root) {
	if (root == nullptr) {	return 0; }
	if (root->left == nullptr && root->right == nullptr) { return 1; }
	else {
		return getLeaves(root->left) + getLeaves(root->right);
	}
}

int IntTree::getNodesWithOneChild(node *root) { 
	if (root == nullptr) { return 0; }
	if ((root->left == nullptr && root->right != nullptr) || (root->left != nullptr && root->right == nullptr)) { return 1; }
	else {
		return getNodesWithOneChild(root->left) + getNodesWithOneChild(root->right);
	}
}

int IntTree::getNodesCount(node *root) {
	int total = 0;
	if (root != nullptr) {
		total = 1 + getNodesCount(root->left) + getNodesCount(root->right);
	}
	return total;
}

IntTree::node* IntTree::getDeepestNode(node *root, node *prev) {
	if (root == nullptr) {
		return prev;
	}
	prev = root;
	node *lResult = getDeepestNode(root->left, prev);
	node *rResult = getDeepestNode(root->right, prev);
	node *result; 
	if (lResult->level < rResult->level) {
		result = rResult;
	}
	else {
		result = lResult;
	}
	if (result == nullptr) {
		result = root;
	}
	return result;
}

int main() {
	IntTree tree;					// our tree
	IntTree::node *deepest;
	std::ifstream inFile;			
	inFile.open("TreeData.dat");
	std::string x;					// string to be read in, will convert to int

	while (inFile >> x) {
		tree.insert(std::stoi(x));	// insert into our tree as an int
	}
	
	inFile.close();					// no longer need the file
	deepest = tree.getDeepestNode(tree.ROOT, nullptr);
	std::cout << "----------================== Binary Tree Fun! ==================----------\n\n";
	std::cout << "In-Order:\n";
	tree.printInOrder(tree.ROOT);
	std::cout << "\n\n";
	std::cout << "Pre-Order:\n";
	tree.printPreOrder(tree.ROOT);
	std::cout << "\n\n";
	std::cout << "Post-Order:\n";
	tree.printPostOrder(tree.ROOT);

	std::cout << "\n\nTotal Nodes: " << tree.getNodesCount(tree.ROOT);
	std::cout << "\n\nAvgerage of Node Values: " << tree.totalOfNodes << " / " << tree.totalNodes << " = " << tree.getAvgOfNodes();
	std::cout << "\n\nTotal Leaves: " << tree.getLeaves(tree.ROOT);
	std::cout << "\n\nTotal Levels in Tree: " << tree.totalLevels;
	std::cout << "\n\nTotal Nodes With One Child: " << tree.getNodesWithOneChild(tree.ROOT);
	std::cout << "\n\nThe Deepest Node(s):\n";
	tree.printDeepestNodes(tree.ROOT);
	std::cout << "\n";	
	std::cout << "In-Order Left Branch:\n";
	tree.printInOrder(tree.ROOT->left);
	std::cout << "\n\n";
	std::cout << "Post-Order Right Branch:\n";
	tree.printPostOrder(tree.ROOT->right);
	std::cout << "\n\n";

	return 0;
}
