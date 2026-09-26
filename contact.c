#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include <ctype.h>
//#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the choosen criteria
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    
	printf("Creating a new contact...\n\n");
    int result;
    //name
    do{
    printf("Enter the name of the contact: ");
    scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].name);
    result=validatename(addressBook);
    }while(result!=1);

    //phone number 
    do{
    printf("Enter the Phone Number: ");
    scanf("%s",addressBook->contacts[addressBook->contactCount].phone);
    result=validatephone(addressBook);
    }while(result!=1);
    do{
    printf("Enter the Email ID: ");
    scanf("%s",addressBook->contacts[addressBook->contactCount].email);
    result=validateemail(addressBook);
    }while(result!=1);
    addressBook->contactCount++;
    
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
   
}
int validatename(AddressBook *addressBook)
{
    int length=strlen(addressBook->contacts[addressBook->contactCount].name);
    if(length<2)
    {
        printf("Entered name is Invalid.\n");
        printf("Please Enter a name with minimum 2 characters.\n");
        return 0;
    }
    for(int i=0;i<length;i++)
    {
    if((!isalnum(addressBook->contacts[addressBook->contactCount].name[i])) &&
                 addressBook->contacts[addressBook->contactCount].name[i]!=' ')
    {
        printf("Entered name is Invalid.\n");
        printf("Name should only contain Alphabets or numbers!!.\n");
        return 0;
    }
    }
    return 1;
    
}
int validatephone(AddressBook *addressBook)
{
  int length=strlen(addressBook->contacts[addressBook->contactCount].phone);
  if(!(length==10))
  {
    printf("\nThe phone number should contain 10 Digits!!\n");
    return 0;
  }
  else if (!(addressBook->contacts[addressBook->contactCount].phone[0]>='6' && 
           addressBook->contacts[addressBook->contactCount].phone[0]<='9'))
  {
     printf("\nThe phone number should start with number greater than 6!!\n");
     return 0;
  }
  for(int i=0;i<length;i++)
  {
    if(!(addressBook->contacts[addressBook->contactCount].phone[i]>='0' &&
       addressBook->contacts[addressBook->contactCount].phone[i]<='9'))
       {
        printf("\nThe phone number should contain only digits!!\n");
        return 0;
       }
  }
 
    return 1;
  
  
}
int validateemail(AddressBook *addressBook)
{
    
}