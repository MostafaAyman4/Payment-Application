#ifndef SERVER_H
#define SERVER_H

#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Linked_List/Linked_List.h"

#include "../std_types.h"



typedef enum EN_transState_t
{
	APPROVED,
	DECLINED_INSUFFECIENT_FUND,
	DECLINED_STOLEN_CARD,
	FRAUD_CARD,
	INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef struct ST_transaction_t         //
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;

typedef enum EN_serverError_t
{
	SERVER_OK,
	SAVING_FAILED,
	TRANSACTION_NOT_FOUND,
	LOW_BALANCE,
	ACCOUNT_NOT_FOUND,
	BLOCKED_ACCOUNT
}EN_serverError_t;


typedef struct ST_accountsDB_t
{
	float balance;
	EN_accountStatee_t state;
	unsigned char primaryAccountNumber[20];
}ST_accountsDB_t;

EN_serverError_t isValidAccount(ST_cardData_t* cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData);
EN_serverError_t saveTransaction(ST_transaction_t* transData);
EN_transState_t recieveTransactionData(ST_transaction_t* transData);
void insert_data(void);
EN_accountStatee_t isBlockedAccount();

void listSavedTransactions(void);


#endif // !SERVER_H
