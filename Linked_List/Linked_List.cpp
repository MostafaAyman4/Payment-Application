#include "Linked_List.h"
#include <iostream>
using namespace std;

Linked_List::Linked_List() {
    head = NULL;
}


bool Linked_List::IsEmpty()
{
    if (head == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}


void Linked_List::Insert(float balance, EN_accountStatee_t state, string primaryAccountNumber){
    node* new_node = new node;
    new_node->balance = balance;
    new_node->state = state;
    new_node->primaryAccountNumber = primaryAccountNumber;
    new_node->next = NULL;

    if (head == NULL) {
        head = new_node;
        return;
    }
    else {
        node* current_node = head;
        while (current_node->next != NULL) {
            current_node = current_node->next;
        }
        current_node->next = new_node;
    }
}


node* Linked_List::Search_by_value(string primaryAccountNumber) {
    node* current_node = head;
    if (current_node->primaryAccountNumber == primaryAccountNumber) {
        return current_node;
    }
    while (current_node != NULL) {
        if (current_node->primaryAccountNumber == primaryAccountNumber) {
            return current_node;
        }
        current_node = current_node->next;
    }
    cout << "\nTHIS IS VALUE DOES NOT EXIST" << endl;
    return NULL;
}






