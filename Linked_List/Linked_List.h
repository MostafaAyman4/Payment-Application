#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED


#include <string>
using namespace std;

typedef enum EN_accountStatee_t
{
    RUNNING,
    BLOCKED

}EN_accountStatee_t;


struct node
{
    float balance;
    EN_accountStatee_t state;
    string primaryAccountNumber;
    node* next;     /* data */
};



class Linked_List {
private:
    node* head;
public:

    Linked_List();
    bool IsEmpty();
    void Insert(float balance, EN_accountStatee_t state, string primaryAccountNumber);
    node* Search_by_value(string primaryAccountNumber);

};



#endif // LINKED_LIST_H_INCLUDED
