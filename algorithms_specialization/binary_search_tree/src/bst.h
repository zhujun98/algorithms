//
// Created by jun on 9/12/17.
//

#ifndef BST_BST_H
#define BST_BST_H

#include <iostream>


template <class Key, class Value>
struct Node {
  Key key;
  Value value;
  Node *right;
  Node *left;

  // constructor
  Node(Key key, Value value, Node* left=nullptr, Node* right=nullptr)
  {
    this->key = key;
    this->value = value;
    this->right = right;
    this->left = left;
  }

  // destructor
  ~Node()
  {
    delete left;
    delete right;
  }

};


template <class Key, class Value>
class bst {

public:
  using KeyValuePair = std::pair<Key, Value>;

  /**
   * constructor
   */
  bst():root_(nullptr) {}

  /**
   * destructor
   */
  ~bst() { delete root_; }

  /**
   * Insert a (key, value) pair
   *
   * @param kv_pair: (key, value) pair
   */
  void insert(KeyValuePair kv_pair)
  {
    auto new_node = new Node<Key, Value>(kv_pair.first, kv_pair.second);
    Node<Key, Value>* y = nullptr;
    auto x = root_;
    while (x != nullptr)
    {
      y = x;
      if (kv_pair.first < x->key)
      {
        x = x->left;
      }
      else
      {
        x = x->right;
      }
    }

    if (y == nullptr)
    {
      root_ = new_node;
    }
    else if (new_node->key < y->key)
    {
      y->left = new_node;
    }
    else
    {
      y->right = new_node;
    }
  }

  /**
   * Find the node with the given key
   *
   * @param key: node key
   * @return: a pair of (key, value)
   */
  KeyValuePair find(Key key) const
  {
    auto x = _find(root_, key);

    if (x == nullptr)
    {
      throw std::invalid_argument("Not found: key");
    }

    return std::make_pair(x->key, x->value);
  }

  /**
   * Print out the tree in order
   */
  void inorderTreeWalk() const
  {
    std::cout << "In-order tree walk: " << std::endl;
    inorderTreeWalk(root_);
  }

  /**
   * Find the node with the minimum key
   *
   * @return: a pair of (key, value)
   */
  KeyValuePair min() const
  {
    auto x = _min(root_);
    return std::make_pair(x->key, x->value);
  }

  /**
   * Find the node with the maximum key
   *
   * @return: a pair of (key, value)
   */
  KeyValuePair max() const
  {
    auto x = _max(root_);

    return std::make_pair(x->key, x->value);
  }

  /**
   * Find the node whose key is the successor of the node with the
   * given key in sorted order.
   *
   * @param key: node key
   * @return: a pair of (key, value)
   */
  KeyValuePair successor(Key key) const
  {
    auto x = _successor(key);
    if (x == nullptr)
    {
      throw std::invalid_argument("Successor is NULL");
    }

    return std::make_pair(x->key, x->value);
  }

  /**
   * Find the node whose key is the predecessor of the node with the
   * given key in sorted order.
   *
   * @param key: node key
   * @return: a pair of (key, value)
   */
  KeyValuePair predecessor(Key key) const
  {
    auto x = _predecessor(key);
    if (x == nullptr)
    {
      throw std::invalid_argument("predecessor is NULL");
    }

    return std::make_pair(x->key, x->value);
  }

  /**
   * Delete the node with the given key in a tree (sub-tree) rooted
   * at the given node.
   *
   * @param key: key value
   */
  void erase(Key key)
  {
    _erase(root_, key);
  }

  /**
   * Get the root node
   *
   * @return: root node
   */
  Node<Key, Value>* getRoot() const { return root_; };

private:

  Node<Key, Value>* root_; // root node

  /**
   * Print out the sub-tree from a given node
   *
   * @param node: tree node
   */
  void inorderTreeWalk(Node<Key, Value>* node) const
  {
    auto x = node;
    if (x != nullptr)
    {
      inorderTreeWalk(x->left);
      std::cout << "key = " << x->key << ", "
                << "value = " << x->value << std::endl;
      inorderTreeWalk(x->right);
    }
  }

  /**
   * Find the node with the given key in the sub-tree rooted at a
   * given node.
   *
   * @param node: tree node
   * @param key: key value
   * @return: node with the given key if found, otherwise nullptr
   */
  Node<Key, Value>* _find(Node<Key, Value>* node, Key key) const
  {
    auto x = node;
    while (x != nullptr && x->key != key)
    {
      if (key < x->key)
      {
        x = x->left;
      }
      else
      {
        x = x->right;
      }
    }

    return x;
  }

  /**
   * Find the node of the subtree rooted at the given node with the
   * minimum key.
   *
   * @return: node with the minimum key
   */
  Node<Key, Value>* _min(Node<Key, Value>* node) const
  {
    auto x = node;
    while (x->left != nullptr) { x = x->left; }

    return x;
  }

  /**
   * Find the node of the subtree rooted at the given node with the
   * maximum key.
   *
   * @return: node with the maximum key
   */
  Node<Key, Value>* _max(Node<Key, Value>* node) const
  {
    auto x = node;
    while (x->right != nullptr) { x = x->right; }

    return x;
  }

  /**
   * Find the node whose key is the successor of the node with the
   * given key in sorted order.
   *
   * @return: successor node
   */
  Node<Key, Value>* _successor(Key key) const
  {
    Node<Key, Value>* scsr = nullptr;
    auto x = root_;
    while (x != nullptr && x->key != key)
    {
      if (key > x->key)
      {
        x = x->right;
      }
      else
      {
        scsr = x;
        x = x->left;
      }
    }

    if (x == nullptr) { throw std::invalid_argument("Invalid key!"); }

    if (x->right != nullptr) { scsr = _min(x->right); }

    return scsr;
  }

  /**
   * Find the node whose key is the predecessor of the node with the
   * given key in sorted order.
   *
   * @return: predecessor node
   */
  Node<Key, Value>* _predecessor(Key key) const
  {
    Node<Key, Value>* pdsr = nullptr;
    auto x = root_;
    while (x != nullptr && x->key != key)
    {
      if (key > x->key)
      {
        pdsr = x;
        x = x->right;
      }
      else
      {
        x = x->left;
      }
    }

    if (x == nullptr) { throw std::invalid_argument("Invalid key!"); }

    if (x->left != nullptr) { pdsr = _max(x->left); }

    return pdsr;
  }

  /**
   * Delete the node with the given key in a tree (sub-tree) rooted
   * at the given node.
   *
   * @param root: root node
   * @param key: key value
   * @return: new root node
   */
  Node<Key, Value>* _erase(Node<Key, Value>* root, Key key)
  {
    // base case
    if (root == nullptr) { return nullptr; }

    // recursive call until find the node with the given key
    if (key > root->key)
    {
      root->right = _erase(root->right, key);
    }
    else if (key < root->key)
    {
      root->left = _erase(root->left, key);
    }
    else // key == root->key
    {
      if (root->left == nullptr)
      {
        auto tmp = root->right;
        delete root;
        return tmp;
      }

      if (root->right == nullptr)
      {
        auto tmp = root->left;
        delete root;
        return tmp;
      }

      // Have two non-empty child nodes

      // Find the in-order successor
      auto scsr = _min(root->right);

      // change the key and value of the root
      root->key = scsr->key;
      root->value = scsr->value;

      // delete the in-order successor
      root->right = _erase(root->right, scsr->key);

    }

    return root;
  }

};


#endif //BST_BST_H
