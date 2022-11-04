#include <array>
#include <iostream>
#include <string>
#include <vector>

#ifndef ACCOUNT_H
#define ACCOUNT_H

using namespace std;

// enum TYPE[
//     MONEY_MARKET = 0,
//     PRIME_MONEY_MARKET = 1,
//     LONG_TERM_BOND = 2,
//     SHORT_TERM_BOND = 3,
//     F_INDEX_FUND = 4,
//     CAPITAL_VALUE_FUND = 5,
//     GROWTH_EQUITY_FUND = 6,
//     GROWTH_INDEX_FUND = 7,
//     VALUE_FUND = 8,
//     VALUE_STOCK_INDEX = 9,
// ];

class Account {

  // Print Account
  friend ostream &operator<<(ostream &out, const Account &other);

public:
  // ********** Constructor **********

  Account(string firstName, string lastName, int inputID);

  // ********** Operator overload - Compare Accounts **********

  bool operator>(const Account &ac) const;

  bool operator<(const Account &ac) const;

  //  ********** Access Account value **********

  int getID();

  // **********  Account transaction **********

  // Deposit money
  void deposit(int amount, int typeOfFund);

  // Withdraw money
  void withdraw(int amount, int typeOfFund);

  // Transfer money
  void transfer(int amount, int typeOfFund1, Account *other, int typeOfFund2);

  // Display Account details
  void displayAcc();

  // Display Account specific fund details
  void displayAccFund(int typeOfFund);

private:
  // Name and ID
  string fName;
  string lName;
  int ID;

  // Account balance
  int balance[10];
  const string fund[10] = {"Money Market",       "Prime Money Market",
                           "Long-Term Bond",     "Short-Term Bond",
                           "500 Index Fund",     "Capital Value Fund",
                           "Growth Equity Fund", "Growth Index Fund",
                           "Value Fund",         "Value Stock Index"};

  // Account history each fund have its own history stored in a vector
  vector<string> history[10];
};
#endif // ACCOUNT_H
