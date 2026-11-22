#define _CRT_SECURE_NO_WARNINGS // Disables security warnings
#include <cstdio>
#include <cstring> // strcmp
#include "Data.h"
#define MAX 100

FILE *filePtr;

int getNumOfCustomer();

bool openFile();

customerData readData(int index);

void writeData(customerData);

void closeFile();

   bool openFile()
{
    char str[MAX];
    filePtr = fopen("data.csv", "a+");

    if (filePtr == NULL)
        return 0;
    (void)fscanf(filePtr, "%s\n", str); // Suppressed unsed return value warning

    return (strcmp(str, "ZipCode,Age,Items") == 0) ? true : false;
}

void closeFile() { fclose(filePtr); }

int getNumOfCustomer()
{
    int dum; // dummy value
    int ch;
    int num = 0;

    // get to the start of the file and ignore the first line
    rewind(filePtr);
    while ((ch = fgetc(filePtr)) != '\n' && ch != EOF); 

    while (!feof(filePtr))
    {
      (void)fscanf(filePtr, "%d,%d,%d\n", &dum, &dum, &dum);// Suppressed unsed return value warning
       num++;
    }
    return num;
}

customerData readData(int index)
{
    int ch, n = 0;
    int zipcode, age, items;

    // get to te start of the file and ignore the first line
    rewind(filePtr);
    while ((ch = fgetc(filePtr)) != '\n');

    while (!feof(filePtr))
    {
        (void)fscanf(filePtr, "%d,%d,%d\n", &zipcode, &age, &items);// Suppressed unsed return value warning
        if (index == n)
        {
            return {zipcode, age, items};
        }
        n++;
    }
    printf("List index out of range.");
    return {0, 0, 0};
}

void writeData(customerData customer)
{
    fseek(filePtr, 0, SEEK_END); // go to the end of file
    fprintf(filePtr, "\n%d, %d, %d", customer.zipcode, customer.age, customer.item);
}