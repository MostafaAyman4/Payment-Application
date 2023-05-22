#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "../Server/server.h"
#include "application.h"
#include <string>
using namespace std;



int appStart(void)
{
	insert_data();


	ST_cardData_t card_Data;
	ST_cardData_t* cardData = &card_Data;

	ST_terminalData_t terminal_Data;
	ST_terminalData_t* termData = &terminal_Data;

	ST_transaction_t transacton_Data;
	ST_transaction_t* trans_Data = &transacton_Data;

	/**
	-----------------------------------------------------
	call get card data functions at first of the program
	-----------------------------------------------------
	**/

		if (getCardHolderName(cardData) == WRONG_NAME) // get card holder name and check it
		{
			cout << "Wrong Name !\n";
			return WRONG_NAME;

		}


		if (getCardExpiryDate(cardData) == WRONG_EXP_DATE) // get card expiry date and check it
		{
			cout << "Wrong Expiry Date !\n";
			return WRONG_EXP_DATE;

		}


		if (getCardPAN(cardData) == WRONG_PAN) // get card primary account number and check it
		{
			cout << "Wrong PAN !\n";
			return WRONG_PAN;

		}



		if (isValidCardPAN(cardData) == INVALID_CARD)        // check luhn algorithm 
		{
			cout << "Card is Invalid Please enter right Pan\n";
			return 0;
		}
		else
			cout << "                                        Card is valid :" << endl;

		getTransactionDate(termData);  // get real date from system

		if (isValidAccount(cardData) == ACCOUNT_NOT_FOUND) {

			cout << "account isn't in the database \n\n";

		}


		if (isBlockedAccount() == RUNNING) {  // check if card running or blocked
			cout << "RUNNING\n";
		}
		if (isBlockedAccount() == BLOCKED) {
			cout << "your card is BLOCKED try to contact the bank to know why .\n\n";

		}

		if (isCardExpired(cardData, termData) == EXPIRED_CARD) // check if card is expired or not
		{
			cout << "Your Card is Expired, Try to contact the bank to renew it soon . ";
			return 0;
		}


		if (setMaxAmountToTransact(termData) == INVALID_MAX_AMOUNT)
		{
			cout << "Invalid Max Amount";
			return 0;
		}

		if (getTransactionAmount(termData) == INVALID_AMOUNT) //get transaction amount from user
		{
			cout << "wrong Amount, Please Enter the right Amount \n";
			return 0;
		}

		if (isBelowMaxAmountToTransact(termData) == EXCEED_MAX_AMOUNT) // check if transaction amount is greater than maximum
		{
			cout << "Sorry ,but you entered more than allowed of 5000 ";
			return 0;
		}



		trans_Data->cardHolderData = card_Data;
		trans_Data->terminalData = terminal_Data;

		switch (recieveTransactionData(trans_Data))
		{
		case DECLINED_STOLEN_CARD:
			cout << "\nTransaction Declined This Card Is Stolen and has been blocked \n";
			saveTransaction(trans_Data);
			break;

		case FRAUD_CARD:
			cout << "\nTransaction Declined This Card Is Fraud, Please Return It To The Nearest bank to check it\n";
			saveTransaction(trans_Data);
			break;


		case APPROVED:
			cout << "\nTransaction was successfull, Have a good day\n";
			saveTransaction(trans_Data);
			break;

		case DECLINED_INSUFFECIENT_FUND:
			cout << "\nTransaction Declined because you entered more than allowed of balance \n";
			saveTransaction(trans_Data);
			break;


		}
	}
	
