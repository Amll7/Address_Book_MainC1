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
        printf("Invalid name: The name must contain at least 2 characters.\n");
        return 0;
    }
    for(int i=0;i<length;i++)
    {
    if((!isalnum(addressBook->contacts[addressBook->contactCount].name[i])) &&
                 addressBook->contacts[addressBook->contactCount].name[i]!=' ')
    {
        printf("Invalid name: The name must contain only alphabets, numbers and spaces.\n");
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
    printf("Invalid phone number: The phone number must contain exactly 10 digits.\n");
    return 0;
  }
  else if (!(addressBook->contacts[addressBook->contactCount].phone[0]>='6' && 
           addressBook->contacts[addressBook->contactCount].phone[0]<='9'))
  {
     printf("Invalid phone number: The phone number must start with a digit from 6 to 9.\n");
     return 0;
  }
  for(int i=0;i<length;i++)
  {
    if(!(addressBook->contacts[addressBook->contactCount].phone[i]>='0' &&
       addressBook->contacts[addressBook->contactCount].phone[i]<='9'))
       {
        printf("Invalid phone number: The phone number must contain only digits.\n");
        return 0;
       }
  }
 
    return 1;
  
  
}
int validateemail(AddressBook *addressBook)
{

 char *com=strstr(addressBook->contacts[addressBook->contactCount].email,".com");
 char *at=strchr(addressBook->contacts[addressBook->contactCount].email,'@');
 char *dot=strchr(addressBook->contacts[addressBook->contactCount].email,'.');
 int length=strlen(addressBook->contacts[addressBook->contactCount].email);
 int atcount=0;
 
 if(addressBook->contacts[addressBook->contactCount].email[0]=='@')
 {
   printf("Invalid email: The email address cannot start with '@'.\n");
   return 0;
 }
 if(addressBook->contacts[addressBook->contactCount].email[0]=='.')
 {
   printf("Invalid email: The email address cannot start with '.'.\n");
   return 0;
 }


 for(int i=0;i<length;i++)
 {
   if(addressBook->contacts[addressBook->contactCount].email[i]=='@')
   {
    atcount++;
   }
   if(atcount==2)
   {
    printf("Invalid email: The email address must contain only one '@'.\n");
    return 0;
   }
 }



 for(int i=0;i<length;i++)
 {
 if(addressBook->contacts[addressBook->contactCount].email[i]>='A' && 
    addressBook->contacts[addressBook->contactCount].email[i]<='Z' )
 {
   printf("Invalid email: Uppercase letters are not allowed.\n");
   return 0;
 }
}



 if(com != NULL)
 {
    if(*(com+4)!='\0')
    {
    printf("Invalid email: '.com' must appear at the end of the email address.\n");
    return 0;
    }
 }
 else
 {
    printf("Invalid email: The email address must contain '.com'.\n");
    return 0;
 }


 if(at!=NULL) 
 {
    if((!(*(at+1)>='a' && *(at+1)<='z')))
    {
    printf("Invalid email: The domain name must start with a lowercase letter.\n");
    return 0;
    }
 }
 else
 {
   printf("Invalid email: The email address must contain '@'.\n");
   return 0;
 }
 

 if(dot!=NULL)
 {
    if(*(dot+1)=='.'||*(dot+1)=='@')
    {
     printf("Invalid email: A dot cannot be immediately followed by another dot or '@'.\n");
    }
 }


 
 return 1;
}