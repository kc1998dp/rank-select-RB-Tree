#ifndef AUGMENTED_RB_H
#define AUGMENTED_RB_H
#include "RBnode.h"
#include <algorithm>
#include <iostream>
#include <vector>


// augmented red-black tree s.t. RBnodes contain subtree sizes
// *note: a single RBnode is considered to have a subtree size = 1
class AugmentedRB {
public:
	AugmentedRB();
	AugmentedRB(const std::vector<int>& v);
	void insert(int key);
	void del(int key);
	void print() const;
	void depth() const;
	RBnode* min(RBnode* node) const;
private:
	RBnode* root;

	void insertHelper(RBnode* root, RBnode* RBnode);
	void printHelper(RBnode* root) const;
	int depthHelper(RBnode* root) const;
	RBnode* find(RBnode* root, int key); // return pointer to the node if found
	void transplant(RBnode* u, RBnode* v); // subroutine for deletion; see CLRS
	void leftRotate(RBnode* subRoot); // used for updating/balancing
	void rightRotate(RBnode* subRoot); // used for updating/balancing
	void insertFix(RBnode* node); // O(logn) balancing to enforce RB properties
	void deleteFix(RBnode* node); // O(logn) balancing to enforce RB properties
};

#endif 