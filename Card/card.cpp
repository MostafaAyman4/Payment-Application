#define _CRT_SECURE_NO_WARNINGS   

#include <iostream>
#include <string>
#include <cctype>
#include "Card.h"
using namespace std;



/*
                       -------------------------------------
                              get name from user
                       ------------------------------------

*/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
    cout << "Please enter Card Holder's Name: ";
    cin.getline(cardData->cardHolderName,26);

    if (strlen(cardData->cardHolderName) < 16 || strlen(cardData->cardHolderName) >= 25 || strlen(cardData->cardHolderName) == NULL) {
        return WRONG_NAME;
    }
    for (int i = 0; i < strlen(cardData->cardHolderName); i++) {
        if (isdigit(cardData->cardHolderName[i])) {
            return WRONG_NAME;

        }
    }
    cout << "Hello: " << cardData->cardHolderName << endl;
    return Card_OK;
}



/*
                       -------------------------------------
                                 get pan from user
                       -------------------------------------

*/

EN_cardError_t getCardPAN(ST_cardData_t* cardData) // get card pan from user
{

    cout << "Please enter primary account number : ";



    int length, i;

    cin.getline(cardData->primaryAccountNumber, 20);

    length = strlen(cardData->primaryAccountNumber);



    // Check on the Card PAN format
    if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19 || (cardData->primaryAccountNumber) == NULL) // check if its less than 16 and more than 19
    {
        return WRONG_PAN;
    }

    for (i = 0; i < length; i++)
    {
        if (!isdigit(cardData->primaryAccountNumber[i]))
        {
            cout << "Entered input is not a number\n";
            return WRONG_PAN;
        }
    }

    cout << "Card PAN number is: " << cardData->primaryAccountNumber << endl;
    cout << ("-----------------------------------------------------------\n");
    return Card_OK;

}

/*
                       ---------------------------------------------
                              get date of espiration from user
                       --------------------------------------------

*/


EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)  //get expiry date from user at format MM/YY
{
    cout << "Please enter card Expiry Date in the format of MM/YY: ";


    cin.getline(cardData->cardExpirationDate, 6);


    int first_month = cardData->cardExpirationDate[1];
    int second_month = cardData->cardExpirationDate[0];


        if (strlen(cardData->cardExpirationDate) != 5 || (cardData->cardExpirationDate) == NULL)
        return WRONG_EXP_DATE;

        if (!isdigit(cardData->cardExpirationDate[0]) || !isdigit(cardData->cardExpirationDate[1]))
            return WRONG_EXP_DATE;

        if ((cardData->cardExpirationDate[2]) != '/')
            return WRONG_EXP_DATE;

        if (!isdigit(cardData->cardExpirationDate[3]) || !isdigit(cardData->cardExpirationDate[4]))
            return WRONG_EXP_DATE;

        if ((cardData->cardExpirationDate[0] == '0') && ((cardData->cardExpirationDate[1]) == '0'))
            return WRONG_EXP_DATE;

        if ((cardData->cardExpirationDate[4] == '0') && ((cardData->cardExpirationDate[3]) == '0'))
            return WRONG_EXP_DATE;

        if ((first_month) > '2') {               // MN  M is second_month and N is first_month
            if (second_month >= '1') {
                return WRONG_EXP_DATE;
            }
        }
       
    

    cout << "The Expiry Date is: " << cardData->cardExpirationDate << endl;
    return Card_OK;

}