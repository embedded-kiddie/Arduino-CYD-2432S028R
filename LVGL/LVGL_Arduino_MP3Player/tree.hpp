//================================================================================
// N-ary Tree for directory tree
// https://www.geeksforgeeks.org/dsa/tree-data-structure/
// https://www.geeksforgeeks.org/dsa/generic-treesn-array-trees/
//================================================================================
#ifndef _TREE_HPP_
#define _TREE_HPP_

//----------------------------------------------------------------------
// SD file system configuration
//----------------------------------------------------------------------
#include "sdfs.h"
#include "debug.h"
#include <string>
#include <vector>
#include <exception>
#include <assert.h>
#include <string.h>

#define AUDIO_FILE_EXT  {".m4a", ".mp3", ".wav"}
#define IsValidFile(f)  ((f)[0] != '@' && (f)[0] != '.')

//----------------------------------------------------------------------
// Meta information for Node class
//----------------------------------------------------------------------
#define TYPE_NODE   0 // typically "folder"
#define TYPE_LEAF   1 // typically "file"

// States of Node and Leaf
#define NODE_HIDDEN     true  // for 'bool hidden'
#define NODE_REVEALED   false // for 'bool hidden'
#define NODE_FOLDED     true  // for 'bool checked'
#define NODE_UNFOLDED   false // for 'bool checked'
#define LEAF_SELECTED   true  // for 'bool checked'
#define LEAF_UNSELECTED false // for 'bool checked'

typedef struct {
  uint8_t depth    : 4;         // hierarchy depth in N-ary tree
  uint8_t type     : 1;         // 0: folder node, 1: leaf node
  bool    hidden   : 1;         // true: hidden, false: displayed
  bool    checked  : 1;         // true: folded (folder node) / selected (leaf node)
  bool    spare    : 1;         // spare
} NodeMeta_t;

//----------------------------------------------------------------------
// Class definition
//----------------------------------------------------------------------
class Node {
private:
  static bool m_found;          // node search flag
  static Node *m_found_node;    // node search result
  static std::string m_path;    // file path search result
  static uint32_t n_nodes;      // number of nodes
  static uint32_t n_leafs;      // number of leaf nodes
  static uint32_t n_depth;      // depth of tree
public:
  uint8_t key;                  // a key assigned to each node
  NodeMeta_t meta;              // information for album list
  uint16_t n_files;             // number of audio files
  std::string name;             // folder name or file name
  std::vector<Node*> children;  // a set of child nodes

  Node(const char * name) {
    n_nodes++;
    this->meta = {0,};
    this->n_files = 0;
    this->name = name;
  }

  ~Node() {
    for (auto &n : this->children) {
      delete n;
    }
    this->children.clear();
    this->name.clear();
  }

  // number of nodes / leaf nodes / depth
  const uint32_t get_n_nodes(void) {
    return n_nodes;
  }
  const uint32_t get_n_leafs(void) {
    return n_leafs;
  }
  const uint32_t get_n_depth(void) {
    return n_depth;
  }
  Node * get_node(void) {
    return m_found_node;
  }

  // creates a new node and adds it to the set of children
  Node* append(const char * name) {
    Node *node = new Node(name);
    assert(node);
    try {
      this->children.push_back(node);
    } catch (const std::exception &e) {
      assert(false); //  e.what()
    }
    return node;
  }

private:
  // check the file extension
  bool check_ext(const char *path) {
    const char* ext[] = AUDIO_FILE_EXT;
    for (int i = 0; i < sizeof(ext) / sizeof(ext[0]); i++) {
      if (strcmp(&path[strlen(path) - strlen(ext[i])], ext[i]) == 0) {
        return true;
      }
    }
    return false;
  }

  // traversing the file system
  void scan_node(File &dir, Node *node, bool scan_file) {
    for (File entry = dir.openNextFile(); entry; entry = dir.openNextFile()) {
#ifdef USE_SDFAT
      char buf[BUF_SIZE];
      entry.getName(buf, sizeof(buf));
      const char *name = buf;
#else
      const char *name = entry.name();
#endif
      if (IsValidFile(name)) {
        if (entry.isDirectory()) {
          scan_node(entry, node->append(name), scan_file);
        }
        else if (scan_file && check_ext(name)) {
          node->append(name);
        }
      }
      entry.close();
    }

    // Sort child nodes in ascending order
    std::sort(node->children.begin(), node->children.end(), [](Node *a, Node *b) {
      return a->name.compare(b->name) < 0 ? true : false;
    });
  }

  // traverse and assign keys similar to post-order
  // e.g.      root
  //    ┌───────┼─────────┐
  //    1       3         8
  //  ┌─┴─┐   ┌─┴─┐   ┌───┴───┐
  //  0   1   2   3   5       8
  //                ┌─┴─┐  ┌──┼──┐
  //                4   5  6  7  8
  uint32_t traverse_node(Node *node, uint32_t depth = 1) {
    for (auto &n : node->children) {
      if (n->meta.depth == 0) {
        n->meta.depth   = depth;
        n->meta.hidden  = true;
        n->meta.checked = true;
      }

      if (n->children.size()) {
        uint32_t d = traverse_node(n, depth + 1);
        n_depth = max(n_depth, d);
        n->meta.type = TYPE_NODE;
      } else {
        n->key = n_leafs++;
        n->meta.type = TYPE_LEAF;
      }
    }

    // set the leaf node number to the parent
    node->key = n_leafs - 1;
    return depth;
  }

  // traverse and assign keys by pre-order
  // e.g.      root
  //    ┌───────┼─────────┐
  //    0       3         6
  //  ┌─┴─┐   ┌─┴─┐   ┌───┴───┐
  //  1   2   4   5   7       10
  //                ┌─┴─┐  ┌──┼──┐
  //                8   9  11 12 13
  void traverse_preorder(Node *node, uint32_t depth) {
    for (auto &n : node->children) {
      n->key = n_nodes++;
      traverse_preorder(n, depth + 1);
    }
  }

public:
  uint32_t traverse_node(void) {
    n_leafs = n_depth = 0;
    traverse_node(this);
    return n_nodes;
  }

  uint32_t traverse_preorder(void) {
    n_nodes = 0;
    traverse_preorder(this, 1);
    return n_nodes;
  }

  // create a file tree
  void scan_file(File &dir) {
    n_nodes = n_leafs = n_depth = 0;

    scan_node(dir, this, true);
    traverse_node(this);

    this->key = n_leafs;
    this->meta = { 0, TYPE_NODE, false, false, false }; // depth, type, hidden, checked, spare
  }

  // create a directory tree
  void scan_dir(File &dir) {
    n_nodes = n_leafs = n_depth = 0;

    scan_node(dir, this, false);
    traverse_node(this);

    this->key = n_leafs;
    this->meta = { 0, TYPE_NODE, false, false, false }; // depth, type, hidden, checked, spare
  }

private:
  // find the leaf node with the specified key
  bool find_node(Node * node, int key) {
    for (auto &n : node->children) {
      // within the range ?
      if (n->key >= key) {
        // are there any subtrees?
        if (n->children.size()) {
          m_path.append(n->name).append("/");
          if (find_node(n, key)) {
            return m_found;
          }
        }
        // found the leaf node
        else {
          DBG_ASSERT(n->key == key);
          m_path.append(n->name);
          m_found = true;
          m_found_node = n;
          return m_found;
        }
      }
    }
    return m_found;
  }

  // find the node/leaf with the specified key
  Node *find_preorder(Node * node, int key) {
    const int N = node->children.size();
    for (int i = N - 1; i >= 0; i--) {
      Node *n = node->children[i];
      if (n->key == key) {
        m_found_node = node;  // parent node
        return n;             // found node
      }
      else if (n->key < key) {
        if (n = find_preorder(n, key)) {
          return n;
        }
      }
    }
    return NULL;
  }

public:
  // find the leaf node with the specified key and returns node / path.
  Node *find_node(int key) {
    m_found = false;
    m_found_node = NULL;
    m_path = this->name;

    find_node(this, key);
    return m_found_node;
  }

  std::string find_path(int key) {
    m_found = false;
    m_found_node = NULL;
    m_path = this->name;

    find_node(this, key);
    return m_path; // without trailing slash
  }

  // find the node/leaf with the specified key
  Node *find_preorder(int key) {
    return find_preorder(this, key);
  }

private:
  void print_node(Node *node) {
    Serial.printf("key:%3d, size:%2d, depth:%d, type:%d, hidden:%d, checked:%d %s\n",
                  node->key, node->children.size(), node->meta.depth, node->meta.type,
                  node->meta.hidden, node->meta.checked, node->name.c_str());
  }

  void print_nodes(Node * node, int indent = 0) {
    ++indent;
    for (auto &n : node->children) {
      for (int j = 0; j < indent; j++) { Serial.print("  "); }
      print_node(n);
      if (n->children.size()) {
        print_nodes(n, indent);
      }
    }
  }

public:
  // traverse the tree and print node information
  void dump_tree(void) {
    print_node(this);
    print_nodes(this);
    Serial.printf("n_nodes: %d, n_leaf: %d, n_depth: %d\n", n_nodes, n_leafs, n_depth);
  }

  void dump_path(void) {
    for (int i = 0; i < n_leafs; i++) {
      if (find_node(i)) {
        Serial.printf("key: %d, path: %s\n", i, m_path.c_str());
      }
    }
  }

  void dump_preorder(bool all = false) {
    traverse_preorder();
    //dump_tree();
    //print_node(this);
    for (int i = 0; i < n_nodes; i++) {
      Node *n = find_preorder(i);
      Node *p = m_found_node; // parent node
      DBG_ASSERT(n);
      if (all || p->meta.checked == false) {
        print_node(n);
      }
    }
  }
};

#endif // _TREE_HPP_