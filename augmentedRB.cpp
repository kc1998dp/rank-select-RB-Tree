#include "augmentedRB.h"
#include "RBnode.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;


// default constructor that creates an empty tree
AugmentedRB::AugmentedRB() : root(nullptr) {}

// constructor that takes a vector of unsorted #'s as input
// creates an augmented RB-tree with subtree sizes stored at RBnodes 
AugmentedRB::AugmentedRB(const vector<int>& v) : root(nullptr) {
	root = new RBnode(v[0], BLACK); // root is black and has subtree size = 1
	for (size_t i = 1; i < v.size(); ++i) insert(v[i]); // build tree
}

// insert a new node into tree (takes key as input)
void AugmentedRB::insert(int key) {
	RBnode* node = new RBnode(key); // by default, new nodes are red
	insertHelper(root, node); // insert into tree
	insertFix(node); // insertFix/recolor if necessary
}

// delete a node from the tree (takes key as input)
void AugmentedRB::del(int key) {

}

// inorder traversal to print out elements in sorted order
void AugmentedRB::print() const {
	printHelper(root);
}

// reports max depth of tree
void AugmentedRB::depth() const {
	cout << "height:" << depthHelper(root) << endl;
}

// returns node containing minimum key value in subtree rooted at input node
RBnode* AugmentedRB::min(RBnode* node) const {
	if (node) while (node->left) node = node->left;
	return node;
}

// private methods
void AugmentedRB::insertHelper(RBnode* root, RBnode* RBnode) {
	if (!root) return;
	else {
		++root->subtreeSize; // update subtree sizes
		// root has no left child and (RBnode->data < root->data)
		if (!root->left && RBnode->data < root->data) {
			// affix pointers between parent and child
			root->left = RBnode;
			RBnode->parent = root;
		}
		// root has no right child and (RBnode->data > root->data)
		else if (!root->right && RBnode->data > root->data) {
			// affix pointers between parent and child
			root->right = RBnode;
			RBnode->parent = root;
		}
		// root has a left child and (RBnode->data < root->data)
		else if (root->left && RBnode->data < root->data) {
			insertHelper(root->left, RBnode); // recurse left
		}
		// root has a right child and (RBnode->data > root->data)
		else insertHelper(root->right, RBnode); // recurse right
	}
}

void AugmentedRB::printHelper(RBnode* root) const {
	if (!root) return;
	else {
		printHelper(root->left);
		cout << root->data << ' ';
		printHelper(root->right);
	}
}

int AugmentedRB::depthHelper(RBnode* root) const {
	if (!root) return 0;
	else if (!root->left && !root->right) return 0;
	else {
		return 1 + max(depthHelper(root->left), depthHelper(root->right));
	}
}

RBnode* AugmentedRB::find(RBnode* root, int key) {
	if (!root) return nullptr;
	else {
		if (key == root->data) return root;
		else if (key < root->data) return find(root->left, key);
		else return find(root->right, key);
	}
}

void AugmentedRB::transplant(RBnode* u, RBnode* v) {
	/* based on CLRS pseudocode for RB-transplant */
	if (!u->parent) root = v; // u was root
	else if (u == u->parent->left) u->parent->left = v; // u was left child
	else u->parent->right = v; // u was right child

	if (v) v->parent = u->parent;
}

void AugmentedRB::leftRotate(RBnode* subRoot) {
	if (!subRoot) return;
	if (!subRoot->right) return;

	// renaming for clarity
	// (A & B are the focal points of the rotation)
	RBnode* A = subRoot;
	RBnode* B = A->right;
	RBnode* y = B->left;
	RBnode* g = A->parent;

	// affix pointers between parent of subRoot and new subRoot
	if (g) {
		if (A == g->left) g->left = B;
		else g->right = B;
	}

	// rotating and fixing subtree sizes
	B->parent = g;

	if (y && A->left) {
		y->parent = A;
		A->subtreeSize = 1 + A->left->subtreeSize + y->subtreeSize;
	}
	else if (A->left) A->subtreeSize = 1 + A->left->subtreeSize;
	else A->subtreeSize = 1; // A has no children

	if (B->right) B->subtreeSize = 1 + A->subtreeSize + B->right->subtreeSize;

	A->right = y;
	A->parent = B;
	B->left = A;

}

void AugmentedRB::rightRotate(RBnode* subRoot) {
	if (!subRoot) return;
	if (!subRoot->left) return;

	RBnode* A = subRoot->left;
	RBnode* B = subRoot;
	RBnode* y = A->right;
	RBnode* g = B->parent;

	// affix pointers between parent of subRoot and new subRoot 
	if (g) {
		if (B == g->left) g->left = A;
		else g->right = A;
	}
	
	// rotating
	A->parent = g;

	if (y && B->right) {
		y->parent = B;
		B->subtreeSize = 1 + B->right->subtreeSize + y->subtreeSize;
	}
	else if (B->right) B->subtreeSize = 1 + B->right->subtreeSize;
	else B->subtreeSize = 1; // B has no children

	if (A->left) A->subtreeSize = 1 + B->subtreeSize + A->left->subtreeSize;
	else A->subtreeSize = 1 + B->subtreeSize; // A has no left child

	B->left = y;
	A->right = B;
	B->parent = A;
}

void AugmentedRB::insertFix(RBnode* node) {
	/* g(x) = grandparent of x
	   p(x) = parent of x 
	   y(x) = uncle of x
	   x = the input node */

	RBnode* p = nullptr;
	RBnode* g = nullptr;
	RBnode* y = nullptr;

	// continue propagating the red-red violation between x and p(x)
	// to root if necessary 
	while ((node != root) && (node->color == RED) &&
		   (node->parent->color == RED)) {

		p = node->parent;
		g = p->parent;

		// parent(node) is left-child of grandparent(node)
		if (g->left == p) {
			y = g->right;
			// case 1: y is red
			if (y && y->color == RED) {
				g->color = RED;
				p->color = BLACK;
				y->color = BLACK;
				node = g;
			}
			// case 2/3: y is black
			else {
				// case 2: turns into case 3
				if (p->right == node) {
					leftRotate(p);
					node = p;
					p = node->parent;
				}
				// case 3
				rightRotate(g);
				p->color = BLACK;
				g->color = RED;
				node = p;
				if (g == root) {
					root = node;
					root->parent = nullptr;
				}
			}
		}
		// parent(node) is right-child of grandparent(node)
		else {
			y = g->left;
			// case 1: y is red
			if (y && y->color == RED) {
				g->color = RED;
				p->color = BLACK;
				y->color = BLACK;
				node = g;
			}
			// case 2/3: y is black
			else {
				// case 2: turns into case 3
				if (p->left == node) {
					rightRotate(p);
					node = p;
					p = node->parent;
				}
				// case 3
				leftRotate(g);
				p->color = BLACK;
				g->color = RED;
				node = p;
				if (g == root) {
					root = node;
					root->parent = nullptr;
				}
			}
		}
	}
	
	root->color = BLACK;
}

void AugmentedRB::deleteFix(RBnode* node) {
	
}