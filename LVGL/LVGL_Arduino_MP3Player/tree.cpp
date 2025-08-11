/*----------------------------------------------------------------------
 * N-ary Tree for directory tree
 * https://www.geeksforgeeks.org/dsa/tree-data-structure/
 * https://www.geeksforgeeks.org/dsa/generic-treesn-array-trees/
 *----------------------------------------------------------------------*/
#include "tree.hpp"

/*----------------------------------------------------------------------
 * instantiate static member variables
 *----------------------------------------------------------------------*/
bool        Node::found;
std::string Node::path;
uint32_t    Node::n_nodes;
uint32_t    Node::n_leafs;
uint32_t    Node::n_depth;