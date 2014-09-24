/*
* Client.h
*
*  Created on: Sep 21, 2014
*      Author: Team 5
*/

#ifndef CLIENT_H_
#define CLIENT_H_
#include <string>
#include "Account.h"

using namespace std;

class Client {

protected:
	string id;
	string pwd;
	Account chqAcc;
	Account savAcc;

public:
	Client();
	Client(string, string);
	~Client();
	string getId();
	string getPwd();
	Account getChq();
	Account getSav();
	void setChq(Account);
	void setSav(Account);
	void setId(string);
	void setPwd(string);
	void depChq(float);
	void depSav(float);
	void withChq(float);
	void withSav(float);
};

#endif /* CLIENT_H_ */

