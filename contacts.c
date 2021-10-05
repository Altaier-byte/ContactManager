#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "contactHelpers.h"

void getName(struct Name* name) {

    char yesNo;

    printf("Please enter the contact's first name: ");
    scanf("%30[^\n]%*c", name->firstName);

    printf("Do you want to enter a middle initial(s)? (y or n): ");
    yesNo = yes();

    int a = 0;
    if (yesNo == 1)
    {
        printf("Please enter the contact's middle initial(s): ");
        char temp[100] = { '\0' };
        scanf("%100[^\n]%*c", temp);

        for (; a < 6; a++)
        {
            name->middleInitial[a] = temp[a];
        }

        name->middleInitial[6] = '\0';
    }

    printf("Please enter the contact's last name: ");
    scanf("%35[^\n]%*c", name->lastName);
}

void getAddress(struct Address* address)
{
    char yesNo;
    int show = 1;

    do {

        if (show == 1)
        {
            printf("Please enter the contact's street number: ");
            show = 0;
        }
        address->streetNumber = getInt();

        if (address->streetNumber < 1) {
            printf("*** INVALID STREET NUMBER *** <must be a positive number>:");
        }

    } while (address->streetNumber < 1);

    printf("Please enter the contact's street name: ");
    scanf("%40[^\n]%*c", address->street);

    printf("Do you want to enter an apartment number? (y or n): ");
    yesNo = yes();

    int show1 = 1;
    if (yesNo == 1)
    {
        do {

            if (show1 == 1)
            {
                printf("Please enter the contact's apartment number: ");
                show1 = 0;
            }
            address->apartmentNumber = getInt();

            if (address->apartmentNumber < 1) {
                printf("*** INVALID APARTMENT NUMBER *** <must be a positive number>:");
            }
        } while (address->apartmentNumber < 1);
    }

    printf("Please enter the contact's postal code: ");
    char temp[100] = { '\0' };
    scanf("%100[^\n]%*c", temp);

    int a = 0;
    for (; a < 7; a++)
    {
        address->postalCode[a] = temp[a];
    }

    address->postalCode[7] = '\0';

    printf("Please enter the contact's city: ");
    scanf("%40[^\n]%*c", address->city);
}

void getNumbers(struct Numbers* numbers)
{
    char yesNo;


    printf("Please enter the contact's cell phone number: ");
    getTenDigitPhone(numbers->cell);


    printf("Do you want to enter a home phone number? (y or n): ");
    yesNo = yes();

    if (yesNo == 1)
    {
        printf("Please enter the contact's home phone number: ");
        getTenDigitPhone(numbers->home);
    }

    printf("Do you want to enter a business phone number? (y or n): ");
    yesNo = yes();

    if (yesNo == 1)
    {
        printf("Please enter the contact's business phone number: ");
        getTenDigitPhone(numbers->business);
    }
}

void getContact(struct Contact* contact)
{
    getName(&contact->name);
    getAddress(&contact->address);
    getNumbers(&contact->numbers);
}