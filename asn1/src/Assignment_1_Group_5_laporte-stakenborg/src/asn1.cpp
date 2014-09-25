/*
* asn1.cpp
*
*  Created on: Sep 15, 2014
*      Author: Team 5
*/

#define _CRT_SECURE_NO_WARNINGS // programmed it in visual studio and I needed to add this to stop it from forcing me to use the non-standard ctime_s function

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

// variable declaration
float amt;		//amount for withdraw or deposit
string userId; //stores a user id
string pin; //stores a use pin
string option; //stores the input when the user is given options
vector<Client> clientList; //vector containing all the clients
bool trace; //bool set to true when the execution tracer is turned on, false otherwise
ofstream traceFile; //write execution tracer to this file
time_t now; //used to get the current time
string currentTime; //string containing the current time

// some function declarations
void menu(); //main menu
void signUp(); //sign up menu
void signIn(); //sign in menu
void clientOptions(int i); //client options menu
void transferToUser(int i, int user, string type); //used to transfer money from one account to another
void printInfo(int i); //prints the info of a client
void manager(); //manager menu
int withdrawCheck(int i, string type); //checks if there is enough money to withdraw and withdraws it if there is
string getTime(); //returns a string with the current time

//clientExists function returns the vector location of the client with the given id
//returns -1 if said client does not exist
int clientExists(string id){

	for (int i = 0; i < clientList.size(); i++){
		if (clientList[i].getId() == id)
			return i;
	}
	return -1;
}

// opens a chequing or savings account, depending on user input
int openAccount(int i){

	string type;
	float initBal;

	cout << "Are you opening a chequing or savings account?\n \n Enter:\n 0 for Chequing \n 1 for Savings\n x to Cancel" << "\n\n ";
	cin >> type;

	if (type == "x"){

		//tracer output
		if (trace){
			traceFile << getTime() << " --- " << userId << " opted to cancel the open account process.\n";
		}

		// cancels open account
		return 0;
	}
	
	//Open chequing account
	else if (type == "0"){
		//checks if chequing account is already open
		if (clientList[i].getChq().getIni()){
			cout << "A chequing account is already open.\n";
			if (trace){
				traceFile << getTime() << " --- " << userId << " attempted to open a chequing account but it was already open.\n";
			}
			openAccount(i);
		}
		//chequing account not already open
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
	// open savings account
	else if (type == "1"){
		// checks if savings account is already open
		if (clientList[i].getSav().getIni()){
			cout << "A savings account is already open.\n";
			if (trace){
				traceFile << getTime() << " --- " << userId << " attempted to open a savings account but it was already open.\n";
			}
			openAccount(i);
		}
		// savings account not already open
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
	// invalid input
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

//close an account 
void closeAccount(int i){

	cout << "\nEnter:\n0 to close your chequing account\n1 to close your savings account\nx to cancel\n\n ";
	cin >> option;
	// close chequing
	if (option == "0"){
		//checks if chequing account exists
		if (clientList[i].getChq().getIni()){
			// checks if savings account exist
			if (clientList[i].getSav().getIni()){
				// check if account is empty, can't close if it is not
				if (clientList[i].getChq().getBal() != 0){
					cout << "\nCould not close chequing account because it still has money in it.\n\n";
					if (trace){
						traceFile << getTime() << " --- " << userId << " attempted to close the chequing account but could not because it still has money in it.\n";
					}
				}
				// all conditions met, can close account
				else {
					clientList[i].setChq(Account());
					if (trace){
						traceFile << getTime() << " --- " << userId << " successfully closed the chequing account.\n";
					}
					cout << "\nChequing account successfully closed\n\n";
				}
			}
			// if savings account doesn't exist, can't close chequing account because a user needs one account to remain a client
			else {
				cout << "\nCould not close chequing account because it is the only account.\n\n";
				if (trace){
					traceFile << getTime() << " --- " << userId << " attempted to close the chequing account but could not because it is the only account.\n";
				}
			}
		}
		// doesn't exist, can't close
		else {
			if (trace){
				traceFile << getTime() << " --- " << userId << " attempted to close the chequing account but could not because it does not exist.\n";
			}
			cout << "\nNo existing chequing account to close.\n\n";
		}
	}
	// close savings
	else if (option == "1"){
		//checks if savings account exists
		if (clientList[i].getSav().getIni()){
			// checks if savings account exist
			if (clientList[i].getChq().getIni()){
				// check if account is empty, can't close if it is not
				if (clientList[i].getSav().getBal() != 0){
					cout << "\nCould not close savings account because it still has money in it.\n\n";
					if (trace){
						traceFile << getTime() << " --- " << userId << " attempted to close the savings account but could not because it still has money in it.\n";
					}
				}
				// all conditions met, can close account
				else {
					clientList[i].setSav(Account());
					cout << "\nSavings account successfully closed\n\n";
					if (trace){
						traceFile << getTime() << " --- " << userId << " successfully closed the savings account.\n";
					}
				}
			}
			// if chequing account doesn't exist, can't close savings account because a user needs one account to remain a client
			else {
				cout << "\nCould not close savings account because it is the only account.\n\n";
				if (trace){
					traceFile << getTime() << " --- " << userId << " attempted to close the savings account but could not because it is the only account.\n";
				}
			}
		}
		// doesn't exist, can't close
		else {
			cout << "\nNo existing savings account to close.\n\n";
			if (trace){
				traceFile << getTime() << " --- " << userId << " attempted to close the savings account but could not because it does not exist.\n";
			}
		}
	}
	// cancel close account
	else if (option == "x"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " opted to cancel the close account process.\n";
		}
		// if called from manager, return to manager options
		if (clientList[i].getId() == "manager"){
			manager();
		}
		// otherwise return to client options
		else {
			clientOptions(i);
		}
	}
	// invalid input
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
	// deposit to chequing
	if (option == "0"){
		// check if chequing account exists
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
		// chequing account doens't exist
		else {
			if (trace){
				traceFile << getTime() << " --- " << userId << " chose to deposit money into his/her chequing account, but no chequing account exists.\n";
			}
			cout << "\nYou currently don't have a chequing account\n";
			deposit(i);
		}
	}
	// deposit to savings
	else if (option == "1"){
		// check if savings account exists
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
		// savings account doesn't exist
		else {
			if (trace){
				traceFile << getTime() << " --- " << userId << " chose to deposit money into his/her savings account, but no savings account exists.\n";
			}
			cout << "\nYou currently don't have a savings account\n";
			deposit(i);
		}
	}
	// cancel deposit
	else if (option == "x"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " opted to cancel the deposit process.\n";
		}
		clientOptions(i);
	}
	// invalid input
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
	// withdraw from chequing
	if (option == "0"){
		// check if chequing account exists
		if (clientList[i].getChq().getIni()){
			if (trace){
				traceFile << getTime() << " --- " << userId << " chose to withdraw money from his/her chequing account.\n";
			}
			cout << "\nHow much would you like to withdraw today?\n\n";
			cin >> amt;
			if (trace){
				traceFile << getTime() << " --- " << userId << " entered $" << amt << " for the amount of money to withdraw from his/her chequing account.\n";
			}
			// withdraws and handles potential surcharge
			withdrawCheck(i, "Chq");
			cout << "\nYour chequing account balance is now: $" << clientList[i].getChq().getBal() << "\n\n";
		}
		// checking account doesn't exist
		else {
			if (trace){
				traceFile << getTime() << " --- " << userId << " chose to withdraw money from his/her chequing account, but no savings account exists.\n";
			}
			cout << "\nYou currently don't have a chequing account\n";
			withdraw(i);
		}
	}
	// withdraw from savings
	else if (option == "1"){
		// checks if savings account exist
		if (clientList[i].getSav().getIni()){
			if (trace){
				traceFile << getTime() << " --- " << userId << " chose to withdraw money from his/her savings account.\n";
			}
			cout << "\nHow much would you like to withdraw today?\n";
			cin >> amt;
			if (trace){
				traceFile << getTime() << " --- " << userId << " entered $" << amt << " for the amount of money to withdraw from his/her savings account.\n";
			}
			// withdraws
			withdrawCheck(i, "Sav");
			cout << "\nYour savings account balance is now: $" << clientList[i].getSav().getBal() << "\n\n";
		}
		// savings account doesn't exist
		else {
			if (trace){
				traceFile << getTime() << " --- " << userId << " chose to withdraw money from his/her savings account, but no savings account exists.\n";
			}
			cout << "\nYou currently don't have a savings account\n";
			withdraw(i);
		}
	}
	// cancel withdraw
	else if (option == "x"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " opted to cancel the withdraw process.\n";
		}
		clientOptions(i);
	}
	// invalid input
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

// transfer money from one account to another account
void transfer(int i) {

	int user;
	userId = clientList[i].getId();
	cout << "\nEnter:\n0 to transfer from your chequing account to your savings account\n1 to transfer from your savings account to your chequing account\n" <<
			"2 to transfer from your chequing account to another user's account\n3 to transfer from your savings account to another user's account\nx to cancel\n\n ";
	cin >> option;
	// transfer from chequing to savings
	if (option == "0"){
		// check if both accounts exist
		if (clientList[i].getChq().getIni() && clientList[i].getSav().getIni()){
			if (trace){
				traceFile << getTime() << " --- " << userId << " decided to transfer from his/her chequing account to his/her savings account.\n";
			}
			cout << "\nHow much would you like to transfer?\n";
			cin >> amt;
			if (trace){
				traceFile << getTime() << " --- " << userId << " enetered $" << amt << " as the amount to transfer.\n";
			}
			// if withdraw is successfull (they have enough money to make the withdraw) then deposit (complete the transfer)
			if (withdrawCheck(i, "Chq") > 0){
				if (trace){
					traceFile << getTime() << " --- " << userId << "'s transfer was successfull.\n";
				}
				clientList[i].depSav(amt);
				checkBal(i);
				clientOptions(i);
			}
			// withdraw wasn't successfull, cancel transaction
			else {
				if (trace){
					traceFile << getTime() << " --- " << userId << "'s transfer was unsuccessfull.\n";
				}
				transfer(i);
			}
		}
		// both accounts don't exist
		else {
			if (trace){
				traceFile << getTime() << " --- " << userId << " decided to transfer from his/her chequing account to his/her " << 
					"savings account but does not have both accounts. Transaction cancelled.\n";
			}
			cout << "\nYou don't have a both a chequing and savings account\n";
			transfer(i);
		}

	}
	// transfer from savings to chequing
	else if (option == "1"){
		// check if both accounts exist
		if (clientList[i].getChq().getIni() && clientList[i].getSav().getIni()){
			if (trace){
				traceFile << getTime() << " --- " << userId << " decided to transfer from his/her savings account to his/her chequing account.\n";
			}
			cout << "\nHow much would you like to transfer?\n";
			cin >> amt;
			if (trace){
				traceFile << getTime() << " --- " << userId << " enetered $" << amt << " as the amount to transfer.\n";
			}
			// if withdraw is successfull (they have enough money to make the withdraw) then deposit (complete the transfer)
			if (withdrawCheck(i, "Sav") > 0){
				if (trace){
					traceFile << getTime() << " --- " << userId << "'s transfer was successfull.\n";
				}
				clientList[i].depChq(amt);
				checkBal(i);
				clientOptions(i);
			}
			// withdraw wasn't successfull, cancel transaction
			else {
				if (trace){
					traceFile << getTime() << " --- " << userId << "'s transfer was unsuccessfull.\n";
				}
				transfer(i);
			}
		}
		// both accounts don't exist
		else {
			if (trace){
				traceFile << getTime() << " --- " << userId << " decided to transfer from his/her savings account to his/her " <<
					"checking account but does not have both accounts. Transaction cancelled.\n";
			}
			cout << "\nYou don't have both a chequing and savings account\n";
			transfer(i);
		}
	}
	// transfer from chequing to another user's account
	else if (option == "2"){
		// check if chequing account exists
		if (clientList[i].getChq().getIni()){
			if (trace){
				traceFile << getTime() << " --- " << userId << " decided to transfer from his/her chequing account to another user's account.\n";
			}
			cout << "\nEnter the user ID you wish to transfer money to:\n";
			cin >> userId;
			user = clientExists(userId);
			// checks if the user exists (the user that will be getting money from the transfer)
			if (user > 0){
				if (trace){
					traceFile << getTime() << " --- " << clientList[i].getId() << "entered " << userId << " for the user he/she will transfer money to.\n";
				}
				// handels transfering money to another user
				transferToUser(i, user, "chq");
			}
			// user to recieve transfer doesn't exist
			else {
				if (trace){
					traceFile << getTime() << " --- " << clientList[i].getId() << "entered " << userId << " for the user he/she will transfer money to, " << 
						"but that user does not exist. Transaction cancelled.\n";
				}
				cout << "\nThat user does not exist\n";
				transfer(i);
			}
		}
		// chequing account doens't exist
		else {
			if (trace){
				traceFile << getTime() << " --- " << userId << " decided to transfer from his/her chequing account to another user's account, " << 
					"but he/she does not have a chequing account. Transaction cancelled.\n";
			}
			cout << "\nYou don't have a chequing account\n";
			transfer(i);
		}
	}
	// transfer from savings to another user's account
	else if (option == "3"){
		// check if savings account exists
		if (clientList[i].getSav().getIni()){
			if (trace){
				traceFile << getTime() << " --- " << userId << " decided to transfer from his/her savings account to another user's account.\n";
			}
			cout << "\nEnter the user ID you wish to transfer money to:\n";
			cin >> userId;
			user = clientExists(userId);
			// checks if the user exists (the user that will be getting money from the transfer)
			if (user > 0){
				if (trace){
					traceFile << getTime() << " --- " << clientList[i].getId() << "entered " << userId << " for the user he/she will transfer money to.\n";
				}
				// handels transfering money to another user
				transferToUser(i, user, "sav");
			}
			// user to recieve transfer doesn't exist
			else {
				if (trace){
					traceFile << getTime() << " --- " << clientList[i].getId() << "entered " << userId << " for the user he/she will transfer money to, " <<
						"but that user does not exist. Transaction cancelled.\n";
				}
				cout << "\nThat user does not exist\n";
				transfer(i);
			}
		}
		// savings account doens't exist
		else {
			if (trace){
				traceFile << getTime() << " --- " << userId << " decided to transfer from his/her savings account to another user's account, " <<
					"but he/she does not have a savings account. Transaction cancelled.\n";
			}
			cout << "\nYou don't have a savings account\n";
			transfer(i);
		}
	}
	// cancel transfer
	else if (option == "x"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " opted to cancel the transfer process.\n";
		}
		clientOptions(i);
	}
	// invalid input
	else {
		if (trace){
			traceFile << getTime() << " --- " << userId << " entered an invalid input in the transfer process.\n";
		}
		cout << "\nInvalid input\n";
		transfer(i);
	}
}

// handles transfering money to another user's account
void transferToUser(int i, int user, string type){
	cout << "\nEnter:\n0 to transfer to their chequing account\n1 to transfer to their savings account\nx to cancel\n\n ";
	cin >> option;
	// transering to their chequing account
	if (option == "0"){
		// checks if they have a chequing account
		if (clientList[user].getChq().getIni()){
			if (trace){
				traceFile << getTime() << " --- " << clientList[i].getId() << " decided to transfer money to " << clientList[user].getId() << "'s chequing account.\n";
			}
			cout << "\nHow much would you like to transfer?\n";
			cin >> amt;
			if (trace){
				traceFile << getTime() << " --- " << clientList[i].getId() << " enetered $" << amt << " as the amount to transfer.\n";
			}
			// if the transfer is coming from a savings account
			if (type == "sav"){
				// if withdraw is successfull, deposit into the user's account
				if (withdrawCheck(i, "Sav") > 0){
					if (trace){
						traceFile << getTime() << " --- " << clientList[i].getId() << "'s transfer was successfull.\n";
					}
					clientList[user].depChq(amt);
					checkBal(i);
					clientOptions(i);
				}
				// withdraw wasn't successfull, cancel transaction
				else {
					if (trace){
						traceFile << getTime() << " --- " << userId << "'s transfer was unsuccessfull.\n";
					}
					transferToUser(i, user, type);
				}
			}
			// if the transfer is coming from a chequing account
			else {
				// if withdraw is successfull, deposit into the user's account
				if (withdrawCheck(i, "Chq") > 0){
					if (trace){
						traceFile << getTime() << " --- " << clientList[i].getId() << "'s transfer was successfull.\n";
					}
					clientList[user].depChq(amt);
					checkBal(i);
					clientOptions(i);
				}
				// withdraw wasn't successfull, cancel transaction
				else {
					if (trace){
						traceFile << getTime() << " --- " << userId << "'s transfer was unsuccessfull.\n";
					}
					transferToUser(i, user, type);
				}
			}
		}
		// they don't have a chequing account
		else {
			if (trace){
				traceFile << getTime() << " --- " << clientList[i].getId() << " decided to transfer money to " << clientList[user].getId() << 
					"'s chequing account, but he/she does not have a chequing account. Transaction cancelled\n";
			}
			cout << "\nThe user does not have a chequing account\n";
			transferToUser(i, user, type);
		}
	}
	// transfering to their savings
	else if (option == "1"){
		// checks if they have a savings account
		if (clientList[user].getSav().getIni()){
			if (trace){
				traceFile << getTime() << " --- " << clientList[i].getId() << " decided to transfer money to " << clientList[user].getId() << "'s savings account.\n";
			}
			cout << "\nHow much would you like to transfer?\n";
			cin >> amt;
			if (trace){
				traceFile << getTime() << " --- " << clientList[i].getId() << " enetered $" << amt << " as the amount to transfer.\n";
			}
			// if the transfer is coming from a savings account
			if (type == "sav"){
				// if withdraw is successfull, deposit into the user's account
				if (withdrawCheck(i, "Sav") > 0){
					if (trace){
						traceFile << getTime() << " --- " << clientList[i].getId() << "'s transfer was successfull.\n";
					}
					clientList[user].depSav(amt);
					checkBal(i);
					clientOptions(i);
				}
				// withdraw wasn't successfull, cancel transaction
				else {
					if (trace){
						traceFile << getTime() << " --- " << userId << "'s transfer was unsuccessfull.\n";
					}
					transferToUser(i, user, type);
				}
			}
			// if the transfer is coming from a chequing account
			else {
				// if withdraw is successfull, deposit into the user's account
				if (withdrawCheck(i, "Chq") > 0){
					if (trace){
						traceFile << getTime() << " --- " << clientList[i].getId() << "'s transfer was successfull.\n";
					}
					clientList[user].depSav(amt);
					checkBal(i);
					clientOptions(i);
				}
				// withdraw wasn't successfull, cancel transaction
				else {
					if (trace){
						traceFile << getTime() << " --- " << userId << "'s transfer was unsuccessfull.\n";
					}
					transferToUser(i, user, type);
				}
			}
		}
		// they don't have a savings account
		else {
			if (trace){
				traceFile << getTime() << " --- " << clientList[i].getId() << " decided to transfer money to " << clientList[user].getId() <<
					"'s savings account, but he/she does not have a savings account. Transaction cancelled\n";
			}
			cout << "\nThe user does not have a savings account\n";
			transferToUser(i, user, type);
		}
	}
	// cancel transfer
	else if (option == "x"){
		if (trace){
			traceFile << getTime() << " --- " << clientList[i].getId() << "opted to cancel the transfer to another user process.\n";
		}
		transfer(i);
	}
	// invalid input
	else {
		if (trace){
			traceFile << getTime() << " --- " << clientList[i].getId() << " entered an invalid input in the transfer to another user process.\n";
		}
		cout << "\nInvalid input\n";
		transferToUser(i, user, type);
	}
}

// checks if the withdraw is possible and completes the withdraw if it is
// if successfully, return 1. otherwise return 0
int withdrawCheck(int i, string type){
	float checkBal;
	// set checkBal to the chequing balance if that is the type indicated
	if (type == "Chq"){
		checkBal = clientList[i].getChq().getBal();
	}
	// set checkBal to the savings balance if that is the type indicated
	else {
		checkBal = clientList[i].getSav().getBal();
	}
	char ans;
	// if there isn't enough money
	if ((checkBal - amt) < 0){
		cout << "\nThere is insufficient funds to process this transaction.\nRequest Denied. Transaction Cancelled.\n" << endl;
		if (trace){
			traceFile << getTime() << " --- " << userId << "'s withdraw from his/her account was cancelled because of insufficient funds.\n";
		}
		return 0;
	}
	// if the withdraw is being taken from chequing account
	else if (type == "Chq"){
		// if the withdraw will bring the chequing account below $1000 a surcharge of $2 is applied
		if (checkBal - amt < 1000){
			// if there isn't enough money to cover the surcharge and the withdraw
			if ((checkBal - amt - 2) < 0){
				cout << "\nCurrent withdraw subject to $2.00 Surcharge. Insufficient Funds.\nRequest Denied. Transaction Cancelled.\n" << endl;
				if (trace){
					traceFile << getTime() << " --- " << userId << "'s withdraw from his/her account was cancelled because of insufficient funds (couldn't pay surcharge).\n";
				}
				return 0;
			}
			// there is enough money
			else {
				cout << "\nYour balance after withdraw will be less than 1000 and subject to a $2.00 charge\nPress Y to continue or any other key to cancel request: Y/N?\n ";
				cin >> ans;
				// user accepts the surcharge, transaction is successfull
				if (ans == 'Y' || ans == 'y'){
					clientList[i].withChq(amt + 2);
					cout << "Transaction successful. Thank you!\n" << endl;
					if (trace){
						traceFile << getTime() << " --- " << userId << " withdraw was subject to a $2.00 surcharge and (s)he agreed to pay it. Transaction was successful.\n";
					}
					return 1;
				}
				// user declines the surcharge
				else{
					cout << "\nYour transaction has been cancelled. Surcharge was declined by customer.\n" << endl;
					if (trace){
						traceFile << getTime() << " --- " << userId << " withdraw was subject to a $2.00 surcharge and (s)he declined to pay it. Transaction was cancelled.\n";
					}
					return 0;
				}
			}
		}
		// no surcharge, enough money in chequing account
		else {
			clientList[i].withChq(amt);
			cout << "Transaction successful. Thank you!\n" << endl;
			if (trace){
				traceFile << getTime() << " --- " << userId << " withdraw from chequing account was successful.\n";
			}
			return 1;
		}
	}
	// enough money in savings account
	else {
		clientList[i].withSav(amt);
		cout << "Transaction successful. Thank you!\n" << endl;
		if (trace){
			traceFile << getTime() << " --- " << userId << " withdraw from savings account was successful.\n";
		}
		return 1;
	}
}

// prints all the information of the client indicated
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

// manager option menu, completes all manager tasks based on user input
void manager() {
	cout << "\nEnter:\n0 to view the list of clients\n1 to view a client's information\n2 to view the information of all clientele\n3 to view total bank funds"
		<< "\n4 to open an account\n5 to close an account\nx to logout\n\n ";
	cin >> option;
	// view list of clients
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
	//view a single client's information
	else if (option == "1"){
		if (trace){
			traceFile << getTime() << " --- The manager decided to view a clients information.\n";
		}
		cout << "\nEnter the client's user ID: ";
		cin >> userId;
		int i = clientExists(userId);
		// if the user exists, display his/her information
		if (i > 0){
			if (trace){
				traceFile << getTime() << " --- The manager entered " << userId << " as the client to view.\n";
			}
			printInfo(i);
			cout << endl;
			manager();
		}
		// the user doesn't exist
		else {
			if (trace){
				traceFile << getTime() << " --- The manager entered " << userId << " as the client to view, but that client does not exist.\n";
			}
			cout << "\nThat client does not exist\n";
			manager();
		}
	}
	// view all clientele information
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
	// view total bank funds
	else if (option == "3"){
		if (trace){
			traceFile << getTime() << " --- The manager decided to view the total bank funds.\n";
		}
		float savings = 0;
		float chequings = 0;
		// goes through each client and adds their chequing and savings to the totals
		for (int i = 2; i < clientList.size(); i++){
			// if chequing account exists, add balance to total
			if (clientList[i].getChq().getIni()){
				chequings += clientList[i].getChq().getBal();
			}
			// if savings account exists, add balance to total
			if (clientList[i].getSav().getIni()){
				savings += clientList[i].getSav().getBal();
			}
		}
		// print results
		cout << "\nTotal money in chequing: $" << chequings << "\nTotal money in savings: $" << savings << "\nTotal money: $" << chequings + savings << endl;
		manager();
	}
	// open an account for a user
	else if (option == "4"){
		if (trace){
			traceFile << getTime() << " --- The manager decided to open an account for a user.\n";
		}
		cout << "\nEnter the client's user ID: ";
		cin >> userId;
		int i = clientExists(userId);
		// if the user exists
		if (i > 0){
			if (trace){
				traceFile << getTime() << " --- The manager entered " << userId << " as the client to open an account for.\n";
			}
			userId = "manager";
			openAccount(i);
			manager();
		}
		// the user doens't exist
		else {
			if (trace){
				traceFile << getTime() << " --- The manager entered " << userId << " as the client to open an account for, but that client does not exist.\n";
			}
			cout << "\nThat client does not exist\n";
			manager();
		}
	}
	// close an account for a user
	else if (option == "5"){
		if (trace){
			traceFile << getTime() << " --- The manager decided to close an account for a user.\n";
		}
		cout << "\nEnter the client's user ID: ";
		cin >> userId;
		int i = clientExists(userId);
		// if the user exists
		if (i > 0){
			if (trace){
				traceFile << getTime() << " --- The manager entered " << userId << " as the client to close an account for.\n";
			}
			userId = "manager";
			closeAccount(i);
			manager();
		}
		// the user doesn't exist
		else {
			if (trace){
				traceFile << getTime() << " --- The manager entered " << userId << " as the client to close an account for, but that client does not exist.\n";
			}
			cout << "\nThat client does not exist\n";
			manager();
		}
	}
	// manager logs out
	else if (option == "x"){
		if (trace){
			traceFile << getTime() << " --- The manager has logged out. \n\n";
		}
		menu();
	}
	// invalid input
	else {
		if (trace){
			traceFile << getTime() << " --- The manager entered invalid input in the manager option menu.\n";
		}
		cout << "\nInvalid input\n";
		manager();
	}
}

// maintenance person menu
void maint() {
	cout << "\nEnter:\n0 to turn on the execution tracer\n1 to turn off the execution tracer\nx to logout\n\n ";
	cin >> option;
	// turns on tracer
	if (option == "0"){
		// if the tracer is off
		if (!trace) {
			trace = true;
			cout << "\nExecution tracer has been turned on\n";
			traceFile.open("trace.txt", ios::app);
			traceFile << getTime() << " --- Maintenence man turned on execution tracer\n";
			maint();
		}
		// if the tracer is already on
		else {
			cout << "\nExecution tracer already turned on\n";
			traceFile << getTime() << " --- Maintenence man attemped to turn execution tracer on, but it was already on\n";
			maint();
		}
	}
	// turns off tracer
	else if (option == "1"){
		// if the tracer is on
		if (trace){
			trace = false;
			cout << "\nExecution tracer has been turned off\n";
			traceFile << getTime() << " --- Maintenence man turned off execution tracer\n\n";
			traceFile.close();
			maint();
		}
		// the tracer is already off
		else {
			cout << "\nExecution tracer already turned off\n";
			maint();
		}
	}
	// logs out
	else if (option == "x"){
		cout << endl;
		if (trace){
			traceFile << getTime() << " --- Maintenance man logged out.\n\n";
		}
		menu();
	}
	// invalid input
	else {
		if (trace){
			traceFile << getTime() << " --- Maintenance man entered invalid input in the maintenance man option menu.\n";
		}
		cout << "\nInvalid input\n\n";
		maint();
	}
}

// client options menu, does various tasks based on user input
void clientOptions(int i){
	userId = clientList[i].getId();
	cout << "Enter:\n 0 to open a chequing or savings account\n 1 to close an account\n 2 to check balance\n 3 to deposit money\n" 
		<< " 4 to withdraw money \n 5 to transfer funds \n 6 to display transaction history\n x to logout\n\n ";
	cin >> option;
	// open a chequing account
	if (option == "0"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " has started the open account process.\n";
		}
		openAccount(i);
		clientOptions(i);
	}
	// open a savings account
	else if (option == "1"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " has started the close account process.\n";
		}
		closeAccount(i);
		clientOptions(i);
	}
	// check balance
	else if (option == "2"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " has checked his/her account balances.\n";
		}
		checkBal(i);
		clientOptions(i);
	}
	// deposit money
	else if (option == "3"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " has started the deposit process.\n";
		}
		deposit(i);
		clientOptions(i);
	}
	// withdraw money
	else if (option == "4"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " has started the withdraw process.\n";
		}
		withdraw(i);
		clientOptions(i);
	}
	// transfer money
	else if (option == "5"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " has started the transfer money process.\n";
		}
		transfer(i);
		clientOptions(i);
	}
	// view transaction history
	else if (option == "6"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " has decided to display trasaction history for his/her accounts.\n";
		}
		// if chequing account exists, display transaction history
		if (clientList[i].getChq().getIni()){
			cout << "\nTransaction history for chequing account:\n";
			// prints transaction history
			clientList[i].getChq().history();
		}
		// if savings account exists, display transaction history
		if (clientList[i].getSav().getIni()){
			cout << "\nTransaction history for savings account:\n";
			// prints transaction history
			clientList[i].getSav().history();
		}
		clientOptions(i);
	}
	// log out
	else if (option == "x"){
		if (trace){
			traceFile << getTime() << " --- " << userId << " has logged out.\n\n";
		}
		menu();
	}
	// invalid input
	else {
		if (trace){
			traceFile << getTime() << " --- " << userId << " entered invalid input in the client option menu.\n";
		}
		cout << "\nInvalid input\n";
		clientOptions(i);
	}
}

// sign in with user id and pin
void signIn(){
	cout << "\nEnter your user ID: ";
	cin >> userId;
	int i = clientExists(userId);
	// check if the user exists
	if (i >= 0){
		if (trace){
			traceFile << getTime() << " --- Unkown user entered " << userId << " as the user ID to sign into\n";
		}
		// loops until correct pin is entered (user can break out by cancelling)
		while (true){
			cout << "\nEnter your pin or x to cancle: ";
			cin >> pin;
			// if the pin entered matched the correct pin
			if (pin == clientList[i].getPwd()){
				// if the user is the manager
				if (clientList[i].getId() == "manager"){
					if (trace){
						traceFile << "\n" << getTime() << " --- The bank manager entered the correct pin and is now logged in.\n";
					}
					cout << "\nYou are now logged in as the bank manager.\n\n";
					manager();
					break;
				}
				// if the user is the maintenance person
				else if (clientList[i].getId() == "maintenance"){
					if (trace){
						traceFile << "\n" << getTime() << " --- The maintenance man entered the correct pin and is now logged in.\n ";
					}
					cout << "\nYou are now logged in as the maintenance man.\n\n";
					maint();
					break;
				}
				// the user is a client
				else {
					if (trace){
						traceFile << "\n" << getTime() << " --- " << userId << " enetered the correct pin and is now logged in.\n";
					}
					cout << "\nYou are now logged in as " << userId << ".\n\n";
					clientOptions(i);
					break;
				}
			}
			// go back to menu if x is entered
			else if (pin == "x"){
				if (trace){
					traceFile << getTime() << " --- Unkown user opted to cancel the sign in process.\n";
				}
				cout << endl;
				menu();
			}
			// invalid input (needs to be 4 characters)
			else {
				if (trace){
					traceFile << getTime() << " --- Unkown user entered the wrong pin to log into " << userId << "'s account.\n";
				}
				cout << "\nInvalid pin.\n";
			}
		}
	}
	// the user does not exist, can't sign in
	else {
		if (trace){
			traceFile << getTime() << " --- Unkown user entered " << userId << " as the user ID to sign into, but that user does not exist\n";
		}
		cout << "\nThe user ID entered does not exist.\n\n";
		menu();
	}
}

// allows a user to sign up and become a new bank client
void signUp(){
	cout << "\nEnter the user ID for your new account: ";
	cin >> userId;
	int i = clientExists(userId);
	// if the user doesn't already exist
	if (i < 0){
		// loops until account is created
		do {
			if (trace){
				traceFile << getTime() << " --- Unknown user entered " << userId << " as their user ID.\n";
			}
			cout << "\nEnter the 4 character pin for your new account: ";
			cin >> pin;
			// checks pin length
			if (pin.length() == 4){
				if (trace){
					traceFile << getTime() << " --- Unknown user entered " << pin << " as their PIN.\n";
				}
				cout << "\nTo finish creating your new account, you must open either a chequing or savings account\n";
				clientList.push_back(Client(userId, pin));
				i = clientExists(userId);
				// checks if the user opened a chequing or savings account
				if (openAccount(i)){
					cout << "\nAccount with user ID " << userId << " was successfully created.";
					cout << "\nYou are now logged in as " << userId << ".\n\n";
					if (trace){
						traceFile << "\n" << getTime() << " --- " << userId << "'s account was successfully created and (s)he is now logged in.\n";
					}
					clientOptions(i);
				}
				// user didn't opened a chequing or savings account. user account not created because they need a chequing or savings account to be a client
				else {
					cout << "Account with user ID " << userId << " was not created.\n\n";
					if (trace){
						traceFile << getTime() << " --- Unkown user failed to create the account " << userId << " because (s)he didn't open a chequing or savings account.\n";
					}
					clientList.pop_back();
					menu();
				}
			}
			// invalid pin
			else {
				if (trace){
					traceFile << getTime() << " --- Unknown user entered " << pin << " as their pin, but it invalid.\n";
				}
				cout << "\nInvalid pin\n";
			}
		} while (pin.length() != 4);
	}
	// the user already exists
	else {
		cout << "\nThat user ID already exists\n\n";
		if (trace){
			traceFile << getTime() << " --- Unknown user tried to sign up as " << userId << ", but that account already exists.\n";
		}
		menu();
	}
}

// returns the current time (used for execution traces)
string getTime(){
	now = time(0);
	currentTime = ctime(&now);
	return currentTime;
}

// main menu, sign in/up or quit
void menu(){
	cout << "Welcome, enter:\n\n 0 to sign in\n 1 to sign up\n q to quit\n\n ";
	cin >> option;
	// sign in
	if (option == "0"){
		if (trace){
			traceFile << getTime() << " --- Unknown user started sign in process.\n";
		}
		signIn();
	}
	// sign up
	else if (option == "1"){
		if (trace){
			traceFile << getTime() << " --- Unknown user started sign up process.\n";
		}
		signUp();
	}
	// close program
	else if (option == "q"){
		if (trace){
			traceFile << getTime() << " --- Unknown user shut down program, execution tracer is turned off.\n";
			traceFile.close();
		}
		exit(0);
	}
	// invalid input
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