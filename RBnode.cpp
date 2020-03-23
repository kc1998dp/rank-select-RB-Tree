#include "RBnode.h"

RBnode::RBnode(int data, bool color, int subtreeSize, RBnode* p,
			   RBnode* lc, RBnode* rc)
	: data(data), color(color), subtreeSize(subtreeSize),
	  parent(p), left(lc), right(rc) {}