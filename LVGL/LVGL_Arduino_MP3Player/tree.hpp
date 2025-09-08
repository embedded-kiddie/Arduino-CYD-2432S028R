/*----------------------------------------------------------------------
 * N-ary Tree for directory tree
 * https://www.geeksforgeeks.org/dsa/tree-data-structure/
 * https://www.geeksforgeeks.org/dsa/generic-treesn-array-trees/
 *----------------------------------------------------------------------*/
#ifndef _TREE_HPP_
#define _TREE_HPP_

/*----------------------------------------------------------------------
 * SD file system configuration
 *----------------------------------------------------------------------*/
#include "sdfs.h"
#include "debug.h"
#include <string>
#include <vector>
#include <exception>
#include <assert.h>
#include <string.h>

#define AUDIO_FILE_EXT  {".mp3", ".m4a", ".wav"}
#define IsValidFile(f)  ((f)[0] != '@' && (f)[0] != '.')

/*----------------------------------------------------------------------
 * Class definition
 *----------------------------------------------------------------------*/
class Node {
private:
  static bool m_found;          // node search flag
  static Node *m_found_node;    // node search result
  static std::string m_path;    // file path search result
  static uint32_t n_nodes;      // number of nodes
  static uint32_t n_leafs;      // number of leaf nodes
  static uint32_t n_depth;      // depth of tree
public:
  bool selected;                // selection for playlist
  uint8_t key;                  // a key assigned to each node
  std::string name;             // folder name or file name
  std::vector<Node*> children;  // a set of child nodes

  Node(const char * name) {
    n_nodes++;
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
  const Node * get_found_node(void) {
    return m_found_node;
  }

  // creates a new node and adds it to the set of children
  Node* append(const char * name) {
    Node *node = new Node(name);
    assert(node);
    node->selected = true;
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

  // traverse by preorder
  uint32_t traverse_node(Node *node) {
    uint32_t depth = 0;
    for (auto &n : node->children) {
      if (n->children.size()) {
        uint32_t d = traverse_node(n);
        depth = max(depth, d);
      } else {
        n->key = n_leafs++;
      }
    }
    node->key = n_leafs - 1;
    return depth + 1;
  }

public:
  // create a file tree
  void scan_file(File &dir) {
    n_nodes = n_leafs = 0;
    scan_node(dir, this, true);
    n_depth = traverse_node(this);
  }

  // create a directory tree
  void scan_dir(File &dir) {
    n_nodes = n_leafs = 0;
    scan_node(dir, this, false);
    n_depth = traverse_node(this);
  }

private:
  // find the leaf node with the specified key
  bool find_node(Node * node, int key, bool find_path) {
    for (auto &n : node->children) {
      // within the range ?
      if (n->key >= key) {
        // are there any subtrees?
        if (n->children.size()) {
          if (find_path) {
            m_path.append(n->name).append("/");
          }
          if (find_node(n, key, find_path)) {
            return m_found;
          }
        }
        // found the leaf node
        else {
          DBG_ASSERT(n->key == key);
          if (find_path) {
            m_path.append(n->name);
          }
          m_found = true;
          m_found_node = n;
          return m_found;
        }
      }
    }
    return m_found;
  }

public:
  // find the leaf node with the specified key and returns node / path.
  Node *find_node(int key) {
    m_found = false;
    m_found_node = NULL;
    m_path = "";

    if (find_node(this, key, false)) {
      return m_found_node;
    } else {
      return NULL;
    }
  }

  std::string find_path(int key) {
    m_found = false;
    m_found_node = NULL;
    m_path = this->name;

    if (find_node(this, key, true)) {
      return m_path;
    } else {
      return "";
    }
  }

private:
  void print_node(Node * node, int indent) {
    ++indent;
    for (auto &n : node->children) {
      for (int j = 0; j < indent; j++) { Serial.print("  "); }
      Serial.printf("%3d %s (%d)\n", n->key, n->name.c_str(), n->children.size());
      if (n->children.size()) {
        print_node(n, indent);
      }
    }
  }

public:
  // traverse the tree and print node information
  void print_tree(void) {
    Serial.printf("%3d %s (%d)\n", this->key, this->name.c_str(), this->children.size());
    print_node(this, 0);
  }
};

#endif // _TREE_HPP_