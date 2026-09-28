#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook,int index[]);
int editContact(AddressBook *addressBook,int index[]);
int deleteContact(AddressBook *addressBook,int index[]);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
void display(AddressBook *addressBook,int index[],int i);
int validatename(AddressBook *addressBook,int count);
int validatephone(AddressBook *addressBook,int count);
int validateemail(AddressBook *addressBook,int count);
int searchbyname(AddressBook *addressBook,int index[]);
int searchbyphone(AddressBook *addressBook,int index[]);
int searchbyemail(AddressBook *addressBook,int index[]);

#endif
