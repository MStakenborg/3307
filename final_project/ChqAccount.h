/*
* ChqAccount.h
*
*  Created on: Nov 29, 2014
*      Author: Team 14
*/

#ifndef CHQACCOUNT_H_
#define CHQACCOUNT_H_
#include "Account.h"

class ChqAccount : public Account {

protected:

	float creditLimit;
	float creditDebt;
	float monthlyTotal;
	float outstandingDebt;
	std::vector<std::string>creditHist;
	bool frozen;
	bool fullAmount;

public:
	ChqAccount();
	ChqAccount(float, std::string, float, bool);
	~ChqAccount();
	bool payment(float);
	bool depositToCredit(float amt);
	void applyPayment(float);
	void purchase(float);
	void creditHistory();
	void freeze();
	void unfreeze();
	bool getFreeze();
	bool getFullAmount();
	float getDebt();
	void interest();
	void resetHistory();
	float getOutstandingDebt();

};

#endif /* ACCOUNT_H_ */
