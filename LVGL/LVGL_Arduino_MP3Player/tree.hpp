/*----------------------------------------------------------------------
 * N-ary Tree for directory tree
 * https://www.geeksforgeeks.org/dsa/tree-data-structure/
 * https://www.geeksforgeeks.org/dsa/generic-treesn-array-trees/
 *----------------------------------------------------------------------*/
#ifndef _TREE_H_
#define _TREE_H_

/*--------------------------------------------------------------------------------
 * SD library
 *--------------------------------------------------------------------------------*/
#include "sdfs.h"

/*----------------------------------------------------------------------
 * Directory tree
 *----------------------------------------------------------------------*/
#include <string>
#include <vector>
#include <exception>
#include <assert.h>

class Node {
private:
  static bool found;
  static std::string path;
  static uint16_t n_leafs;
public:
  uint16_t id;
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
    this->name.clear();
  }

public:
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
  // traverse by preorder
  void traverse_node(Node *node) {
    for (auto &n : node->children) {
      if (n->children.size()) {
        traverse_node(n);
      } else {
        n->id = n_leafs++;
      }
    }
    node->id = n_leafs - 1;
  }

public:
  void traverse() {
    n_leafs = 0;
    traverse_node(this);
  }

  const size_t size(void) {
    return n_leafs;
  }

private:
  void sort_node(Node *node) {
    std::sort(node->children.begin(), node->children.end(), [](Node *a, Node *b) {
      return a->name.compare(b->name) < 0 ? true : false; // ascending order
    });
    for (auto &n : node->children) {
      if (n->children.size() > 1) {
        sort_node(n);
      }
    }
  }

public:
  void sort(void) {
    if (this->children.size() > 1) {
      sort_node(this);
    }
  }

public:
  void scan_dir(File &dir, Node *node) {
    while (true) {
      File entry = dir.openNextFile();
      if (!entry) {
        break;
      }
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
  }

public:
  void scan_dir(File &dir) {
    scan_dir(dir, this);
  }

private:
  bool find_node(Node * node, int id) {
    for (auto &n : node->children) {
      // within the range ?
      if (n->id >= id) {
        // are there any subtrees?
        if (n->children.size()) {
          path.append(n->name).append("/");
          if (find_node(n, id)) {
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
  std::string find(int id) {
    // initialize static variables
    found = false;
    path = this->name;

    if (find_node(this, id)) {
      return path;
    } else {
      return "";
    }
  }

private:
  void print_node(Node * node, int i) {
    ++i;
    for (auto &n : node->children) {
      for (int j = 0; j < i; j++) printf("  ");
      printf("%d %s (%d)\n", n->id, n->name.c_str(), n->children.size());
      if (n->children.size()) {
        print_node(n, i);
      }
    }
  }

public:
  void print_tree(void) {
    printf("%d %s (%d)\n", this->id, this->name.c_str(), this->children.size());
    print_node(this, 0);
  }
};

#endif // _TREE_H_