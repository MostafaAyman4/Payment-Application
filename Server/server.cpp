#include <iostream>
#include "server.h"
#include <string.h>

using namespace std;


/*ST_accountsDB_t DataBase[255] =
{   {20000.00 ,RUNNING, "1467938765494732"},
	{10400.00 ,RUNNING, "0077106374661323"},
	{4000.00  ,RUNNING, "5399353562786443"},
	{7000.00  ,BLOCKED, "8989374615436851"},
	{5400.00  ,RUNNING, "6952362058527242"},
	{566.00   ,RUNNING, "4350621408617612"}
};
*/

ST_transaction_t Transactions[255]; // 
ST_transaction_t* list_saved;
EN_transState_t t_state;
node* point;
uint32_t i = 0;
uint32_t counting = 0;

Linked_List Data_Base_Linkedd;

void insert_data(void) {

	Data_Base_Linkedd.Insert(20000.00, RUNNING, "1467938765494732");
	Data_Base_Linkedd.Insert(10400.00, RUNNING, "0077106374661323");
	Data_Base_Linkedd.Insert(4000.00, RUNNING, "5399353562786443");
	Data_Base_Linkedd.Insert(7000.00, BLOCKED, "8989374615436851");
	Data_Base_Linkedd.Insert(5400.00, RUNNING, "6952362058527242");
	Data_Base_Linkedd.Insert(566.00, RUNNING, "4350621408617612");
}

/*
					   -------------------------------------
							  check if account in data base or not
					   ------------------------------------

*/
EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
		point = Data_Base_Linkedd.Search_by_value(cardData->primaryAccountNumber);

		if (point != NULL)
		{
			return SERVER_OK;
		}
	
	return ACCOUNT_NOT_FOUND;
}
//---------------------------------------------------------------------------------------------------------------------------------------

EN_accountStatee_t isBlockedAccount()
{
	return point->state;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if ((*termData).transAmount < point->balance)
	{
		return SERVER_OK;
	}
	return LOW_BALANCE;
}

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{

	if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND)
	{
		transData->transState = FRAUD_CARD;
		t_state = FRAUD_CARD;
		return FRAUD_CARD;
	}
	if (isBlockedAccount() == BLOCKED)
	{
		transData->transState = DECLINED_STOLEN_CARD;
		t_state = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}
	if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE)
	{
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		t_state = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}

	
	transData->transState = APPROVED;
	t_state = APPROVED;

	cout << "\nYour old balance is : " << point->balance;

	point->balance = (point->balance - (*transData).terminalData.transAmount);

	cout << "\nyour new balance is : " << point->balance;

	return APPROVED;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	(*transData).transactionSequenceNumber = i;
	if ((*transData).transactionSequenceNumber < 255)  // 
	{
		//transData = transData + i;  
		list_saved = transData;
		Transactions[(*transData).transactionSequenceNumber].cardHolderData = transData->cardHolderData;
		Transactions[(*transData).transactionSequenceNumber].terminalData = (*transData).terminalData;
		Transactions[transData->transactionSequenceNumber].transState = transData->transState;
		Transactions[(*transData).transactionSequenceNumber].transactionSequenceNumber = (*transData).transactionSequenceNumber + 1;

		i++;
		listSavedTransactions();
		
		
		return SERVER_OK;
	}
	return SAVING_FAILED;
}

void listSavedTransactions(void)
{
	cout << "\n\n\n#############################################################\n" << endl;
	cout << "Transaction Sequence Number: " <<  i  << endl;
	cout << "Transaction Date: " << list_saved->terminalData.transactionDate << endl;
	cout << "Transaction Amount: " << list_saved->terminalData.transAmount << endl;

	if ((t_state) == APPROVED)
		cout << "Transaction State is: Approved\n";

	if ((t_state) == FRAUD_CARD)
		cout << "Transaction State is: fraud card\n";

	if ((t_state) == DECLINED_INSUFFECIENT_FUND)
		cout << "Transaction State is:  Insufficient fund\n";

	if ((t_state) == DECLINED_STOLEN_CARD)
		cout << "Transaction State is:  STOLEN_CARD\n";



	cout << "Terminal Max Amount: " << (list_saved->terminalData.maxTransAmount) << endl;

	cout << "Cardholder Name: " << (list_saved->cardHolderData.cardHolderName) << endl;

	cout << "PAN: " << (list_saved->cardHolderData.primaryAccountNumber) << endl;

	cout << "Card Expiration Date: " << (list_saved->cardHolderData.cardExpirationDate) << endl;

	cout << "\n#############################################################\n";
}

