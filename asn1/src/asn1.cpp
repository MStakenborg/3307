#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "Client.h"
#include "Account.h"
#include <vector>
#include <iomanip>
#include <fstream>
#include <ctime>

using namespace std;

float amt;		//amount for withdraw or deposit
string userId;
string pin;
string option;
vector<Client> clientList;
bool trace;
ofstream traceFile;
time_t now;
string currentTime;


void menu();
void signUp();
void signIn();
void clientOptions(int i);
void transferToUser(int i, int user, string type);
void printInfo(int i);
void manager();
int withdrawCheck(int i, string type);
string getTime();


int clientExists(string id){
	for (int i = 0; i < clientList.size(); i++){
		if (clientList[i].getId() == id)
			return i;
	}
	return -1;
}

int openAccount(int i){
	string type;
	float initBal;
	cout << "Are you opening a chequing or savings account?\n \n Enter:\n 0 for Chequing \n 1 for Savings\n x to Cancel" << "\n\n ";
	cin >> type;
	if (type == "x"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " opted to cancel the open account process.\n";
		}
		return 0;
	}
	else if (type == "0"){
		if (clientList[i].getChq().getIni()){
			cout << "A chequing account is already open.\n";
			if (trace){
				traceFile << getTime() << " --- " << userId << " attempted to open a chequing account but it was already open.\n";
			}
			openAccount(i);
		}
		else {
			if (trace){
				traceFile << getTime() << " --- " << userId << " opened a chequing account.\n";
			}
			cout << "\nEnter the initial balance for the account:\n\n ";
			cin >> initBal;
			clientList[i].setChq(Account(initBal, "Chq"));
			if (trace){
				traceFile << getTime() << " --- " << userId << " entered $" << initBal << " as the chequing account's initial balance.\n";
			}
		}
	}
	else if (type == "1"){
		if (clientList[i].getSav().getIni()){
			cout << "A savings account is already open.\n";
			if (trace){
				traceFile << getTime() << " --- " << userId << " attempted to open a savings account but it was already open.\n";
			}
			openAccount(i);
		}
		else {
			if (trace){
				traceFile << getTime() << " --- " << userId << " opened a savings account.\n";
			}
			cout << "\nEnter the initial balance for the account:\n\n ";
			cin >> initBal;
			clientList[i].setSav(Account(initBal, "Sav"));
			if (trace){
				traceFile << getTime() << " --- " << userId << " entered $" << initBal << " as the savings account's initial balance.\n";
			}
		}
	}
	else {
		cout << "\nIncorrect response. Please try again. \n ";
		if (trace){
			traceFile << getTime() << " --- " << userId << " entered an invalid input in the open account process.\n";
		}
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
					if (trace){
						traceFile << getTime() << " --- " << userId << " attempted to close the chequing account but could not because it still has money in it.\n";
					}
				}
				else {
					clientList[i].setChq(Account());
					if (trace){
						traceFile << getTime() << " --- " << userId << " successfully closed the chequing account.\n";
					}
					cout << "\nChequing account successfully closed\n\n";
				}
			}
			else {
				cout << "\nCould not close chequing account because it is the only account.\n\n";
				if (trace){
					traceFile << getTime() << " --- " << userId << " attempted to close the chequing account but could not because it is the only account.\n";
				}
			}
		}
		else {
			if (trace){
				traceFile << getTime() << " --- " << userId << " attempted to close the chequing account but could not because it does not exist.\n";
			}
			cout << "\nNo existing chequing account to close.\n\n";
		}
	}
	else if (option == "1"){
		if (clientList[i].getSav().getIni()){
			if (clientList[i].getChq().getIni()){
				if (clientList[i].getSav().getBal() != 0){
					cout << "\nCould not close savings account because it still has money in it.\n\n";
					if (trace){
						traceFile << getTime() << " --- " << userId << " attempted to close the savings account but could not because it still has money in it.\n";
					}
				}
				else {
					clientList[i].setSav(Account());
					cout << "\nSavings account successfully closed\n\n";
					if (trace){
						traceFile << getTime() << " --- " << userId << " successfully closed the savings account.\n";
					}
				}
			}
			else {
				cout << "\nCould not close savings account because it is the only account.\n\n";
				if (trace){
					traceFile << getTime() << " --- " << userId << " attempted to close the savings account but could not because it is the only account.\n";
				}
			}
		}
		else {
			cout << "\nNo existing savings account to close.\n\n";
			if (trace){
				traceFile << getTime() << " --- " << userId << " attempted to close the savings account but could not because it does not exist.\n";
			}
		}
	}
	else if (option == "x"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " opted to cancel the close account process.\n";
		}
		if (clientList[i].getId() == "manager"){
			manager();
		}
		else {
			clientOptions(i);
		}
	}
	else {
		cout << "\nInvalid input\n";
		if (trace){
			traceFile << getTime() << " --- " << userId << " entered an invalid input in the close account process.\n";
		}
		closeAccount(i);
	}
}

/*deposit money*/
void deposit(int i){
	cout << "\nEnter:\n0 to deposit to your chequing account\n1 to deposit to your savings account\nx to cancel\n\n ";
	cin >> option;
	if (option == "0"){
		if (clientList[i].getChq().getIni()){
			if (trace){
				traceFile << getTime() << " --- " << userId << " chose to deposit money into his/her chequing account.\n";
			}
			cout << "\n\nHow much would you like to deposit today?\n";
			cin >> amt;
			clientList[i].depChq(amt);
			cout << "Deposit transaction successful. Thank you!\n\n";
			cout << "\nYour chequing account balance is now: $" << clientList[i].getChq().getBal() << "\n\n";
			if (trace){
				traceFile << getTime() << " --- " << userId << " entered $" << amt << " and it was deposited into his/her chequing account.\n";
			}
		}
		else {
			if (trace){
				traceFile << getTime() << " --- " << userId << " chose to deposit money into his/her chequing account, but no chequing account exists.\n";
			}
			cout << "\nYou currently don't have a chequing account\n";
			deposit(i);
		}
	}
	else if (option == "1"){
		if (clientList[i].getSav().getIni()){
			if (trace){
				traceFile << getTime() << " --- " << userId << " chose to deposit money into his/her savings account.\n";
			}
			cout << "\n\nHow much would you like to deposit today?\n";
			cin >> amt;
			clientList[i].depSav(amt);
			cout << "Deposit ransaction successful. Thank you!\n\n";
			cout << "\nYour savings account balance is now: $" << clientList[i].getSav().getBal() << "\n\n";
			if (trace){
				traceFile << getTime() << " --- " << userId << " entered $" << amt << " and it was deposited into his/her savings account.\n";
			}
		}
		else {
			if (trace){
				traceFile << getTime() << " --- " << userId << " chose to deposit money into his/her savings account, but no savings account exists.\n";
			}
			cout << "\nYou currently don't have a savings account\n";
			deposit(i);
		}
	}
	else if (option == "x"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " opted to cancel the deposit process.\n";
		}
		clientOptions(i);
	}
	else {
		if (trace){
			traceFile << getTime() << " --- " << userId << " entered an invalid input in the deposit process.\n";
		}
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
			if (trace){
				traceFile << getTime() << " --- " << userId << " chose to withdraw money from his/her chequing account.\n";
			}
			cout << "\nHow much would you like to withdraw today?\n\n";
			cin >> amt;
			if (trace){
				traceFile << getTime() << " --- " << userId << " entered $" << amt << " for the amount of money to withdraw from his/her chequing account.\n";
			}
			withdrawCheck(i, "Chq");
			cout << "\nYour chequing account balance is now: $" << clientList[i].getChq().getBal() << "\n\n";
		}
		else {
			if (trace){
				traceFile << getTime() << " --- " << userId << " chose to withdraw money from his/her chequing account, but no savings account exists.\n";
			}
			cout << "\nYou currently don't have a chequing account\n";
			withdraw(i);
		}
	}
	else if (option == "1"){
		if (clientList[i].getSav().getIni()){
			if (trace){
				traceFile << getTime() << " --- " << userId << " chose to withdraw money from his/her savings account.\n";
			}
			cout << "\nHow much would you like to withdraw today?\n";
			cin >> amt;
			if (trace){
				traceFile << getTime() << " --- " << userId << " entered $" << amt << " for the amount of money to withdraw from his/her savings account.\n";
			}
			withdrawCheck(i, "Sav");
			cout << "\nYour savings account balance is now: $" << clientList[i].getSav().getBal() << "\n\n";
		}
		else {
			if (trace){
				traceFile << getTime() << " --- " << userId << " chose to withdraw money from his/her savings account, but no savings account exists.\n";
			}
			cout << "\nYou currently don't have a savings account\n";
			withdraw(i);
		}
	}
	else if (option == "x"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " opted to cancel the withdraw process.\n";
		}
		clientOptions(i);
	}
	else {
		if (trace){
			traceFile << getTime() << " --- " << userId << " entered an invalid input in the withdraw process.\n";
		}
		cout << "\nInvalid input\n";
		withdraw(i);
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

void transfer(int i) {

	int user;
	userId = clientList[i].getId();
	cout << "\nEnter:\n0 to transfer from your chequing account to your savings account\n1 to transfer from your savings account to your chequing account\n" <<
			"2 to transfer from your chequing account to another user's account\n3 to transfer from your savings account to another user's account\nx to cancel\n\n ";
	cin >> option;
	if (option == "0"){
		if (clientList[i].getChq().getIni() && clientList[i].getSav().getIni()){
			if (trace){
				traceFile << getTime() << " --- " << userId << " decided to transfer from his/her chequing account to his/her savings account.\n";
			}
			cout << "\nHow much would you like to transfer?\n";
			cin >> amt;
			if (trace){
				traceFile << getTime() << " --- " << userId << " enetered $" << amt << " as the amount to transfer.\n";
			}
			if (withdrawCheck(i, "Chq") > 0){
				if (trace){
					traceFile << getTime() << " --- " << userId << "'s transfer was successfull.\n";
				}
				clientList[i].depSav(amt);
				checkBal(i);
				clientOptions(i);
			}
			else {
				if (trace){
					traceFile << getTime() << " --- " << userId << "'s transfer was unsuccessfull.\n";
				}
				transfer(i);
			}
		}
		else {
			if (trace){
				traceFile << getTime() << " --- " << userId << " decided to transfer from his/her chequing account to his/her " << 
					"savings account but does not have both accounts. Transaction cancelled.\n";
			}
			cout << "\nYou don't have a both a chequing and savings account\n";
			transfer(i);
		}

	}
	else if (option == "1"){
		if (clientList[i].getChq().getIni() && clientList[i].getSav().getIni()){
			if (trace){
				traceFile << getTime() << " --- " << userId << " decided to transfer from his/her savings account to his/her chequing account.\n";
			}
			cout << "\nHow much would you like to transfer?\n";
			cin >> amt;
			if (trace){
				traceFile << getTime() << " --- " << userId << " enetered $" << amt << " as the amount to transfer.\n";
			}
			if (withdrawCheck(i, "Sav") > 0){
				if (trace){
					traceFile << getTime() << " --- " << userId << "'s transfer was successfull.\n";
				}
				clientList[i].depChq(amt);
				checkBal(i);
				clientOptions(i);
			}
			else {
				if (trace){
					traceFile << getTime() << " --- " << userId << "'s transfer was unsuccessfull.\n";
				}
				transfer(i);
			}
		}
		else {
			if (trace){
				traceFile << getTime() << " --- " << userId << " decided to transfer from his/her savings account to his/her " <<
					"checking account but does not have both accounts. Transaction cancelled.\n";
			}
			cout << "\nYou don't have both a chequing and savings account\n";
			transfer(i);
		}
	}
	else if (option == "2"){
		if (clientList[i].getChq().getIni()){
			if (trace){
				traceFile << getTime() << " --- " << userId << " decided to transfer from his/her chequing account to another user's account.\n";
			}
			cout << "\nEnter the user ID you wish to transfer money to:\n";
			cin >> userId;
			user = clientExists(userId);
			if (user > 0){
				if (trace){
					traceFile << getTime() << " --- " << clientList[i].getId() << "entered " << userId << " for the user he/she will transfer money to.\n";
				}
				transferToUser(i, user, "chq");
			}
			else {
				if (trace){
					traceFile << getTime() << " --- " << clientList[i].getId() << "entered " << userId << " for the user he/she will transfer money to, " << 
						"but that user does not exist. Transaction cancelled.\n";
				}
				cout << "\nThat user does not exist\n";
				transfer(i);
			}
		}
		else {
			if (trace){
				traceFile << getTime() << " --- " << userId << " decided to transfer from his/her chequing account to another user's account, " << 
					"but he/she does not have a chequing account. Transaction cancelled.\n";
			}
			cout << "\nYou don't have a chequing account\n";
			transfer(i);
		}
	}
	else if (option == "3"){
		if (clientList[i].getSav().getIni()){
			if (trace){
				traceFile << getTime() << " --- " << userId << " decided to transfer from his/her savings account to another user's account.\n";
			}
			cout << "\nEnter the user ID you wish to transfer money to:\n";
			cin >> userId;
			user = clientExists(userId);
			if (user > 0){
				if (trace){
					traceFile << getTime() << " --- " << clientList[i].getId() << "entered " << userId << " for the user he/she will transfer money to.\n";
				}
				transferToUser(i, user, "sav");
			}
			else {
				if (trace){
					traceFile << getTime() << " --- " << clientList[i].getId() << "entered " << userId << " for the user he/she will transfer money to, " <<
						"but that user does not exist. Transaction cancelled.\n";
				}
				cout << "\nThat user does not exist\n";
				transfer(i);
			}
		}
		else {
			if (trace){
				traceFile << getTime() << " --- " << userId << " decided to transfer from his/her savings account to another user's account, " <<
					"but he/she does not have a savings account. Transaction cancelled.\n";
			}
			cout << "\nYou don't have a savings account\n";
			transfer(i);
		}
	}
	else if (option == "x"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " opted to cancel the transfer process.\n";
		}
		clientOptions(i);
	}
	else {
		if (trace){
			traceFile << getTime() << " --- " << userId << " entered an invalid input in the transfer process.\n";
		}
		cout << "\nInvalid input\n";
		transfer(i);
	}
}

void transferToUser(int i, int user, string type){
	cout << "\nEnter:\n0 to transfer to their chequing account\n1 to transfer to their savings account\nx to cancel\n\n ";
	cin >> option;
	if (option == "0"){
		if (clientList[user].getChq().getIni()){
			if (trace){
				traceFile << getTime() << " --- " << clientList[i].getId() << " decided to transfer money to " << clientList[user].getId() << "'s chequing account.\n";
			}
			cout << "\nHow much would you like to transfer?\n";
			cin >> amt;
			if (trace){
				traceFile << getTime() << " --- " << clientList[i].getId() << " enetered $" << amt << " as the amount to transfer.\n";
			}
			if (type == "sav"){
				if (withdrawCheck(i, "Sav") > 0){
					if (trace){
						traceFile << getTime() << " --- " << clientList[i].getId() << "'s transfer was successfull.\n";
					}
					clientList[user].depChq(amt);
					checkBal(i);
					clientOptions(i);
				}
				else {
					if (trace){
						traceFile << getTime() << " --- " << userId << "'s transfer was unsuccessfull.\n";
					}
					transferToUser(i, user, type);
				}
			}
			else {
				if (withdrawCheck(i, "Chq") > 0){
					if (trace){
						traceFile << getTime() << " --- " << clientList[i].getId() << "'s transfer was successfull.\n";
					}
					clientList[user].depChq(amt);
					checkBal(i);
					clientOptions(i);
				}
				else {
					if (trace){
						traceFile << getTime() << " --- " << userId << "'s transfer was unsuccessfull.\n";
					}
					transferToUser(i, user, type);
				}
			}
		}
		else {
			if (trace){
				traceFile << getTime() << " --- " << clientList[i].getId() << " decided to transfer money to " << clientList[user].getId() << 
					"'s chequing account, but he/she does not have a chequing account. Transaction cancelled\n";
			}
			cout << "\nThe user does not have a chequing account\n";
			transferToUser(i, user, type);
		}
	}
	else if (option == "1"){
		if (clientList[user].getSav().getIni()){
			if (trace){
				traceFile << getTime() << " --- " << clientList[i].getId() << " decided to transfer money to " << clientList[user].getId() << "'s savings account.\n";
			}
			cout << "\nHow much would you like to transfer?\n";
			cin >> amt;
			if (trace){
				traceFile << getTime() << " --- " << clientList[i].getId() << " enetered $" << amt << " as the amount to transfer.\n";
			}
			if (type == "sav"){
				if (withdrawCheck(i, "Sav") > 0){
					if (trace){
						traceFile << getTime() << " --- " << clientList[i].getId() << "'s transfer was successfull.\n";
					}
					clientList[user].depSav(amt);
					checkBal(i);
					clientOptions(i);
				}
				else {
					if (trace){
						traceFile << getTime() << " --- " << userId << "'s transfer was unsuccessfull.\n";
					}
					transferToUser(i, user, type);
				}
			}
			else {
				if (withdrawCheck(i, "Chq") > 0){
					if (trace){
						traceFile << getTime() << " --- " << clientList[i].getId() << "'s transfer was successfull.\n";
					}
					clientList[user].depSav(amt);
					checkBal(i);
					clientOptions(i);
				}
				else {
					if (trace){
						traceFile << getTime() << " --- " << userId << "'s transfer was unsuccessfull.\n";
					}
					transferToUser(i, user, type);
				}
			}
		}
		else {
			if (trace){
				traceFile << getTime() << " --- " << clientList[i].getId() << " decided to transfer money to " << clientList[user].getId() <<
					"'s savings account, but he/she does not have a savings account. Transaction cancelled\n";
			}
			cout << "\nThe user does not have a savings account\n";
			transferToUser(i, user, type);
		}
	}
	else if (option == "x"){
		if (trace){
			traceFile << getTime() << " --- " << clientList[i].getId() << "opted to cancel the transfer to another user process.\n";
		}
		transfer(i);
	}
	else {
		if (trace){
			traceFile << getTime() << " --- " << clientList[i].getId() << " entered an invalid input in the transfer to another user process.\n";
		}
		cout << "\nInvalid input\n";
		transferToUser(i, user, type);
	}
}

int withdrawCheck(int i, string type){
	float checkBal;
	if (type == "Chq"){
		checkBal = clientList[i].getChq().getBal();
	}
	else {
		checkBal = clientList[i].getSav().getBal();
	}
	char ans;
	if ((checkBal - amt) < 0){
		cout << "\nThere is insufficient funds to process this transaction.\nRequest Denied. Transaction Cancelled.\n" << endl;
		if (trace){
			traceFile << getTime() << " --- " << userId << "'s withdraw from his/her account was cancelled because of insufficient funds.\n";
		}
		return 0;
	}
	else if (type == "Chq"){
		if (checkBal - amt < 1000){
			if ((checkBal - amt - 2) < 0){
				cout << "\nCurrent withdraw subject to $2.00 Surcharge. Insufficient Funds.\nRequest Denied. Transaction Cancelled.\n" << endl;
				if (trace){
					traceFile << getTime() << " --- " << userId << "'s withdraw from his/her account was cancelled because of insufficient funds (couldn't pay surcharge).\n";
				}
				return 0;
			}
			else {
				cout << "\nYour balance after withdraw will be less than 1000 and subject to a $2.00 charge\nPress Y to continue or any other key to cancel request: Y/N?\n ";
				cin >> ans;
				if (ans == 'Y' || ans == 'y'){
					clientList[i].withChq(amt - 2);
					cout << "Transaction successful. Thank you!\n" << endl;
					if (trace){
						traceFile << getTime() << " --- " << userId << " withdraw was subject to a $2.00 surcharge and (s)he agreed to pay it. Transaction was successful.\n";
					}
					return 1;
				}
				else{
					cout << "\nYour transaction has been cancelled. Surcharge was declined by customer.\n" << endl;
					if (trace){
						traceFile << getTime() << " --- " << userId << " withdraw was subject to a $2.00 surcharge and (s)he declined to pay it. Transaction was cancelled.\n";
					}
					return 0;
				}
			}
		}
		else {
			clientList[i].withChq(amt);
			cout << "Transaction successful. Thank you!\n" << endl;
			if (trace){
				traceFile << getTime() << " --- " << userId << " withdraw from chequing account was successful.\n";
			}
			return 1;
		}
	}
	else {
		clientList[i].withSav(amt);
		cout << "Transaction successful. Thank you!\n" << endl;
		if (trace){
			traceFile << getTime() << " --- " << userId << " withdraw from savings account was successful.\n";
		}
		return 1;
	}
}

void printInfo(int i){
	Client client = clientList[i];
	cout << "\nID: " << setw(15) << left << client.getId() << " Pin: " << client.getPwd();
	if (client.getChq().getIni()){
		cout << " Chequing: $" << client.getChq().getBal();
	}
	if (client.getSav().getIni()){
		cout << " Savings: $" << client.getSav().getBal();
	}
}

void manager() {
	cout << "\nEnter:\n0 to view the list of clients\n1 to view a client's information\n2 to view the information of all clientele\n3 to view total bank funds"
		<< "\n4 to open an account\n5 to close an account\nx to logout\n\n ";
	cin >> option;
	if (option == "0"){
		if (trace){
			traceFile << getTime() << " --- The manager decided to view the list of clients.\n";
		}
		cout << "\nList of clients:\n";
		for (int i = 2; i < clientList.size(); i++){
			cout << " " << clientList[i].getId() << endl;
		}
		manager();
	}
	else if (option == "1"){
		if (trace){
			traceFile << getTime() << " --- The manager decided to view a clients information.\n";
		}
		cout << "\nEnter the client's user ID: ";
		cin >> userId;
		int i = clientExists(userId);
		if (i > 0){
			if (trace){
				traceFile << getTime() << " --- The manager entered " << userId << " as the client to view.\n";
			}
			printInfo(i);
			cout << endl;
			manager();
		}
		else {
			if (trace){
				traceFile << getTime() << " --- The manager entered " << userId << " as the client to view, but that client does not exist.\n";
			}
			cout << "\nThat client does not exist\n";
			manager();
		}
	}
	else if (option == "2"){
		if (trace){
			traceFile << getTime() << " --- The manager decided to view the information of all clientele.\n";
		}
		cout << "Clientele information:\n";
		for (int i = 2; i < clientList.size(); i++){
			printInfo(i);
		}
		cout << endl;
		manager();
	}
	else if (option == "3"){
		if (trace){
			traceFile << getTime() << " --- The manager decided to view the total bank funds.\n";
		}
		float savings = 0;
		float chequings = 0;
		for (int i = 2; i < clientList.size(); i++){
			if (clientList[i].getChq().getIni()){
				chequings += clientList[i].getChq().getBal();
			}
			if (clientList[i].getSav().getIni()){
				savings += clientList[i].getSav().getBal();
			}
		}
		cout << "\nTotal money in chequing: $" << chequings << "\nTotal money in savings: $" << savings << "\nTotal money: $" << chequings + savings << endl;
		manager();
	}
	else if (option == "4"){
		if (trace){
			traceFile << getTime() << " --- The manager decided to open an account for a user.\n";
		}
		cout << "\nEnter the client's user ID: ";
		cin >> userId;
		int i = clientExists(userId);
		if (i > 0){
			if (trace){
				traceFile << getTime() << " --- The manager entered " << userId << " as the client to open an account for.\n";
			}
			userId = "manager";
			openAccount(i);
			manager();
		}
		else {
			if (trace){
				traceFile << getTime() << " --- The manager entered " << userId << " as the client to open an account for, but that client does not exist.\n";
			}
			cout << "\nThat client does not exist\n";
			manager();
		}
	}
	else if (option == "5"){
		if (trace){
			traceFile << getTime() << " --- The manager decided to close an account for a user.\n";
		}
		cout << "\nEnter the client's user ID: ";
		cin >> userId;
		int i = clientExists(userId);
		if (i > 0){
			if (trace){
				traceFile << getTime() << " --- The manager entered " << userId << " as the client to close an account for.\n";
			}
			userId = "manager";
			closeAccount(i);
			manager();
		}
		else {
			if (trace){
				traceFile << getTime() << " --- The manager entered " << userId << " as the client to close an account for, but that client does not exist.\n";
			}
			cout << "\nThat client does not exist\n";
			manager();
		}
	}
	else if (option == "x"){
		if (trace){
			traceFile << getTime() << " --- The manager has logged out. \n\n";
		}
		menu();
	}
	else {
		if (trace){
			traceFile << getTime() << " --- The manager entered invalid input in the manager option menu.\n";
		}
		cout << "\nInvalid input\n";
		manager();
	}
}

void maint() {
	cout << "\nEnter:\n0 to turn on the execution tracer\n1 to turn off the execution tracer\nx to logout\n\n ";
	cin >> option;
	if (option == "0"){
		if (!trace) {
			trace = true;
			cout << "\nExecution tracer has been turned on\n";
			traceFile.open("trace.txt", ios::app);
			traceFile << getTime() << " --- Maintenence man turned on execution tracer\n";
			maint();
		}
		else {
			cout << "\nExecution tracer already turned on\n";
			traceFile << getTime() << " --- Maintenence man attemped to turn execution tracer on, but it was already on\n";
			maint();
		}
	}
	else if (option == "1"){
		if (trace){
			trace = false;
			cout << "\nExecution tracer has been turned off\n";
			traceFile << getTime() << " --- Maintenence man turned off execution tracer\n\n";
			traceFile.close();
			maint();
		}
		else {
			cout << "\nExecution tracer already turned off\n";
			maint();
		}
	}
	else if (option == "x"){
		cout << endl;
		if (trace){
			traceFile << getTime() << " --- Maintenance man logged out.\n\n";
		}
		menu();
	}
	else {
		if (trace){
			traceFile << getTime() << " --- Maintenance man entered invalid input in the maintenance man option menu.\n";
		}
		cout << "\nInvalid input\n\n";
		maint();
	}
}

void clientOptions(int i){
	userId = clientList[i].getId();
	cout << "Enter:\n 0 to open a chequing or savings account\n 1 to close an account\n 2 to check balance\n 3 to deposit money\n" 
		<< " 4 to withdraw money \n 5 to transfer funds \n x to logout\n\n ";
	cin >> option;
	if (option == "0"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " has started the open account process.\n";
		}
		openAccount(i);
		clientOptions(i);
	}
	else if (option == "1"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " has started the close account process.\n";
		}
		closeAccount(i);
		clientOptions(i);
	}
	else if (option == "2"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " has checked his/her account balances.\n";
		}
		checkBal(i);
		clientOptions(i);
	}
	else if (option == "3"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " has started the deposit process.\n";
		}
		deposit(i);
		clientOptions(i);
	}
	else if (option == "4"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " has started the withdraw process.\n";
		}
		withdraw(i);
		clientOptions(i);
	}
	else if (option == "5"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " has started the transfer money process.\n";
		}
		transfer(i);
		clientOptions(i);
	}
	else if (option == "x"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " has logged out.\n\n";
		}
		menu();
	}
	else {
		if (trace){
			traceFile << getTime() << " --- " << userId << " entered invalid input in the client option menu.\n";
		}
		cout << "\nInvalid input\n";
		clientOptions(i);
	}
}

void signIn(){
	cout << "\nEnter your user ID: ";
	cin >> userId;
	int i = clientExists(userId);
	if (i >= 0){
		if (trace){
			traceFile << getTime() << " --- Unkown user entered " << userId << " as the user ID to sign into\n";
		}
		while (true){
			cout << "\nEnter your pin or x to cancle: ";
			cin >> pin;
			if (pin == clientList[i].getPwd()){
				if (clientList[i].getId() == "manager"){
					if (trace){
						traceFile << "\n" << getTime() << " --- The bank manager entered the correct pin and is now logged in.\n";
					}
					cout << "\nYou are now logged in as the bank manager.\n\n";
					manager();
					break;
				}
				else if (clientList[i].getId() == "maintenance"){
					if (trace){
						traceFile << "\n" << getTime() << " --- The maintenance man entered the correct pin and is now logged in.\n ";
					}
					cout << "\nYou are now logged in as the maintenance man.\n\n";
					maint();
					break;
				}
				else {
					if (trace){
						traceFile << "\n" << getTime() << " --- " << userId << " enetered the correct pin and is now logged in.\n";
					}
					cout << "\nYou are now logged in as " << userId << ".\n\n";
					clientOptions(i);
					break;
				}
			}
			else if (pin == "x"){
				if (trace){
					traceFile << getTime() << " --- Unkown user opted to cancel the sign in process.\n";
				}
				cout << endl;
				menu();
			}
			else {
				if (trace){
					traceFile << getTime() << " --- Unkown user entered the wrong pin to log into " << userId << "'s account.\n";
				}
				cout << "\nInvalid pin.\n";
			}
		}
	}
	else {
		if (trace){
			traceFile << getTime() << " --- Unkown user entered " << userId << " as the user ID to sign into, but that user does not exist\n";
		}
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
			if (trace){
				traceFile << getTime() << " --- Unknown user entered " << userId << " as their user ID.\n";
			}
			cout << "\nEnter the 4 character pin for your new account: ";
			cin >> pin;
			if (pin.length() == 4){
				if (trace){
					traceFile << getTime() << " --- Unknown user entered " << pin << " as their PIN.\n";
				}
				cout << "\nTo finish creating your new account, you must open either a chequing or savings account\n";
				clientList.push_back(Client(userId, pin));
				i = clientExists(userId);
				if (openAccount(i)){
					cout << "\nAccount with user ID " << userId << " was successfully created.";
					cout << "\nYou are now logged in as " << userId << ".\n\n";
					if (trace){
						traceFile << "\n" << getTime() << " --- " << userId << "'s account was successfully created and (s)he is now logged in.\n";
					}
					clientOptions(i);
				}
				else {
					cout << "Account with user ID " << userId << " was not created.\n\n";
					if (trace){
						traceFile << getTime() << " --- Unkown user failed to create the account " << userId << " because (s)he didn't open a chequing or savings account.\n";
					}
					clientList.pop_back();
					menu();
				}
			}
			else {
				if (trace){
					traceFile << getTime() << " --- Unknown user entered " << pin << " as their pin, but it invalid.\n";
				}
				cout << "\nInvalid pin\n";
			}
		} while (pin.length() != 4);
	}
	else {
		cout << "\nThat user ID already exists\n\n";
		if (trace){
			traceFile << getTime() << " --- Unknown user tried to sign up as " << userId << ", but that account already exists.\n";
		}
		menu();
	}
}

string getTime(){
	now = time(0);
	currentTime = ctime(&now);
	return currentTime;
}

void menu(){
	cout << "Welcome, enter:\n\n 0 to sign in\n 1 to sign up\n q to quit\n\n ";
	cin >> option;
	if (option == "0"){
		if (trace){
			traceFile << getTime() << " --- Unknown user started sign in process.\n";
		}
		signIn();
	}
	else if (option == "1"){
		if (trace){
			traceFile << getTime() << " --- Unknown user started sign up process.\n";
		}
		signUp();
	}
	else if (option == "q"){
		if (trace){
			traceFile << getTime() << " --- Unknown user shut down program, execution tracer is turned off.\n";
			traceFile.close();
		}
		exit(0);
	}
	else {
		if (trace){
			traceFile << getTime() << " --- Unknown user entered invalid input in the main menu.\n";
		}
		cout << "\nInvalid input\n\n";
		menu();
	}
}

/*Main program*/
int main() {
	clientList.push_back(Client("manager", "1111"));
	clientList.push_back(Client("maintenance", "1111"));
	menu();
	return 0;
}