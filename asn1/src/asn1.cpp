#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "Client.h"
#include "Account.h"
#include <vector>
#include <iomanip>

using namespace std;

float amt;		//amount for withdraw or deposit
string userId;
string pin;
string option;
vector<Client> clientList;
bool trace;

void menu();
void signUp();
void signIn();
void clientOptions(int i);
void transferToUser(int i, int user, string type);
void printInfo(int i);


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
			cout << "Deposit transaction successful. Thank you!\n\n";
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
			cout << "Deposit ransaction successful. Thank you!\n\n";
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
			cout << "\nHow much would you like to withdraw today?\n\n";
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

void transfer(int i) {

	int user;
	cout << "\nEnter:\n0 to transfer from your chequing account to your savings account\n1 to transfer from your savings account to your chequing account\n" <<
			"2 to transfer from your chequing account to another user's account\n3 to transfer from your savings account to another user's account\nx to cancel\n\n ";
	cin >> option;
	if (option == "0"){
		if (clientList[i].getChq().getIni() && clientList[i].getSav().getIni()){
			cout << "\nHow much would you like to transfer?\n";
			cin >> amt;
			if (clientList[i].withChq(amt) > 0){
				clientList[i].depSav(amt);
				checkBal(i);
				clientOptions(i);
			}
			else {
				transfer(i);
			}
		}
		else {
			cout << "\nYou don't have a both a chequing and savings account\n";
			transfer(i);
		}

	}
	else if (option == "1"){
		if (clientList[i].getChq().getIni() && clientList[i].getSav().getIni()){
			cout << "\nHow much would you like to transfer?\n";
			cin >> amt;
			if (clientList[i].withSav(amt) > 0){
				clientList[i].depChq(amt);
				checkBal(i);
				clientOptions(i);
			}
			else {
				transfer(i);
			}
		}
		else {
			cout << "\nYou don't have both a chequing and savings account\n";
			transfer(i);
		}
	}
	else if (option == "2"){
		if (clientList[i].getChq().getIni()){
			cout << "\nEnter the user ID you wish to transfer money to:\n";
			cin >> userId;
			user = clientExists(userId);
			if (user > 0){
				transferToUser(i, user, "chq");
			}
			else {
				cout << "\nThat user does not exist\n";
				transfer(i);
			}
		}
		else {
			cout << "\nYou don't have a chequing account\n";
			transfer(i);
		}
	}
	else if (option == "3"){
		if (clientList[i].getSav().getIni()){
			cout << "\nEnter the user ID you wish to transfer money to:\n";
			cin >> userId;
			user = clientExists(userId);
			if (user > 0){
				transferToUser(i, user, "sav");
			}
			else {
				cout << "\nThat user does not exist\n";
				transfer(i);
			}
		}
		else {
			cout << "\nYou don't have a savings account\n";
			transfer(i);
		}
	}
	else if (option == "x"){
		clientOptions(i);
	}
	else {
		cout << "\nInvalid input\n";
		transfer(i);
	}
}

void transferToUser(int i, int user, string type){
	cout << "\nEnter:\n0 to transfer to their chequing account\n1 to transfer to their savings account\nx to cancel\n\n ";
	cin >> option;
	if (option == "0"){
		if (clientList[user].getChq().getIni()){
			cout << "\nHow much would you like to transfer?\n";
			cin >> amt;
			if (type == "sav"){
				if (clientList[i].withSav(amt) > 0){
					clientList[user].depChq(amt);
					checkBal(i);
					clientOptions(i);
				}
				else {
					transferToUser(i, user, type);
				}
			}
			else {
				if (clientList[i].withChq(amt) > 0){
					clientList[user].depChq(amt);
					checkBal(i);
					clientOptions(i);
				}
				else {
					transferToUser(i, user, type);
				}
			}
		}
		else {
			cout << "\nThe user does not have a chequing account\n";
			transferToUser(i, user, type);
		}
	}
	else if (option == "1"){
		if (clientList[user].getSav().getIni()){
			cout << "\nHow much would you like to transfer?\n";
			cin >> amt;
			if (type == "sav"){
				if (clientList[i].withSav(amt) > 0){
					clientList[user].depSav(amt);
					checkBal(i);
					clientOptions(i);
				}
				else {
					transferToUser(i, user, type);
				}
			}
			else {
				if (clientList[i].withChq(amt) > 0){
					clientList[user].depSav(amt);
					checkBal(i);
					clientOptions(i);
				}
				else {
					transferToUser(i, user, type);
				}
			}
		}
		else {
			cout << "\nThe user does not have a savings account\n";
			transferToUser(i, user, type);
		}
	}
	else if (option == "x"){
		transfer(i);
	}
	else {
		cout << "\nInvalid input\n";
		transferToUser(i, user, type);
	}
}

void printInfo(int i){
	Client client = clientList[i];
	cout << setw(20) << left << "\nID: " << client.getId() << "Pin: " << client.getPwd() << "Chequing: $" << client.getChq().getBal() << "Savings: $" << client.getSav().getBal();
}

void manager() {
	cout << "\nEnter:\n0 to view the list of clients\n1 to view a client's information\n2 to view the information of all clientele\n3 to open an account"
		<< "\n4 to close an account\nx to logout\n\n ";
	cin >> option;
	if (option == "0"){
		cout << endl;
		for (int i = 2; i < clientList.size(); i++){
			cout << clientList[i].getId() << endl;
		}
		manager();
	}
	else if (option == "1"){
		cout << "\nEnter the client's user ID: ";
		cin >> userId;
		int i = clientExists(userId);
		if (i > 0){
			printInfo(i);
			manager();
		}
		else {
			cout << "\nThat client does not exist\n";
			manager();
		}
	}
	else if (option == "2"){
		for (int i = 2; i < clientList.size(); i++){
			printInfo(i);
		}
		manager();
	}
	else if (option == "3"){

	}
	else if (option == "4"){

	}
	else if (option == "x"){
		menu();
	}
	else {
		cout << "\nInvalid input\n";
		manager();
	}
}

void maint() {

}

void clientOptions(int i){
	cout << "Enter:\n 0 to open a chequing or savings account\n 1 to close an account\n 2 to check balance\n 3 to deposit money\n" 
		<< " 4 to withdraw money \n 5 to transfer funds \n x to logout\n\n ";
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
		transfer(i);
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
					manager();
				}
				else if (clientList[i].getId() == "maintenance"){
					cout << "\nYou are now logged in as the maintenance man.\n\n";
					maint();
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
	return 0;
}