/*
 * Account.cpp
 *
 *  Created on: Sep 15, 2014
 *      Author: Sparky
 */

#include "Account.h"
#include <iostream>
#include <string>

using namespace std;

	float balance;
	bool initialized;
	string type;

/*constructors*/

	/*default constructor*/
	Account::Account() {
		initialized = false;
	}

Account::Account(float bal, string t) {
	balance = bal;
	type = t;
	initialized = true;
}

/*deconstructor */
Account::~Account(void){

}

/*getters & setters*/
/*get the current balance for selected account*/
float Account::getBal(){
	return balance;
}

bool Account::getIni(){
	return initialized;
}


/*deposit money into current account*/
void Account::addBal(float amt){
	balance += amt;
	cout << "Deposit transaction successful. Thank you!\n" << endl;
}

/*withdraw money from current account, surcharge if over 1000 and error if insufficient funds*/
int Account::subBal(float amt){
	float checkBal = balance;
	char ans;
	if((checkBal - amt) < 0){
		cout << "There is insufficient funds to process this transaction.\nRequest Denied. Transaction Cancelled.\n" << endl;
		return 0;
	}
	else if (type == "Chq"){
		if (checkBal - amt < 1000){
			if ((checkBal - amt - 2) < 0){
				cout << "Current withdraw subject to $2.00 Surcharge. Insufficient Funds.\nRequest Denied. Transaction Cancelled.\n" << endl;
				return 1;
			}
			else {
				cout << "Your balance after withdraw will be less than 1000 and subject to a $2.00 charge\nPress Y to continue or any other key to cancel request: Y/N?\n ";
				cin >> ans;
				if (ans = 'Y' || 'y'){
					balance = (balance - amt - 2);
					cout << "Transaction successful. Thank you!\n" << endl;
					return 0;
				}
				else{
					cout << "Your transaction has been cancelled. Surcharge was declined by customer.\n" << endl;
					return 1;
				}
			}
		}
	}
	balance = balance - amt; 
	cout << "Withdraw transaction successful. Thank you!\n" << endl;
	return 0;
};
