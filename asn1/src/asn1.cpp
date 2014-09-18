#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "Account.h"
#include "Maint.h"

using namespace std;
int numCust = 1000;
void choose();
int action;
float amt;		//amount for withdraw or deposit
int id;			
int pNum;		//pin and id to search for current account -deposits and withdraws
int cnt=0;		//keeps track of number of customers and place in accounts array 
Maint* maintAccts = new Maint[100];
Account* custAccts = new Account[numCust];
int MAXCUST = numCust+1;

Account searchAcc(int id){
	Account findMe; 
	findMe.setPin(-1);
	//search for account with given id 
	for (int i = 0; i <= cnt; i++) {
		if (custAccts[i].getId() == id){
			findMe = custAccts[i];
		}
	}
	return findMe;
}

/*verify an account exists*/
int verify(Account ver, int id){
ver = searchAcc(id);
if (ver.getPin() == -1){
	cout << "That account does not exist. Please try again.\n" << endl;
	return 1;
}
return 0;
}

/*open an account - this needs work still .. just put something in for now */
int openAccount(){
	std::string type;
	float initBal;
	int pNum;
	cout << "Are you opening a chequing or savings account?\n \n Enter:\n 0 for Chequing \n 1 for Savings\n x to Cancel:" << "\n-> ";
	cin >> type;
	if (type == "x"){
		choose();
	}
	else if (type == "0"){
		type = "Chq";
	}
	else if (type == "1"){
		type = "Sav";
	}
	else {
		cout << "Incorrect response. Please try again. \n-> ";
			openAccount();
}
	cout << "Enter a 4 digit PIN number for your new account:\n-> ";
	cin >> pNum;
	while (pNum < 0 || pNum >= 10000) {
		cout << "Pin must be 4 integer digits. Please try again:\n-> ";
		cin >> pNum;
	}
	cout << "Enter the initial balance for the account\n-> ";
	cin >> initBal;
	Account acct(initBal, pNum, type, cnt);
	///add accounts to structure 
	custAccts[cnt] = acct; 
	cout << "Your Account ID is:  " << custAccts[cnt].getId() << ". " << "Please keep it handy for future transactions. \n" << endl;
	cnt++;
	//go back so they can do more transactions if they want
	cout << "Transaction successful. Thank you!\n" << endl;
	choose();
	return 0;
}
/*close an account - delete account from tree*/
int closeAccount(){
	int id;
	Account act;
	cout << "What is the Account ID for your account? \n -> ";
	cin >> id; 
	act = searchAcc(id);
	cout << "Enter PIN:\n" << endl;
	cin >> pNum;
	while (pNum != act.getPin()){
		cout << "Incorrect PIN. Please try again.\n -> ";
		cin >> pNum;
	}
	//find account with matching id and if pin is correct and balance is 0? close account 
	if (act.getPin() == -1){
		cout << "That account does not exist. Please try again.\n " << endl;
		closeAccount();
	}
	if (act.getBal() != 0){
		cout << "Balance must be 0 before the account can be closed. Returning to main menu." << endl;
		choose();
	}
	else{
		//remove from structure 
		custAccts[id].setId(MAXCUST);

		//go back so they can do more transactions if they want
		cout << "Transaction successful. Thank you!\n" << endl;
		choose();
	}
	return 0;
}
/*deposit money*/
int deposit(){
	Account act; 
	cout << "Enter account ID: \n -> "; 
	cin >> id; 
	act = searchAcc(id);
	if (verify(act, id)){
		deposit();
	}
	else{
		cout << "Enter PIN:\n ->";
		cin >> pNum;
		while (pNum != act.getPin()){
			cout << "Incorrect PIN. Please try again.\n -> ";
			cin >> pNum;
		}
		cout << "How much would you like to deposit today? \n -> ";
		cin >> amt;
		custAccts[id].addBal(amt);
		cout << "Current Balance: " << custAccts[id].getBal() << endl;
		//go back so they can do more transactions if they want
		choose();
	}
	return 0;
}
/*withdraw money*/
int withdraw() {
	Account act;
	cout << "Enter Account ID: \n -> ";
	cin >> id;
	act = searchAcc(id);
	if (verify(act,id)){
		withdraw();
	}
	else{
		cout << "Enter PIN:\n ->";
		cin >> pNum;
		while (pNum != act.getPin()){
			cout << "Incorrect PIN. Please try again.\n -> ";
			cin >> pNum;
		}
		cout << "How much would you like to withdraw today? \n -> ";
		cin >> amt;
		custAccts[id].subBal(amt);
		cout << "Current Balance: " << custAccts[id].getBal() << endl;
		//go back so they can do more transactions if they want
		choose();
	}
	return 0;
}

/*check balance*/
int checkBal(){
	Account act;
	cout << "Enter Account ID: \n -> ";
	cin >> id;
	act = searchAcc(id);
	if (verify(act,id)){
		checkBal();
	}
	else{
		cout << "Enter your PIN: \n -> ";
		cin >> pNum;
		while (pNum != act.getPin()){
			cout << "Incorrect PIN. Please Try Again:\n -> ";
			cin >> pNum; 
		}
		cout << "Your account balance is:  " << act.getBal() << "\n" << endl;
		//go back so they can do more transactions if they want
		cout << "Thank you!\n" << endl;
		choose();
	}
	return 0;
}

/*transfer funds between two accounts*/
void transfer() {
	Account a; 
	Account b;
	int sendId;
	int recId;
	cout << "Enter the account ID for sender's account: \n->";
	cin >> sendId;
	a = searchAcc(sendId);
	if (verify(a,sendId)){
		transfer();
	}
	cout << "Enter PIN for sender's account: \n ->";
	cin >> pNum; 
	while (pNum != custAccts[sendId].getPin()){
		cout << "Incorrect PIN. Please Try Again:\n -> ";
		cin >> pNum;
	}
	cout << "Enter the account ID for receiver's account: \n ->";
	cin >> recId; 
	b = searchAcc(recId);
	if (verify(b,recId)){
		transfer();
	}
	cout << "Enter the amount to transfer: \n ->";
	cin >> amt; 
	a = custAccts[sendId]; 
	b = custAccts[recId];
	if (a.subBal(amt)){
		b.addBal(amt);
		cout << "Transaction Complete. Thank you!" << endl;
	}
	//go back so they can do more transactions if they want
	choose();
}
/*maintenance login*/
int maint() {
	return 0;
}

void choose(){
	std::cout << "Enter:\n 0 to open a new account\n 1 to close an account\n 2 to deposit money\n 3 to withdraw money\n 4 to check balance \n 5 to transfer funds \n 6 for maintenance options \n 7 to quit\n \n->";
	std::cin >> action;
	switch (action){
	case 0:
		openAccount();
		break;
	case 1:
		closeAccount();
		break;
	case 2:
		deposit();
		break;
	case 3:
		withdraw();
		break;
	case 4:
		checkBal();
		break;
	case 5:
		transfer();
		break;
	case 6:
		maint();
		break;
	case 7: 
		exit(0);
		break;
	default:
		exit(0);
		break;
	}
}

/*Main program*/
int main() {
	choose();
	return 0;
}
