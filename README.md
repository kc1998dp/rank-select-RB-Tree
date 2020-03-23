# rank-select-RB-Tree
dynamic rank selection with O(n) queries after preprocessing data into augmented RB tree with subtree sizes

# The red-black tree implementation currently includes initialization, insertion, balancing (for insertion only), and other small functions
# Finding the rank of an element in the tree is O(logn) using subtrees sizes to compute rank after searching for the key
# The tree can be kept balanced in O(logn) to keep query times at O(logn)
# O(nlogn) preprocessing to construct to the tree

# To be added
- deletion (while updating subtree sizes)
- balancing (for deletion)
- rank selection function
