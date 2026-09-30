#include <stdio.h>
#include "contact.h"

int main() {
    int choice,criteria;
    int index[100]={0};
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook,index);
                break;
            case 3:
                editContact(&addressBook,index);
                break;
            case 4:
                deleteContact(&addressBook,index);
                break;
            case 5:
               printf("\n========== LIST CONTACTS ==========\n");
                do{
                printf("Enter the criteria to sort the contacts: \n");
                printf("1. Sort by Name\n");
                printf("2. Sort by Phone Number\n");
                printf("3. Sort by Email\n");
                printf("Enter your choice: ");
                scanf("%d",&criteria);
                if(criteria<1 || criteria>3)
                {
                    printf("\nINVALID INPUT!! PLEASE ENTER AGAIN.\n\n");
                }
                }while(criteria<1 || criteria>3);
                listContacts(&addressBook,criteria);
                break;
            case 6:
                printf("Saving...\n");
                saveContactsToFile(&addressBook);
                break;   
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
    
       return 0;
}
