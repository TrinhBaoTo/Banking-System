#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>

#include "bank.h"

using namespace std;

// Process the Transaction File
void Bank::processTransactionFile(const string &fileName) {

  // Create InputFileStream
  ifstream transactionFile;

  // Open file
  transactionFile.open(fileName);

  // Check if the filr is open
  if (transactionFile.is_open()) {

    // Innitialize transaction command
    string transc;

    // Read file line by line

    while (getline(transactionFile, transc)) {

      // and push into a queue
      transactions.push(transc);
    }

    // Process the Commands stored in queue
    while (!transactions.empty()) {

      // Check the command and process
      processTransaction(transactions.front());

      // Take the command out of the queue after finish
      transactions.pop();
    }

    cout << endl;

    // Display the Accounts
    accountStorage.display();
  }

  // Close file
  transactionFile.close();
}

// Process the Command line
void Bank::processTransaction(const string &transc) {

  // A stringstream tbreak down each command.
  stringstream strStrm(transc);

  // First evaluate the Command type
  char cType;

  strStrm >> cType;

  // If the command is OPEN new account
  if (cType == 'O') {

    // Take in the first name, last name and the ID for the new account
    string firstName;
    string lastName;
    int iD;

    strStrm >> firstName >> lastName >> iD;

    // A pointer to the new account
    Account *newA;

    // If the account does not exist in the Tree
    if (!accountStorage.retrieve(iD, newA)) {

      // Create a new account
      newA = new Account(firstName, lastName, iD);

      // Insert to the Tree
      accountStorage.insert(newA);

      // If account existed, cannot open
    } else {

      cerr << "ERROR: Account " << iD << " is already existed." << endl << endl;
    }

    // If the command is TRANSFER
  } else if (cType == 'T') {

    // Take in the ID and type of fund for the first account, the amount and, ID
    // and type of fund for the second account
    int iDaF1;
    int amount;
    int iDaF2;

    strStrm >> iDaF1 >> amount >> iDaF2;

    // A pointer to the 2 accounts
    Account *acc1;
    Account *acc2;

    // Find the type of fund to transfer for 2 accounts
    int typeOfFund1 = iDaF1 % 10;
    int typeOfFund2 = iDaF2 % 10;

    // If the account exist in the Tree,
    if (accountStorage.retrieve(iDaF1 / 10, acc1) &&
        accountStorage.retrieve(iDaF2 / 10, acc2)) {

      // Process transfer
      acc1->transfer(amount, typeOfFund1, acc2, typeOfFund2);

      // If the first account does not exist in the Tree
    } else if (acc1 == nullptr) {

      cerr << "ERROR: Could not find Account " << iDaF1 / 10
           << ". Transfer cancelled." << endl
           << endl;

      // If the second account does not exist in the Tree
    } else {

      cerr << "ERROR: Could not find Account " << iDaF2 / 10
           << ". Transfer cancelled." << endl
           << endl;
    }

    // If the command is HISTORY
  } else if (cType == 'H') {

    // Take in the ID (and type of fund) for the first account
    int iDaF;

    strStrm >> iDaF;

    // A pointer to the account
    Account *acc;

    // If the number has 4 digit,
    if (int(log10(iDaF) + 1) == 4) {

      // If the account does not exist in the Tree
      if (!accountStorage.retrieve(iDaF, acc)) {

        cerr << "ERROR: Could not find Account " << iDaF / 10
             << ". Cannot display history." << endl
             << endl;

        // If the account exist in the Tree
      } else {

        // Display the account
        acc->displayAcc();
      }

      // If the number has 5 digit,
    } else {

      // Find the type of fund
      int typeOfFund = iDaF % 10;

      // If the account does not exist in the Tree
      if (!accountStorage.retrieve(iDaF / 10, acc)) {

        cerr << "ERROR: Could not find Account " << iDaF / 10
             << ". Cannot display history." << endl
             << endl;

        // If the account exist in the Tree
      } else {

        // Display the account's _typeOfFund_
        acc->displayAccFund(typeOfFund);
      }
    }

  } else {

    // Take in the ID and type of fund for the account and the amount
    int iDaF;
    int amount;

    strStrm >> iDaF >> amount;

    // A pointer to the account
    Account *acc;

    // Find the type of fund
    int typeOfFund = iDaF % 10;

    // Find the ID
    int iD = iDaF / 10;

    // If the account exist in the Tree
    if (accountStorage.retrieve(iD, acc)) {

      // If the command is DEPOSIT
      if (cType == 'D') {

        acc->deposit(amount, typeOfFund);

        // If the command is WITHDRAW
      } else if (cType == 'W') {

        acc->withdraw(amount, typeOfFund);
      }

      // If the account does not exist in the Tree
    } else {

      cerr << "ERROR: Could not find Account " << iD
           << ". Transaction cancelled." << endl
           << endl;
    }
  }
}