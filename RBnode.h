#ifndef RBnode_H
#define RBnode_H

enum Color { BLACK, RED };

struct RBnode {
	RBnode(int data, bool color = RED, int subtreeSize = 1, RBnode* 
		   p = nullptr, RBnode* lc = nullptr, RBnode* rc = nullptr);

	int data;
	int subtreeSize; // one RBnode has subtree size = 1
	bool color; // true = red, false = black
	RBnode* parent;
	RBnode* left;
	RBnode* right;
};

#endif