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

string Client::getId() {
	return id;
}

string Client::getPwd() {
	return pwd;
}

Account Client::getChq(){
	return chqAcc;
}

Account Client::getSav(){
	return savAcc;
}

void Client::setChq(Account newChq){
	chqAcc = newChq;
}

void Client::setSav(Account newSav){
	savAcc = newSav;
}

void Client::setId(string newId){
	id = newId;
}

void Client::setPwd(string newPwd){
	pwd = newPwd;
}

void Client::depChq(float amt){
	chqAcc.addBal(amt);
}

void Client::depSav(float amt){
	savAcc.addBal(amt);
}

int Client::withChq(float amt){
	return chqAcc.subBal(amt);
}

int Client::withSav(float amt){
	return savAcc.subBal(amt);
}