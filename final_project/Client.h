/*
* Client.h
*
*  Created on: Sep 21, 2014
*      Author: Team 5
*/

#ifndef CLIENT_H_
#define CLIENT_H_
#include "Account.h"
#include "ChqAccount.h"

class Client {

protected:
	std::string id;
	std::string pwd;
	ChqAccount chqAcc;
	Account savAcc;
	std::vector<std::string> notifications;

public:
	Client();
	Client(std::string, std::string);
	~Client();
	std::string getId();
	std::string getPwd();
	ChqAccount getChq();
	Account getSav();
	void setChq(ChqAccount);
	void setSav(Account);
	void setId(std::string);
	void setPwd(std::string);
	void depChq(float);
	void depSav(float);
	void withChq(float);
	void withSav(float);
	void notify(std::string);
	void getNotifications();
	void purchase(float);
	bool payment(float amt);
	bool depositToCredit(float amt);
};

#endif /* CLIENT_H_ */

