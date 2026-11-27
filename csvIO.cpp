#include "csvIO.h"
#include <cstdlib>

inline FILE* filePtr = NULL;

bool openFile()
{
    char line[MAX_LINE];
    int status;
    errno_t err = fopen_s(&filePtr, "data.csv", "a+");

    if (err != 0 && filePtr == NULL)
    {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }


    if (fgets(line, sizeof(line), filePtr) == NULL) {
        fclose(filePtr);
        status = false; // Empty file or read error
        return EXIT_FAILURE;
    }

    line[strcspn(line, "\r\n")] = '\0';

    if (strcmp(line, "ZipCode,Age,Items") != 0) {
        printf("Invalid CSV header: `%s`\n", line);
        fclose(filePtr);
        status = false;
        return EXIT_FAILURE;
    }

    return true;
}
void closeFile() { 
    fclose(filePtr);
    filePtr = NULL;
}

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
      fscanf_s(filePtr, "%d,%d,%d\n", &dum, &dum, &dum);// Suppressed unsed return value warning
       num++;
    }
    return num;
}

Customer readData(int index)
{
    int ch, n = 0;
    int zipcode, age, items;

    // get to te start of the file and ignore the first line
    rewind(filePtr);
    while ((ch = fgetc(filePtr)) != '\n');

    while (!feof(filePtr))
    {
        fscanf_s(filePtr, "%d,%d,%d\n", &zipcode, &age, &items);// Suppressed unsed return value warning
        if (index == n)
        {
            return {zipcode, age, items};
        }
        n++;
    }
    printf("List index out of range.");
    return {0, 0, 0};
}

void writeData(Customer customer)
{
    fseek(filePtr, 0, SEEK_END); // go to the end of file
    fprintf_s(filePtr, "\n%d, %d, %d", customer.zipCode, customer.age, customer.items);
}

// =========================
// Debugging
// =========================

//int main()
//{
//    if (openFile())
//    {
//        writeData((customerData) { 25783, 29, 18 });
//        int n = getNumOfCustomer();
//        printf("The number of customers are %d.\n", n);
//        for (int i = 0; i < n; i++)
//        {
//            customerData customer;
//            customer = readData(i);
//            printf("Customer zip code: %d.\n", customer.zipcode);
//            printf("Customer age: %d.\n", customer.age);
//            printf("Customer items: %d.\n\n", customer.item);
//        }
//        closeFile();
//    }
//    return 0;
//}