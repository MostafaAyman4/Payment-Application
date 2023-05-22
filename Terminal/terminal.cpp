#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "terminal.h"
#include <time.h>
#include <string>

using namespace std;

float MaxAmountToTransact = 5000;
ST_terminalData_t date;


/*
       -----------------------------------------------------------------------------------------------------------------
              check if transaction amount is valid or not by this site https://www.geeksforgeeks.org/luhn-algorithm/
       ------------------------------------------------------------------------------------------------------------------
*/

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{

    uint32_t count = 0;
    int32_t sum = 0,
        second = 0;
    int length = 16;      // (cardData->primaryAccountNumber).length();

    for (int i = length - 1; i >= 0; i--)
    {
        count = (*cardData).primaryAccountNumber[i] - '0';
        if (second == 1)
            count = count * 2;

        sum += count / 10;
        sum += count % 10;
        second = !second;

    }
    if (sum % 10 == 0) {
        return OK;
    }
    else {
        return INVALID_CARD;
    }
}
string day;
string month;
string year;


/**

---------------------------------------------------------
now we get date from system
---------------------------------------------------------

**/

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
    time_t t = time(NULL);
    struct tm real_time = *localtime(&t);

    day = to_string(real_time.tm_mday);           // Get Day from system and store it in day
    month = to_string(real_time.tm_mon + 1);        // Get Month from system and store it in month
    year = to_string(real_time.tm_year + 1900);       // Get Year from system and store it in year

    if (real_time.tm_mday < 10)
    {
        ((*termData).transactionDate[0]) = '0';
        ((*termData).transactionDate[1]) = day[0];
    }
    else {
        ((*termData).transactionDate[0]) = day[0];
        ((*termData).transactionDate[1]) = day[1];
    }

    ((*termData).transactionDate[2]) = '/';

    // Storing MM
    if (stoi(month) < 10)
    {
        ((*termData).transactionDate[3]) = '0';
        ((*termData).transactionDate[4]) = month[0];

    }
    else {
        ((*termData).transactionDate[3]) = month[0];
        ((*termData).transactionDate[4]) = month[1];
    }

    // Storing YYYY
    ((*termData).transactionDate[5]) = '/';
    ((*termData).transactionDate[6]) = year[0];
    ((*termData).transactionDate[7]) = year[1];
    ((*termData).transactionDate[8]) = year[2];
    ((*termData).transactionDate[9]) = year[3];
    ((*termData).transactionDate[10]) = '\0';

    cout <<"Date is : "<<(*termData).transactionDate<<endl;

    return OK;
}
/*
                       ------------------------------------------------------
                              check if card is expired or not
                       ------------------------------------------------------
*/

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
    // cardExpirationDate MM/YY      transactionDate DD/MM/YYYY


    if (((*cardData).cardExpirationDate[3]) < ((*termData).transactionDate[8]))                    // check year first
        return EXPIRED_CARD;

    if (((*cardData).cardExpirationDate[3]) == ((*termData).transactionDate[8]))

        if (((*cardData).cardExpirationDate[4]) < ((*termData).transactionDate[9]))
            return EXPIRED_CARD;

    // ------------------------------------------------------------------------------------------------//

    if (((*cardData).cardExpirationDate[0]) < ((*termData).transactionDate[3]))
        return EXPIRED_CARD;

    if (((*cardData).cardExpirationDate[0]) == ((*termData).transactionDate[3]))
    {
        if (((*cardData).cardExpirationDate[1]) < ((*termData).transactionDate[4]))
            return EXPIRED_CARD;
    }




    cout << "card isn't expired yet" << endl;;
    return OK;

}

/*
                       ------------------------------------------------------
                              check if card is valid or not
                       ------------------------------------------------------
*/


EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
    // should be more than 0 to make transaction
    cout << "Please enter the Transaction Amount: ";

    cin >> termData->transAmount;
    if ((*termData).transAmount <= 0)
        return INVALID_AMOUNT;

    cout << "Your Transaction Amount is: " << (*termData).transAmount << endl;
    cout << "------------------------------------------------------------------" << endl;

    return OK;
}

/*
                       ---------------------------
                              set max amount
                       ---------------------------

*/
EN_terminalError_t setMaxAmountToTransact(ST_terminalData_t* termData)
{
    // Prints max transaction amount to let user know before typing the transaction

    (*termData).maxTransAmount = MaxAmountToTransact;

    cout << "Max Transaction Amount is : " << (*termData).maxTransAmount << endl;

    return OK;
}
/*
                       --------------------------------------------------
                              compare transaction amount to maximum
                       --------------------------------------------------

*/

EN_terminalError_t isBelowMaxAmountToTransact(ST_terminalData_t* termData)
{
    // Check if the Transactions Amount is less than the Max Amount

    if (((*termData).transAmount - (*termData).maxTransAmount) > 0) {
        return EXCEED_MAX_AMOUNT;
    }

    return OK;
}

