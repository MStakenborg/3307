#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "Client.h"
#include "Account.h"
#include "Maint.h"
#include <vector>

using namespace std;
int numCust = 1000;
void choose();
int action;
float amt;		//amount for withdraw or deposit
int id;
string userId;
string pin;
string option;
int pNum;		//pin and id to search for current account -deposits and withdraws
int cnt=0;		//keeps track of number of customers and place in accounts array 
Maint* maintAccts = new Maint[100];
Account* custAccts = new Account[numCust];
vector<Client> clientList;
int MAXCUST = numCust+1;

void menu();
void signUp();
void signIn();
void clientOptions(int i);

/*Account searchAcc(int id){
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
*/

int clientExists(string id){
	for (int i = 0; i < clientList.size(); i++){
		if (clientList[i].getId() == id)
			return i;
	}
	return -1;
}

/*verify an account exists
int verify(Account ver, int id){
	ver = searchAcc(id);
	if (ver.getPin() == -1){
		cout << "That account does not exist. Please try again.\n" << endl;
		return 1;
	}
	return 0;
}
*/

/*open an account - this needs work still .. just put something in for now */
int openAccount(int i){
	string type;
	float initBal;
	cout << "Are you opening a chequing or savings account?\n \n Enter:\n 0 for Chequing \n 1 for Savings\n x to Cancel" << "\n\n ";
	cin >> type;
	if (type == "x"){
		return 0;
	}
	else if (type == "0"){
		if (clientList[i].getChq().getIni()){
			cout << "A chequing account is already open.\n";
			openAccount(i);
		}
		else {
			cout << "\nEnter the initial balance for the account:\n\n ";
			cin >> initBal;
			clientList[i].setChq(Account(initBal, "Chq"));
		}
	}
	else if (type == "1"){
		if (clientList[i].getSav().getIni()){
			cout << "A savings account is already open.\n";
			openAccount(i);
		}
		else {
			cout << "\nEnter the initial balance for the account:\n\n ";
			cin >> initBal;
			clientList[i].setSav(Account(initBal, "Sav"));
		}
	}
	else {
		cout << "\nIncorrect response. Please try again. \n ";
			openAccount(i);
	}
	cout << "\nAccount successfully opened. Thank you!\n" << endl;
	return 1;
}
/*close an account - delete account from tree*/
void closeAccount(int i){
	//find account with matching id and if pin is correct and balance is 0? close account 
	cout << "\nEnter:\n0 to close your chequing account\n1 to close your savings account\nx to cancel\n\n ";
	cin >> option;
	if (option == "0"){
		if (clientList[i].getChq().getIni()){
			if (clientList[i].getSav().getIni()){
				if (clientList[i].getChq().getBal() != 0){
					cout << "\nCould not close chequing account because it still has money in it.\n\n";
				}
				else {
					clientList[i].setChq(Account());
					cout << "\nChequing account successfully closed\n\n";
				}
			}
			else {
				cout << "\nCould not close chequing account because it is the only account you have.\n\n";
			}
		}
		else {
			cout << "\nYou currently don't  have a chequing account.\n\n";
		}
	}
	else if (option == "1"){
		if (clientList[i].getSav().getIni()){
			if (clientList[i].getChq().getIni()){
				if (clientList[i].getSav().getBal() != 0){
					cout << "\nCould not close savings account because it still has money in it.\n\n";
				}
				else {
					clientList[i].setSav(Account());
					cout << "\nSavings account successfully closed\n\n";
				}
			}
			else {
				cout << "\nCould not close savings account because it is the only account you have.\n\n";
			}
		}
		else {
			cout << "\nYou currently don't  have a savings account.\n\n";
		}
	}
	else if (option == "x"){
		clientOptions(i);
	}
	else {
		cout << "\nInvalid input\n";
		closeAccount(i);
	}
}
/*deposit money*/
void deposit(int i){
	cout << "\nEnter:\n0 to deposit to your chequing account\n1 to deposit to your savings account\nx to cancel\n\n ";
	cin >> option;
	if (option == "0"){
		if (clientList[i].getChq().getIni()){
			cout << "\n\nHow much would you like to deposit today?\n";
			cin >> amt;
			clientList[i].depChq(amt);
			cout << "\nYour chequing account balance is now: $" << clientList[i].getChq().getBal() << "\n\n";
		}
		else {
			cout << "\nYou currently don't have a chequing account\n";
			deposit(i);
		}
	}
	else if (option == "1"){
		if (clientList[i].getSav().getIni()){
			cout << "\n\nHow much would you like to deposit today?\n";
			cin >> amt;
			clientList[i].depSav(amt);
			cout << "\nYour savings account balance is now: $" << clientList[i].getSav().getBal() << "\n\n";
		}
		else {
			cout << "\nYou currently don't have a savings account\n";
			deposit(i);
		}
	}
	else if (option == "x"){
		clientOptions(i);
	}
	else {
		cout << "\nInvalid input\n";
		closeAccount(i);
	}
}
/*withdraw money*/
void withdraw(int i) {
	cout << "\nEnter:\n0 to withdraw from your chequing account\n1 to withdraw from your savings account\nx to cancel\n\n ";
	cin >> option;
	if (option == "0"){
		if (clientList[i].getChq().getIni()){
			cout << "\nHow much would you like to withdraw today?\n";
			cin >> amt;
			clientList[i].withChq(amt);
			cout << "\nYour chequing account balance is now: $" << clientList[i].getChq().getBal() << "\n\n";
		}
		else {
			cout << "\nYou currently don't have a chequing account\n";
			withdraw(i);
		}
	}
	else if (option == "1"){
		if (clientList[i].getSav().getIni()){
			cout << "\nHow much would you like to withdraw today?\n";
			cin >> amt;
			clientList[i].withSav(amt);
			cout << "\nYour savings account balance is now: $" << clientList[i].getSav().getBal() << "\n\n";
		}
		else {
			cout << "\nYou currently don't have a savings account\n";
			withdraw(i);
		}
	}
	else if (option == "x"){
		clientOptions(i);
	}
	else {
		cout << "\nInvalid input\n";
		closeAccount(i);
	}
}

/*check balance*/

void checkBal(int i){
	if (clientList[i].getChq().getIni()){
		cout << "\nYour chequing account balance is : $" << clientList[i].getChq().getBal();
	}
	if (clientList[i].getSav().getIni()){
		cout << "\nYour savings account balance is : $" << clientList[i].getSav().getBal();
	}
	cout << "\n\n";
}

/*transfer funds between two accounts*/
/*
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

void clientOptions(int i){
	cout << "Enter:\n 0 to open a chequing or savings account\n 1 to close an account\n 2 to check balance\n 3 to deposit money\n 4 to withdraw money \n 5 to transfer funds \n x to logout\n \n ";
	cin >> option;
	if (option == "0"){
		openAccount(i);
		clientOptions(i);
	}
	else if (option == "1"){
		closeAccount(i);
		clientOptions(i);
	}
	else if (option == "2"){
		checkBal(i);
		clientOptions(i);
	}
	else if (option == "3"){
		deposit(i);
		clientOptions(i);
	}
	else if (option == "4"){
		withdraw(i);
		clientOptions(i);
	}
	else if (option == "5"){
		//transferFunds(i);
		clientOptions(i);
	}
	else if (option == "x"){
		menu();
	}
	else {
		cout << "\nInvalid input\n";
		clientOptions(i);
	}
}

void signIn(){
	cout << "\nEnter your user ID: ";
	cin >> userId;
	int i = clientExists(userId);
	if (i >= 0){
		while (true){
			cout << "\nEnter your pin or x to cancle: ";
			cin >> pin;
			if (pin == clientList[i].getPwd()){
				if (clientList[i].getId() == "manager"){
					cout << "\nYou are now logged in as the bank manager.\n\n";
					menu();
				}
				else if (clientList[i].getId() == "maintenance"){
					cout << "\nYou are now logged in as the maintenance man.\n\n";
					menu();
				}
				else {
					cout << "\nYou are now logged in as " << userId << ".\n\n";
					clientOptions(i);
				}
			}
			else if (pin == "x"){
				cout << endl;
				menu();
			}
			else {
				cout << "\nInvalid pin.\n";
			}
		}
	}
	else {
		cout << "\nThe user ID entered does not exist.\n\n";
		menu();
	}
}

void signUp(){
	cout << "\nEnter the user ID for your new account: ";
	cin >> userId;
	int i = clientExists(userId);
	if (i < 0){
		do {
			cout << "\nEnter the 4 character pin for your new account: ";
			cin >> pin;
			if (pin.length() == 4){
				cout << "\nTo finish creating your new account, you must open either a chequing or savings account\n";
				clientList.push_back(Client(userId, pin));
				i = clientExists(userId);
				if (openAccount(i)){
					cout << "\nAccount with user ID " << userId << " was successfully created.";
					cout << "\nYou are now logged in as " << userId << ".\n\n";
					clientOptions(i);
				}
				else {
					cout << "Account with user ID " << userId << " was not created.\n\n";
					clientList.pop_back();
					menu();
				}
			}
			else {
				cout << "\nInvalid pin\n";
			}
		} while (pin.length() != 4);
	}
	else {
		cout << "\nThat user ID already exists\n\n";
		menu();
	}
}

void menu(){
	cout << "Welcome, enter:\n\n 0 to sign in\n 1 to sign up\n q to quit\n\n ";
	cin >> option;
	if (option == "0")
		signIn();
	else if (option == "1")
		signUp();
	else if (option == "q")
		exit(0);
	else {
		cout << "\nInvalid input\n\n";
		menu();
	}
}

/*Main program*/
int main() {
	clientList.push_back(Client("manager", "1234"));
	clientList.push_back(Client("maintenance", "1234"));
	menu();
	//choose();
	return 0;
}
