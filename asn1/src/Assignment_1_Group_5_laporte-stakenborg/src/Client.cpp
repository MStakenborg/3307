/*
* Client.cpp
*
*  Created on: Sep 21, 2014
*      Author: Team 5
*/

#include "Client.h"
#include <iostream>
#include <string>

using namespace std;

string id;
string pwd;
Account chqAcc;
Account savAcc;


/*constructors*/

/*default constructor*/
Client::Client() {
}

Client::Client(string id, string pwd) {
	this->id = id;
	this->pwd = pwd;
}

/*deconstructor */
Client::~Client(void){

}

// returns id
string Client::getId() {
	return id;
}

// returns pin
string Client::getPwd() {
	return pwd;
}

// returns chequing account
Account Client::getChq(){
	return chqAcc;
}

// returns savings account
Account Client::getSav(){
	return savAcc;
}

// sets chequing account to account passed in
void Client::setChq(Account newChq){
	chqAcc = newChq;
}

// sets savings account to account passed in
void Client::setSav(Account newSav){
	savAcc = newSav;
}

// sets id
void Client::setId(string newId){
	id = newId;
}

// sets pin
void Client::setPwd(string newPwd){
	pwd = newPwd;
}

// deposit into chequing
void Client::depChq(float amt){
	chqAcc.addBal(amt);
}

// deposit into savings
void Client::depSav(float amt){
	savAcc.addBal(amt);
}

// withdraw from chequing
void Client::withChq(float amt){
	return chqAcc.subBal(amt);
}

// withdraw from savings
void Client::withSav(float amt){
	return savAcc.subBal(amt);
}