/*----------------------------------------------------------------------
 * N-ary Tree for directory tree
 * https://www.geeksforgeeks.org/dsa/tree-data-structure/
 * https://www.geeksforgeeks.org/dsa/generic-treesn-array-trees/
 *----------------------------------------------------------------------*/
#ifndef _TREE_H_
#define _TREE_H_

/*--------------------------------------------------------------------------------
 * SD file system configuration
 *--------------------------------------------------------------------------------*/
#include "sdfs.h"

/*----------------------------------------------------------------------
 * Directory tree
 *----------------------------------------------------------------------*/
#include <string>
#include <vector>
#include <exception>
#include <assert.h>
#include <string.h>

class Node {
private:
  static bool found;
  static std::string path;
  static uint16_t n_leafs;
public:
  uint16_t key;
  std::string name;
  std::vector<Node*> children;

  Node(const char * name) {
    this->name = name;
  }

  ~Node() {
    this->children.clear();
    for (auto &n : this->children) {
      delete n;
    }
    this->children.clear();
    this->name.clear();
  }

  const size_t size(void) {
    return n_leafs;
  }

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

  void scan_dir(File &dir, Node *node) {
    for (File entry = dir.openNextFile(); entry; entry = dir.openNextFile()) {
      if (entry.isDirectory()) {
#ifdef USE_SDFAT
        char buf[BUF_SIZE];
        entry.getName(buf, sizeof(buf));
        if (buf[0] != '@') {
          scan_dir(entry, node->append(buf));
        }
#else
        if (entry.name()[0] != '@') {
          scan_dir(entry, node->append(entry.name()));
        }
#endif
      }
      entry.close();
    }

    std::sort(node->children.begin(), node->children.end(), [](Node *a, Node *b) {
      return a->name.compare(b->name) < 0 ? true : false; // ascending order
    });
  }

private:
  // traverse by preorder
  void traverse_node(Node *node) {
    for (auto &n : node->children) {
      if (n->children.size()) {
        traverse_node(n);
      } else {
        n->key = n_leafs++;
      }
    }
    node->key = n_leafs - 1;
  }

public:
  void scan_dir(File &dir) {
    scan_dir(dir, this);

    n_leafs = 0;
    traverse_node(this);
  }

private:
  bool find_node(Node * node, int key) {
    for (auto &n : node->children) {
      // within the range ?
      if (n->key >= key) {
        // are there any subtrees?
        if (n->children.size()) {
          path.append(n->name).append("/");
          if (find_node(n, key)) {
            return found;
          }
        }
        // found the leaf node
        else {
          path.append(n->name);
          found = true;
          return found;
        }
      }
    }
    return found;
  }

public:
  std::string find(int key) {
    // initialize static variables
    found = false;
    path = this->name;

    if (find_node(this, key)) {
      return path;
    } else {
      return "";
    }
  }

private:
  void print_node(Node * node, int indent) {
    ++indent;
    for (auto &n : node->children) {
      for (int j = 0; j < indent; j++) { printf("  "); }
      printf("%3d %s (%d)\n", n->key, n->name.c_str(), n->children.size());
      if (n->children.size()) {
        print_node(n, indent);
      }
    }
  }

public:
  void print_tree(void) {
    printf("%3d %s (%d)\n", this->key, this->name.c_str(), this->children.size());
    print_node(this, 0);
  }
};

#endif // _TREE_H_