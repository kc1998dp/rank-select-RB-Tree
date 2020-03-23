#include "augmentedRB.h"
#include "RBnode.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// dynamic rank selection


int main() {
	vector<int> v;
	for (int i = 1; i <= 10; ++i) v.push_back(i);
	random_shuffle(v.begin(), v.end());

	AugmentedRB rb(v);
	rb.print();
}