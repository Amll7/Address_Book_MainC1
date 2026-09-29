#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include <ctype.h>
//#include "populate.h"


void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

//A function has been called for creating a new contact

void createContact(AddressBook *addressBook)
{
    
	printf("Creating a new contact...\n\n");
    int result;

    /*
     * asking the user to enter the name
     * scanning the entered name into the name string of the contact
     * passing the entered name to the name validation function
     * the validation function checks whether the name satisfies all the required conditions
     * if all conditions are satisfied, the function returns 1
     * otherwise, it will returns 0
     * a do-while loop repeatedly asks the user to enter the name until
       the entered name passes all validation checks*/


    do{
    printf("Enter the name of the contact: ");
    scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].name);
    result=validatename(addressBook->contacts[addressBook->contactCount].name);
    }while(result!=1);
    

    /*
     * asking the user to enter the phone number
     * scanning the entered phone number into the phone number string of the contact
     * passing the entered phone number to the phone number validation function
     * the validation function checks whether the phone number satisfies all the required conditions
     * if all conditions are satisfied, the function returns 1
     * otherwise, it will returns 0
     * a do-while loop repeatedly asks the user to enter the phone number until
       the entered phone number passes all validation checks*/ 


    do{
    printf("Enter the Phone Number: ");
    scanf("%s",addressBook->contacts[addressBook->contactCount].phone);
    result=validatephone(addressBook->contacts[addressBook->contactCount].phone);
    }while(result!=1);


    /*
     * asking the user to enter the Email
     * scanning the entered Email into the Email string of the contact
     * passing the entered Email to the Email validation function
     * the validation function checks whether the Email satisfies all the required conditions
     * if all conditions are satisfied, the function returns 1
     * otherwise, it will returns 0
     * a do-while loop repeatedly asks the user to enter the Email until
       the entered Email passes all validation checks*/


    do{
    printf("Enter the Email ID: ");
    scanf("%s",addressBook->contacts[addressBook->contactCount].email);
    result=validateemail(addressBook->contacts[addressBook->contactCount].email);
    }while(result!=1);
    addressBook->contactCount++;
    
}


//A fuction to display the name,phone number and email.

void display(AddressBook *addressBook,int index[],int i)
{
 for(int j=0;j<i;j++)
 {
    printf("\n\n%d.",j+1);
    printf("Name  : %s\n", addressBook->contacts[index[j]].name);
    printf("  Phone : %s\n", addressBook->contacts[index[j]].phone);
    printf("  Email : %s\n\n", addressBook->contacts[index[j]].email);
 }
}



/*
 * Displaying the search contact menu and asking the user to select the search criteria
 * the user can search  using the name, phone number,or email address.
 * based on the user choice the search function is called
 * the search function returns the index of the matching contact
 * the returned index is passed to the display function to display the contact details
 * if the user enters an invalid choice, an error message is displayed
   and the result is set to -1 
 * finally the function returns the search result because later the search is 
   used in delete and edit also it is basically useful in those functions */


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


/*
 * asking the user to search for the contact which they want to edit
 * the searchContact function is called and it returns the result
 * if no contact is found the count value is -1 so it  returns 0 and exits
 * asking the user to select the contact from the search results
 * then asking the user to select which field they want to edit
 * based on the choice the field is selected 
 * the new string(name,phone,email) is taken from the user and passed to validate function
 * the validate function checks whether the entered value satisfies all the conditions
 * the do-while loop continues until a valid value is entered
 * after successful validation the new value is copied into the selected contact 
 * if an invalid option is entered an error message is displayed 

   why index[choice-1]?
   because in display fn it displays from 1 but the actual index of array starts
   from 0 and also that array contains the matched contacts indexs
 */


int editContact(AddressBook *addressBook,int index[])
{
    int count,result;
    int choice,option;
    char edit[50];
	printf("\n=========== EDIT CONTACT ===========\n");
    printf("Search for the contact you want to edit.\n\n");
    count=searchContact(addressBook,index);
    if(count==-1)
    {
        return 0;
    }
    do{
    printf("Select the contact you want to edit : ");
    scanf("%d",&choice);

    if(choice < 1 || choice > count)
    {
        printf("Invalid choice. Please try again\n");
    }

    }while(choice < 1 || choice > count);
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
           scanf(" %[^\n]",edit);
           result=validatename(edit);
           }while(result!=1);
           strcpy(addressBook->contacts[index[choice-1]].name,edit);
           break;
    case 2:
            do{
            printf("Enter the Phone Number: ");
            scanf("%s",edit);
            result=validatephone(edit);
            }while(result!=1);
            strcpy(addressBook->contacts[index[choice-1]].phone,edit);
            break;
    case 3:
            do
            {
            printf("Enter the Email ID: ");
            scanf("%s",edit);
            result=validateemail(edit);
            }while(result!=1);
             strcpy(addressBook->contacts[index[choice-1]].email,edit);
           break;
    default:
            printf("Invalid Input.");  
    }

    
    return 0;
}


/*
 * asking the user to search for the contact which they want to delete
 * the searchContact function is called and it returns the search result
 * if no contact is found the function returns 0 and exits
 * asking the user to select the contact from the search results
 * getting the index of the selected contact
 * shifting all the contacts after the selected contact 
 * decreasing the contactCount by one after deleting the contact
 */

int deleteContact(AddressBook *addressBook,int index[])
{
    int count;
    int choice,i;
	printf("\n========== DELETE CONTACT ==========\n");
    printf("Search for the contact you want to delete.\n\n");
    count=searchContact(addressBook,index);
    if(count==-1)
    {
        return 0;
    }
    do{
    printf("Select the contact you want to Delete : ");
    scanf("%d",&choice);

    if(choice < 1 || choice > count)
    {
        printf("Invalid choice. Please try again\n");
    }

    }while(choice < 1 || choice > count);
    for(i=index[choice-1];i<addressBook->contactCount-1;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
    printf("Contact Deleted succesfully...\n\n");
    return 0;
   
}

int validatename(char name[])
{
    //finding the length of the name/string\
      using inbuilt function

    int length=strlen(name);



    //The letters should only be alphabets, numbers and spaces.\
      checking every index of name ie,every characher of the name is getting checked\
      using a for loop

    for(int i=0;i<length;i++)
    {
    if((!isalnum(name[i])) && (name[i]!=' '))
    {
        printf("Invalid name: The name must contain only alphabets, numbers and spaces.\n");
        return 0;
    }
    }




    //if length is less than 2 the name is invalid.\
      we are checking it using an if condition.

    if(length<2)
    {
        printf("Invalid phone number: The phone number must contain at least 2 characters.\n");
        return 0;
    }


    //Here we understood that the name satisfies every condition\
      so we are returning 1 if any of the condition is not satisfied it will return 0 \
      to the createcontact function 

      return 1;
    
}
int validatephone(char phone[])
{
  int length=strlen(phone);



  for(int i=0;i<length;i++)
  {
    if(!(phone[i]>='0' && phone[i]<='9'))
       {
        printf("Invalid phone number: The phone number must contain only digits.\n");
        return 0;
       }
  }




  if (!(phone[0]>='6' && phone[0]<='9'))
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
int validateemail(char email[])
{

 char *com=strstr(email,".com");
 char *at=strchr(email,'@');
 char *dot=strchr(email,'.');
 int length=strlen(email);
 int atcount=0;
 
 if(email[0]=='@')
 {
   printf("Invalid email: The email address cannot start with '@'.\n");
   return 0;
 }
 if(email[0]=='.')
 {
   printf("Invalid email: The email address cannot start with '.'.\n");
   return 0;
 }




 for(int i=0;i<length;i++)
 {
 if(email[i]>='A' && email[i]<='Z' )
 {
   printf("Invalid email: Uppercase letters are not allowed.\n");
   return 0;
 }
}

if(at!=NULL) 
 {
    if((!(*(at+1)>='a' && *(at+1)<='z')))
    {
    printf("Invalid email: The domain must contain a letter.\n");
    return 0;
    }
 }
 else
 {
   printf("Invalid email: The email address must contain '@'.\n");
   return 0;
 }






 for(int i=0;i<length;i++)
 {
   if(email[i]=='@')
   {
    atcount++;
   }
   if(atcount==2)
   {
    printf("Invalid email: The email address must contain only one '@'.\n");
    return 0;
   }
 }



if(dot!=NULL)
 {
    if(*(dot+1)=='.'||*(dot+1)=='@')
    {
     printf("Invalid email: A dot cannot be immediately followed by another dot or '@'.\n");
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


 

 return 1;
}


int searchbyname(AddressBook *addressBook,int index[])
{
    char check[20];
    int j=0,flag=0,i;
    printf("Enter the Name : ");
    scanf(" %[^\n]",check);
    for(i=0;i<addressBook->contactCount;i++)
    {
    
        if(strcasestr(addressBook->contacts[i].name,check)!=NULL)
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
        //if(strstr(addressBook->contacts[i].phone, check)!=NULL)
        if(strcmp(addressBook->contacts[i].phone,check)==0)
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
        //if(strstr(addressBook->contacts[i].email, check)!=NULL)
        if(strcmp(addressBook->contacts[i].email,check)==0)
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
void listContacts(AddressBook *addressBook, int sortCriteria)
{
    Contact temp;
    int i,j;
    if(sortCriteria==1)
    {
    
        
        for(i=0;i<addressBook->contactCount-1;i++)
        {
            for(j = 0; j < addressBook->contactCount - i - 1; j++)
            {
                if(strcasecmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
                {
                    temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
        printf("------------------------------------------------------------------------- \n");
        printf("| %-18s | %-20s | %-25s |\n","NAME","PHONE","EMAIL");
        for(i=0;i<addressBook->contactCount;i++)
        {
        printf("------------------------------------------------------------------------- \n");
         printf("| %-18s | %-20s | %-25s |\n",addressBook->contacts[i].name,
            addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        printf("------------------------------------------------------------------------- \n");
    }
    else if(sortCriteria==2)
    {
        
        for(i=0;i<addressBook->contactCount-1;i++)
        {
            for(j = 0; j < addressBook->contactCount - i - 1; j++)
            {
                if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0)
                {
                    temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
        printf("------------------------------------------------------------------------- \n");
        printf("| %-18s | %-20s | %-25s |\n","NAME","PHONE","EMAIL");
        for(i=0;i<addressBook->contactCount;i++)
        {
        printf("------------------------------------------------------------------------- \n");
         printf("| %-18s | %-20s | %-25s |\n",addressBook->contacts[i].name,
            addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        printf("------------------------------------------------------------------------- \n");

    }


     else if(sortCriteria==3)
    {

        
        
        for(i=0;i<addressBook->contactCount-1;i++)
        {
            for(j = 0; j < addressBook->contactCount - i - 1; j++)
            {
                if(strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0)
                {
                    temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                }
            }
        }
        printf("------------------------------------------------------------------------- \n");
        printf("| %-18s | %-20s | %-25s |\n","NAME","PHONE","EMAIL");
        for(i=0;i<addressBook->contactCount;i++)
        {
        printf("------------------------------------------------------------------------- \n");
         printf("| %-18s | %-20s | %-25s |\n",addressBook->contacts[i].name,
            addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        printf("------------------------------------------------------------------------- \n");

    }
    else
    {
        printf("Invalid input!!\n\n");
    }

}