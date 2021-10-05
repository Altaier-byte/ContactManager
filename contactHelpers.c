#include "contactHelpers.h"

#define _CRT_SECURE_NO_WARNINGS
#define MAXCONTACTS 5

#include <stdio.h>
#include <string.h>


void clearKeyboard(void)
{
    while (getchar() != '\n');
}


void pause(void)
{
    printf("(Press Enter to continue)");
    clearKeyboard();
}
int getInt(void)
{
    int integer = 0;
    char checker = '\0';
    while (1)
    {
        scanf("%d%c", &integer, &checker);

        if (checker != '\n')
        {
            clearKeyboard();
            printf("*** INVALID INTEGER *** <Please enter an integer>:  ");
        }
        else
        {
            break;
        }

    }

    return integer;
}
int getIntInRange(int min, int max)
{
    while (1)
    {
        int integer = getInt();

        if (integer >= min && integer <= max)
        {
            return integer;
        }
        else
        {
            printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", min, max);
        }

    }



}


int yes(void)
{
    char character = 0;
    char checker = '\0';
    while (1)
    {
        scanf("%c%c", &character, &checker);

        if (checker != '\n')
        {
            clearKeyboard();
            printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>:  ");
        }
        else
        {
            if (character == 'y' || character == 'Y')
            {
                return 1;
            }
            else if (character == 'n' || character == 'N')
            {
                return 0;
            }
            else {
                clearKeyboard();
                printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
            }
        }


    }

}
int menu(void)
{
    printf("\nContact Management System\n-------------------------\n1. Display contacts\n2. Add a contact\n3. Update a contact\n4. Delete a contact\n5. Search contacts by cell phone number\n6. Sort contacts by cell phone number\n0. Exit\n\nSelect an option:> ");

    int option = getIntInRange(0, 6);

    printf("\n");

    return option;

}
void contactManagerSystem(void)
{
    struct Contact contacts[MAXCONTACTS] = { { { "Rick", {'\0'}, "Grimes" },
             { 11, "Trailer Park", 0, "A7A 2J2", "King City" },
             { "4161112222", "4162223333", "4163334444" } },
           {
              { "Maggie", "R.", "Greene" },
              { 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
              { "9051112222", "9052223333", "9053334444" } },
           {
              { "Morgan", "A.", "Jones" },
              { 77, "Cottage Lane", 0, "C7C 9Q9", "Peterborough" },
              { "7051112222", "7052223333", "7053334444" } },
           {
              { "Sasha", {'\0'}, "Williams" },
              { 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
              { "9052223333", "9052223333", "9054445555" } },
    };

    while (1)
    {
        int option = menu();

        if (option == 1)
        {
            displayContacts(contacts, MAXCONTACTS);
        }
        else if (option == 2)
        {
            addContact(contacts, MAXCONTACTS);
        }
        else if (option == 3)
        {
            updateContact(contacts, MAXCONTACTS);
        }
        else if (option == 4)
        {
            deleteContact(contacts, MAXCONTACTS);
        }
        else if (option == 5)
        {
            searchContacts(contacts, MAXCONTACTS);
        }
        else if (option == 6)
        {
            sortContacts(contacts, MAXCONTACTS);
        }
        else if (option == 0) {
            printf("Exit the program? (Y)es/(N)o: ");
            int choice = yes();

            if (choice == 1) {
                break;
            }
        }

        pause();
    }

    printf("Contact Management System: terminated\n");
}

int isNumber(char* str)
{
    int a = 0;
    for (; a < strlen(str); a++)
    {
        if (str[a] < '0' || str[a]>'9')
            return 0;
    }

    return 1;
}
void getTenDigitPhone(char phoneNum[])
{
    int needInput = 1;

    while (needInput == 1)
    {
        scanf("%10s", phoneNum);
        clearKeyboard();

        // (String Length Function: validate entry of 10 characters)
        if (strlen(phoneNum) == 10 && isNumber(phoneNum))
        {
            needInput = 0;
        }
        else
        {
            printf("Enter a 10-digit phone number: ");
        }
    }

}


int findContactIndex(const struct Contact contacts[], int size, const char cellNum[])
{
    int a = 0;
    for (; a < size; a++)
    {
        if (strcmp(contacts[a].numbers.cell, cellNum) == 0)
        {
            return a;
        }
    }
    return -1;
}

void displayContactHeader(void)
{
    printf("+-----------------------------------------------------------------------------+\n|                              Contacts Listing                               |\n+-----------------------------------------------------------------------------+\n");
}
void displayContactFooter(int count)
{
    printf("+-----------------------------------------------------------------------------+\nTotal contacts: %d\n\n", count);
}
void displayContact(const struct Contact* contact)
{
    if (strlen(contact->name.middleInitial) != 0)
    {
        printf(" %s %s %s\n", contact->name.firstName, contact->name.middleInitial, contact->name.lastName);
    }
    else {
        printf(" %s %s\n", contact->name.firstName, contact->name.lastName);
    }


    printf("    C: %-10s   H: %-10s   B: %-10s\n", contact->numbers.cell, contact->numbers.home, contact->numbers.business);

    printf("       %d %s, ", contact->address.streetNumber, contact->address.street);

    if (contact->address.apartmentNumber > 0)
    {
        printf("Apt# %d, ", contact->address.apartmentNumber);
    }

    printf("%s, %s\n", contact->address.city, contact->address.postalCode);
}

void displayContacts(const struct Contact contacts[], int size)
{
    int validContacts = 0;
    displayContactHeader();
    int a = 0;
    for (; a < size; a++)
    {
        if (strlen(contacts[a].numbers.cell) > 0) {
            displayContact(&contacts[a]);
            validContacts++;
        }
    }
    displayContactFooter(validContacts);
}
void searchContacts(const struct Contact contacts[], int size)
{
    printf("Enter the cell number for the contact: ");
    char phoneNo[11] = { '\0' };
    getTenDigitPhone(phoneNo);

    int index = findContactIndex(contacts, size, phoneNo);
    if (index != -1)
    {
        displayContact(&contacts[index]);
        printf("\n");
    }
    else {
        printf("*** Contact NOT FOUND ***\n");
    }

}
void addContact(struct Contact contacts[], int size)
{
    char arr[11] = { '\0' };
    int index = findContactIndex(contacts, size, arr);
    if (index != -1)
    {
        getContact(&contacts[index]);
        printf("--- New contact added! ---\n");
    }
    else {
        printf("*** ERROR: The contact list is full! ***\n");
    }

}
void updateContact(struct Contact contacts[], int size)
{
    char phoneNo[11] = { '\0' };
    printf("Enter the cell number for the contact: ");
    getTenDigitPhone(phoneNo);

    int index = findContactIndex(contacts, size, phoneNo);
    if (index != -1)
    {
        printf("\nContact found:\n");
        displayContact(&contacts[index]);
        printf("\n");
        printf("Do you want to update the name? (y or n): ");
        int option = yes();

        if (option == 1)
        {
            getName(&contacts[index].name);
        }
        else {
            memset(contacts[index].name.middleInitial, 0, 7);
            memset(contacts[index].name.firstName, 0, 31);
            memset(contacts[index].name.lastName, 0, 36);
        }

        printf("Do you want to update the address? (y or n): ");
        option = yes();

        if (option == 1)
        {
            getAddress(&contacts[index].address);
        }
        else {
            memset(contacts[index].address.city, 0, 41);
            memset(contacts[index].address.postalCode, 0, 8);
            memset(contacts[index].address.street, 0, 41);
            contacts[index].address.streetNumber = 0;
            contacts[index].address.apartmentNumber = 0;
        }

        printf("Do you want to update the numbers? (y or n): ");

        option = yes();

        if (option == 1)
        {
            getNumbers(&contacts[index].numbers);
        }
        else
        {
            memset(contacts[index].numbers.cell, 0, 11);
            memset(contacts[index].numbers.home, 0, 11);
            memset(contacts[index].numbers.business, 0, 11);
        }

        printf("--- Contact Updated! ---\n");

    }
    else {
        printf("*** Contact NOT FOUND ***\n");
    }


}
void deleteContact(struct Contact contacts[], int size)
{
    char phoneNo[11] = { '\0' };
    printf("Enter the cell number for the contact: ");
    getTenDigitPhone(phoneNo);

    int index = findContactIndex(contacts, size, phoneNo);
    if (index != -1)
    {
        printf("\nContact found:\n");
        displayContact(&contacts[index]);
        printf("\n");
        printf("CONFIRM: Delete this contact? (y or n): ");
        int option = yes();

        if (option == 1)
        {
            contacts[index].numbers.cell[0] = '\0';
            printf("--- Contact deleted! ---\n");
        }

    }
    else {
        printf("*** Contact NOT FOUND ***\n");
    }

}
void sortContacts(struct Contact contacts[], int size)
{
    int b = 0;
    for (; b < size; b++)
    {
        int a = 0;
        for (; a < size - 1; a++)
        {

            if (strcmp(contacts[a].numbers.cell, contacts[a + 1].numbers.cell) >= 1)
            {

                struct Name tempName;
                struct Address tempAddress;
                struct Numbers tempNumber;

                memset(tempName.firstName, 0, 31);
                memset(tempName.middleInitial, 0, 7);
                memset(tempName.lastName, 0, 36);

                memset(tempAddress.street, 0, 41);
                memset(tempAddress.postalCode, 0, 8);
                memset(tempAddress.street, 0, 41);

                memset(tempNumber.cell, 0, 11);
                memset(tempNumber.home, 0, 11);
                memset(tempNumber.business, 0, 11);

                strcpy(tempName.firstName, contacts[a].name.firstName);
                strcpy(tempName.middleInitial, contacts[a].name.middleInitial);
                strcpy(tempName.lastName, contacts[a].name.lastName);

                strcpy(tempAddress.city, contacts[a].address.city);
                strcpy(tempAddress.street, contacts[a].address.street);
                strcpy(tempAddress.postalCode, contacts[a].address.postalCode);
                tempAddress.apartmentNumber = contacts[a].address.apartmentNumber;
                tempAddress.streetNumber = contacts[a].address.streetNumber;

                strcpy(tempNumber.cell, contacts[a].numbers.cell);
                strcpy(tempNumber.home, contacts[a].numbers.home);
                strcpy(tempNumber.business, contacts[a].numbers.business);


                memset(contacts[a].name.firstName, 0, 31);
                memset(contacts[a].name.middleInitial, 0, 7);
                memset(contacts[a].name.lastName, 0, 36);

                memset(contacts[a].address.street, 0, 41);
                memset(contacts[a].address.postalCode, 0, 8);
                memset(contacts[a].address.street, 0, 41);

                memset(contacts[a].numbers.cell, 0, 11);
                memset(contacts[a].numbers.home, 0, 11);
                memset(contacts[a].numbers.business, 0, 11);

                strcpy(contacts[a].name.firstName, contacts[a + 1].name.firstName);
                strcpy(contacts[a].name.middleInitial, contacts[a + 1].name.middleInitial);
                strcpy(contacts[a].name.lastName, contacts[a + 1].name.lastName);

                strcpy(contacts[a].address.city, contacts[a + 1].address.city);
                strcpy(contacts[a].address.street, contacts[a + 1].address.street);
                strcpy(contacts[a].address.postalCode, contacts[a + 1].address.postalCode);
                contacts[a].address.apartmentNumber = contacts[a + 1].address.apartmentNumber;
                contacts[a].address.streetNumber = contacts[a + 1].address.streetNumber;

                strcpy(contacts[a].numbers.cell, contacts[a + 1].numbers.cell);
                strcpy(contacts[a].numbers.home, contacts[a + 1].numbers.home);
                strcpy(contacts[a].numbers.business, contacts[a + 1].numbers.business);



                memset(contacts[a + 1].name.firstName, 0, 31);
                memset(contacts[a + 1].name.middleInitial, 0, 7);
                memset(contacts[a + 1].name.lastName, 0, 36);

                memset(contacts[a + 1].address.street, 0, 41);
                memset(contacts[a + 1].address.postalCode, 0, 8);
                memset(contacts[a + 1].address.street, 0, 41);

                memset(contacts[a + 1].numbers.cell, 0, 11);
                memset(contacts[a + 1].numbers.home, 0, 11);
                memset(contacts[a + 1].numbers.business, 0, 11);



                strcpy(contacts[a + 1].name.firstName, tempName.firstName);
                strcpy(contacts[a + 1].name.middleInitial, tempName.middleInitial);
                strcpy(contacts[a + 1].name.lastName, tempName.lastName);

                strcpy(contacts[a + 1].address.city, tempAddress.city);
                strcpy(contacts[a + 1].address.street, tempAddress.street);
                strcpy(contacts[a + 1].address.postalCode, tempAddress.postalCode);

                contacts[a + 1].address.apartmentNumber = tempAddress.apartmentNumber;
                contacts[a + 1].address.streetNumber = tempAddress.streetNumber;

                strcpy(contacts[a + 1].numbers.cell, tempNumber.cell);
                strcpy(contacts[a + 1].numbers.home, tempNumber.home);
                strcpy(contacts[a + 1].numbers.business, tempNumber.business);





            }
        }

    }

    printf("--- Contacts sorted! ---\n");

}



