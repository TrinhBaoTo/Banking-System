
#ifndef BSTREE_H
#define BSTREE_H

#include "account.h"
#include <iostream>

using Node = struct Node {
  Account *account;
  Node *right;
  Node *left;
};

class BSTree {
public:
  // Create BST
  BSTree();

  // Delete all nodes in BST
  ~BSTree();

  // Insert new account
  bool insert(Account *account);

  // Retrieve account
  // returns true if successful AND *Account points to account
  bool retrieve(const int &accountNumber, Account *&account) const;

  // Display information on all accounts
  void display() const;

  // _____ HELPER function for display method
  void displayR(Node *node) const;

  // delete all information in AccountTree
  void clear();

  // _____ HELPER function for clear method
  void clearR(Node *node);

  // check if tree is empty
  bool isEmpty() const;

private:
  Node *root = nullptr;
};

#endif // BSTREE_H
