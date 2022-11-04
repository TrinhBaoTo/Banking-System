#include <string>

#include "bstree.h"

using namespace std;

// Create BST
BSTree::BSTree() = default;

// Delete all nodes in BST
BSTree::~BSTree() { clear(); }

// Insert new account
bool BSTree::insert(Account *account) {

  // Check if there's no account in thr Tree
  if (isEmpty()) {

    // Root is now the Node with the new Account
    root = new Node();

    root->account = account;
    root->left = nullptr;
    root->right = nullptr;

    // Insert success
    return true;
  }

  // 2 pointer point to current and previous Node
  Node *current = root;
  Node *prev = root;

  // Traverse the Tree with the current pointer when it's not nullptr
  while (current != nullptr) {

    // Set new previous pointer Node = to current pointer Node before continue
    // to traverse
    prev = current;

    // --------- Already checked if existed in the retrive function
    // if (*account == *(current->account)) {
    //   return false;
    // }

    // Go to the left if the account to be added smaller than the current
    // account
    if (*account < *(current->account)) {

      current = current->left;

      // Go to the right if the account to be added larger than the current
      // account
    } else {

      current = current->right;
    }
  }

  // By the end of while loop, current pointer= nullptr
  // previous pointer points to the last node

  // Add new Node to the left if the account to be added smaller than the last
  // account
  if (*(prev->account) > *account) {

    prev->left = new Node();

    prev->left->account = account;
    prev->left->left = nullptr;
    prev->left->right = nullptr;

    // Add new Node to the right if the account to be added larger than the last
    // account
  } else {

    prev->right = new Node();

    prev->right->account = account;
    prev->right->left = nullptr;
    prev->right->right = nullptr;
  }

  // Insert success
  return true;
}

// Retrieve account
// returns true if successful AND *Account points to account
bool BSTree::retrieve(const int &accountNumber, Account *&account) const {

  Node *current = root;

  // Traverse the Tree with the current pointer when it's not nullptr
  while (current != nullptr) {

    // If the account is found, account pointer point to the account
    if (current->account->getID() == accountNumber) {

      account = current->account;

      return true;
    }

    // Go to the left if the account to be added smaller than the current
    // account
    if (current->account->getID() > accountNumber) {

      current = current->left;

      // Go to the right if the account to be added larger than the current
      // account
    } else {

      current = current->right;
    }
  }

  // If cannot be fouind after the loop, account pointer == nullptr
  account = nullptr;

  return false;
}

// Display information on all accounts
void BSTree::display() const {

  cout << "Processing Done. Final Balances." << endl;

  // Call helper function
  displayR(root);

  cout << "Process finished with exit code 0" << endl;
}

// HELPER function for display method
void BSTree::displayR(Node *node) const {

  // Finish when pointer == nullptr
  if (node == nullptr) {
    return;
  }

  // Display Nodes to the left of the Node
  displayR(node->left);

  // Display the Node
  cout << *(node->account) << endl;

  // Display Nodes to the right of the Node
  displayR(node->right);
}

// delete all information in AccountTree
void BSTree::clear() {

  // Call helper function
  clearR(root);
}

// _____ HELPER function for clear method
void BSTree::clearR(Node *node) {

  // Nothing to be clear with nullptr
  if (node == nullptr) {
    return;
  }

  // Clear the left and right of the Node
  clearR(node->left);
  clearR(node->right);

  // Clear the node
  delete node->account;
  delete node;

  node = nullptr;
}

// check if tree is empty
bool BSTree::isEmpty() const { return root == nullptr; }
