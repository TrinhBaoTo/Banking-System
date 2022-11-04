#include <queue>
#include <string>

#include "bstree.h"

#ifndef BANK_H
#define BANK_H

using namespace std;

class Bank {
public:
  // Process the Transaction File
  void processTransactionFile(const string &fileName);

  // Process the Command line
  void processTransaction(const string &transc);

private:
  BSTree accountStorage;
  queue<string> transactions;
};
#endif // BANK_H
