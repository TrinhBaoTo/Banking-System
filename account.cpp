#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "account.h"

using namespace std;

// Print Account
ostream &operator<<(ostream &out, const Account &other) {

  out << other.fName << " " << other.lName << " Account ID: " << other.ID
      << endl;

  // Traverse for each fund of the account
  for (int i = 0; i < 10; i++) {

    out << "\t" << other.fund[i] << ": $" << other.balance[i] << endl;
  }

  return out;
}

// ********** Constructor **********
Account::Account(string firstName, string lastName, int inputID)
    : fName(firstName), lName(lastName), ID(inputID) {

  // Initialize the funds balances to 0
  for (int &b : balance) {
    b = 0;
  }
}

// ********** Operator overload - Compare Accounts **********

bool Account::operator>(const Account &ac) const { return ID > ac.ID; }

bool Account::operator<(const Account &ac) const { return ID < ac.ID; }

//  ********** Access Account value **********

int Account::getID() { return ID; }

// **********  Account transaction **********

// Deposit money
void Account::deposit(int amount, int typeOfFund) {

  // A stringstream to write to the history vector.
  stringstream h;
  h << "D " << ID << typeOfFund << " " << amount;

  // Increase the balance for fund _typeOfFund_ by _amount_
  balance[typeOfFund] = balance[typeOfFund] + amount;

  // Update history
  history[typeOfFund].push_back(h.str());
}

// Withdraw money
void Account::withdraw(int amount, int typeOfFund) {

  // A stringstream to write to the history vector.
  stringstream h;
  h << "W " << ID << typeOfFund << " " << amount;

  // If the amoount to be withdraw is > than the balance of _typeOfFund_
  if (amount > balance[typeOfFund]) {

    // Calculate the partial
    int partial = amount - balance[typeOfFund];

    // If the fund is Money Market and the Prime Money Market fund have enough
    // to cover
    if (typeOfFund == 0 && balance[1] >= partial) {

      // Process withdraw
      balance[0] = 0;
      balance[1] = balance[1] - partial;

      // If the fund is Prime Money Market and the Money Market fund have enough
      // to cover
    } else if (typeOfFund == 1 && balance[0] >= partial) {

      // Process withdraw
      balance[1] = 0;
      balance[0] = balance[0] - partial;

      // If the fund is Long-Term Bond and the Short-Term Bond fund have enough
      // to cover
    } else if (typeOfFund == 2 && balance[3] >= partial) {

      // Process withdraw
      balance[2] = 0;
      balance[3] = balance[3] - partial;

      // If the fund is Short-Term Bond and the Long-Term Bond fund have enough
      // to cover
    } else if (typeOfFund == 3 && balance[2] >= partial) {

      // Process withdraw
      balance[3] = 0;
      balance[2] = balance[2] - partial;

    } else {

      // Update history
      history[typeOfFund].push_back(h.str() + " (Failed)");

      return;
    }

  } else {

    // Decrease the balance for fund _typeOfFund_ by _amount_
    balance[typeOfFund] = balance[typeOfFund] - amount;
  }

  // Update history
  history[typeOfFund].push_back(h.str());
}

// Transfer money
void Account::transfer(int amount, int typeOfFund1, Account *other,
                       int typeOfFund2) {

  // A stringstream to write to the history vector.
  stringstream h;
  h << "T " << ID << typeOfFund1 << " " << amount;

  // If the amoount to be transfer fromt he first account is > than the balance
  // of _typeOfFund_
  if (amount > balance[typeOfFund1]) {

    // and transfering from different account
    if (ID != other->getID()) {

      int partial = amount - balance[typeOfFund1];

      // If the fund is Money Market and the Prime Money Market fund have enough
      // to cover
      if (typeOfFund1 == 0 && balance[1] >= partial) {

        // Process transfer
        balance[0] = 0;
        balance[1] = balance[1] - partial;

        // If the fund is Prime Money Market and the Money Market fund have
        // enough to cover
      } else if (typeOfFund1 == 1 && balance[0] >= partial) {

        // Process transfer
        balance[1] = 0;
        balance[0] = balance[0] - partial;

        // If the fund is Long-Term Bond and the Short-Term Bond fund have
        // enough to cover
      } else if (typeOfFund1 == 2 && balance[3] >= partial) {

        // Process transfer
        balance[2] = 0;
        balance[3] = balance[3] - partial;

        // If the fund is Short-Term Bond and the Long-Term Bond fund have
        // enough to cover
      } else if (typeOfFund1 == 3 && balance[2] >= partial) {

        // Process transfer
        balance[3] = 0;
        balance[2] = balance[2] - partial;

      } else {

        // Update history
        history[typeOfFund1].push_back(h.str() + " (Failed)");

        return;
      }
    }

  } else {

    // Decrease the balance for fund _typeOfFund1_ by _amount_ of the first
    // account
    balance[typeOfFund1] = balance[typeOfFund1] - amount;
  }

  // Update history
  history[typeOfFund1].push_back(h.str());

  // Deposit from the second account
  other->deposit(amount, typeOfFund2);
}

// Display Account details
void Account::displayAcc() {

  cout << "Displaying Transaction History for " << fName << " " << lName
       << " by fund. " << endl;

  // Traverse for each fund of the account history
  for (int i = 0; i < 10; i++) {

    cout << fund[i] << ": $" << balance[i] << endl;

    for (const auto &h : history[i]) {

      cout << "\t" << h << endl;
    }
  }

  cout << endl;
}

// Display Account specific fund details
void Account::displayAccFund(int typeOfFund) {

  cout << "Displaying Transaction History for " << fName << " " << lName
       << "'s " << fund[typeOfFund] << ": $" << balance[typeOfFund] << endl;

  // Traverse for each fund of the account history
  for (const auto &h : history[typeOfFund]) {

    cout << "\t" << h << endl;
  }

  cout << endl;
}