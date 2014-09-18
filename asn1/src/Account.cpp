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
	int acctId;			
	std::string type;	//chequing or savings
	int pin;
	int idTally = 0;   //increments for each new account that's opened - account ID for account created

/*constructors*/

	/*default constructor*/
	Account::Account() {
	}

Account::Account(float bal, int pinNum, std::string accType, int id) {
	balance = bal;
	pin = pinNum;
	type = accType;
	acctId = id;
//	idTally++;
}

/*deconstructor */
Account::~Account(void){

}

/*getters & setters*/
/*get the current balance for selected account*/
float Account::getBal(){
	return balance;
}

/*get the account id for currently selected account*/
int Account::getId(){
	return acctId; 
}

/*retreive the pin for the current account*/
int Account::getPin(){
	return pin;
}

/*set the id of an account to null if removing it*/
void Account::setId(int newId){
	acctId = newId;
}
void Account::setPin(int set){
	pin = set; 
}

/*deposit money into current account*/
void Account::addBal(float amt){
	balance = (balance + amt);
	cout << "Deposit transaction successful. Thank you!\n" << endl;
}

/*withdraw money from current account, surcharge if over 1000 and error if insufficient funds*/
int Account::subBal(float amt){
	float checkBal = balance;
	char ans;
	if((checkBal - amt) < 0){
		cout << "There is insufficient funds to process this transaction.\n Request Denied. Transaction Cancelled.\n" << endl;
		return 0;
	}
	else if (type == "Chq"){
		if(checkBal - amt < 1000 ){
		if ((checkBal - amt - 2) < 0){
			cout << "Current withdraw subject to $2.00 Surcharge. Insufficient Funds.\n Request Denied. Transaction Cancelled.\n" << endl;
			return 1;
		}
		else {
			cout << "Your balance after withdraw will be less than 1000 and subject to a $2.00 charge. Press Y to continue or any other key to cancel request: Y/N?\n ->";
			cin >> ans;
			if (ans = 'Y' || 'y'){
				balance = (balance - amt - 2);
				cout << "Transaction successful. Thank you!\n" << endl;
				cout << "Current Balance: " << balance << endl;
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
