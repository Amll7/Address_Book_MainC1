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
    result=validatename(addressBook,addressBook->contactCount);
    }while(result!=1);

    //phone number 
    do{
    printf("Enter the Phone Number: ");
    scanf("%s",addressBook->contacts[addressBook->contactCount].phone);
    result=validatephone(addressBook,addressBook->contactCount);
    }while(result!=1);

    //email
    do{
    printf("Enter the Email ID: ");
    scanf("%s",addressBook->contacts[addressBook->contactCount].email);
    result=validateemail(addressBook,addressBook->contactCount);
    }while(result!=1);
    addressBook->contactCount++;
    
}



void display(AddressBook *addressBook,int index[],int i)
{
 for(int j=0;j<i;j++)
 {
    printf("\n\n%d.",j+1);
    printf("Name  : %s\n", addressBook->contacts[index[j]].name);
    printf("Phone : %s\n", addressBook->contacts[index[j]].phone);
    printf("Email : %s\n\n", addressBook->contacts[index[j]].email);
 }
}




int searchContact(AddressBook *addressBook,int index[]) 
{
   int choice;
   int result;
   printf("\nSearch Contact\n");
   printf("1. Search by Name\n");
   printf("2. Search by Phone Number\n");
   printf("3. Search by Email\n");
   printf("Enter your choice: ");
   scanf("%d",&choice);
   switch(choice)
   {
    case 1:
           result=searchbyname(addressBook,index);
           display(addressBook,index,result);
           break;
    case 2:
           result=searchbyphone(addressBook,index);
           display(addressBook,index,result);
           break;
    case 3:
           result=searchbyemail(addressBook,index);
           display(addressBook,index,result);
           break;
    default:
            printf("Invalid Input.");
            result=-1;
   }
   return result;
}

int editContact(AddressBook *addressBook,int index[])
{
    int count,result;
    int choice,option;
	printf("\n=========== EDIT CONTACT ===========\n");
    printf("Search for the contact you want to delete.\n\n");
    count=searchContact(addressBook,index);
    if(count==-1)
    {
        return 0;
    }
    printf("Select the contact you want to edit : ");
    scanf("%d",&choice);
    printf("\n\nEnter the edit field.\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d",&option);
    switch(option)
    {
      case 1:
           do
           {
           printf("Enter the name of the contact: ");
           scanf(" %[^\n]",addressBook->contacts[index[choice-1]].name);
           result=validatename(addressBook,index[choice-1]);
           }while(result!=1);
           break;
    case 2:
            do{
            printf("Enter the Phone Number: ");
            scanf("%s",addressBook->contacts[index[choice-1]].phone);
            result=validatephone(addressBook,index[choice-1]);
    }while(result!=1);
           break;
    case 3:
            do
            {
            printf("Enter the Email ID: ");
            scanf("%s",addressBook->contacts[index[choice-1]].email);
            result=validateemail(addressBook,index[choice-1]);
            }while(result!=1);
           break;
    default:
            printf("Invalid Input.");  
    }

    
    
}

int deleteContact(AddressBook *addressBook,int index[])
{
    int count;
    int choice,i;
	printf("\n========== DELETE CONTACT ==========\n");
    printf("Search for the contact you want to delete.\n\n");
    count=searchContact(addressBook,index);
    printf("Select the contact you want to delete : ");
    scanf("%d",&choice);
    for(i=index[choice-1];i<addressBook->contactCount-1;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
    printf("Contact Deleted succesfully...\n\n");

   
}

int validatename(AddressBook *addressBook,int count)
{
    int length=strlen(addressBook->contacts[count].name);


    if(length<2)
    {
        printf("Invalid name: The name must contain at least 2 characters.\n");
        return 0;
    }



    for(int i=0;i<length;i++)
    {
    if((!isalnum(addressBook->contacts[count].name[i])) &&
                 addressBook->contacts[count].name[i]!=' ')
    {
        printf("Invalid name: The name must contain only alphabets, numbers and spaces.\n");
        return 0;
    }
    }


    return 1;
    
}
int validatephone(AddressBook *addressBook,int count)
{
  int length=strlen(addressBook->contacts[count].phone);
  for(int i=0;i<length;i++)
  {
    if(!(addressBook->contacts[count].phone[i]>='0' &&
       addressBook->contacts[count].phone[i]<='9'))
       {
        printf("Invalid phone number: The phone number must contain only digits.\n");
        return 0;
       }
  }




  if (!(addressBook->contacts[count].phone[0]>='6' && 
           addressBook->contacts[count].phone[0]<='9'))
  {
     printf("Invalid phone number: The phone number must start with a digit from 6 to 9.\n");
     return 0;
  }
  else if(!(length==10))
  {
    printf("Invalid phone number: The phone number must contain exactly 10 digits.\n");
    return 0;
  }
 
 return 1;
  
  
}
int validateemail(AddressBook *addressBook,int count)
{

 char *com=strstr(addressBook->contacts[count].email,".com");
 char *at=strchr(addressBook->contacts[count].email,'@');
 char *dot=strchr(addressBook->contacts[count].email,'.');
 int length=strlen(addressBook->contacts[count].email);
 int atcount=0;
 
 if(addressBook->contacts[count].email[0]=='@')
 {
   printf("Invalid email: The email address cannot start with '@'.\n");
   return 0;
 }
 if(addressBook->contacts[count].email[0]=='.')
 {
   printf("Invalid email: The email address cannot start with '.'.\n");
   return 0;
 }




 for(int i=0;i<length;i++)
 {
 if(addressBook->contacts[count].email[i]>='A' && 
    addressBook->contacts[count].email[i]<='Z' )
 {
   printf("Invalid email: Uppercase letters are not allowed.\n");
   return 0;
 }
}




 for(int i=0;i<length;i++)
 {
   if(addressBook->contacts[count].email[i]=='@')
   {
    atcount++;
   }
   if(atcount==2)
   {
    printf("Invalid email: The email address must contain only one '@'.\n");
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
    printf("Invalid email: The domain name must contain a letter.\n");
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
     return 0;
    }
 }

 return 1;
}


int searchbyname(AddressBook *addressBook,int index[])
{
    char check[20];
    int j=0,flag=0,i;
    printf("Enter the name: ");
    scanf(" %[^\n]",check);
    for(i=0;i<addressBook->contactCount;i++)
    {
    
        if(strstr(addressBook->contacts[i].name,check)!=NULL)
        {
            flag=1;
            index[j]=i;
            j++;
        }
    }
     
    if(flag==0)
    {
    printf("Contact Not found!!");
    }
    return j;
    
    
}
int searchbyphone(AddressBook *addressBook,int index[])
{
    char check[50];
    int j=0,i;
    printf("Enter the phone number: ");
    scanf(" %s",check);
    int flag=0;
    for(i=0;i<addressBook->contactCount;i++)
    {
        if(strstr(addressBook->contacts[i].phone, check)!=NULL)
        {
            flag=1;
            index[j]=i;
            j++;
            
        }
    }
   if(flag==0)
    {
    printf("Contact Not found!!");
    }
    return j;
    
}


int searchbyemail(AddressBook *addressBook,int index[])
{
    char check[20];
    int j=0,i;
    printf("Enter the email: ");
    scanf(" %s",check);
    int flag=0;
    for(i=0;i<addressBook->contactCount;i++)
    {
        if(strstr(addressBook->contacts[i].email, check)!=NULL)
        {
            flag=1;
            index[j]=i;
            j++;
           
        }
    }
    if(flag==0)
    {
    printf("Contact Not found!!");
    }
    return j;
    
}