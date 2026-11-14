#include "InputBackend.h"

bool AddCustomer(
    Customer customers[],
    int& customerCount,
    int zipCode,
    int age,
    int items,
    std::string& message
)
{
    // Check maximum capacity
    if (customerCount >= MAX_CUSTOMERS)
    {
        message = "Customer storage is full!";
        return false;
    }

    // Validate ZIP Code
    if (zipCode < 10000 || zipCode > 99999)
    {
        message = "ZIP Code must be exactly FIVE digits.";
        return false;
    }
   
    // Validate Age
    if (age < 10 || age > 110)
    {
        message = "Age must be between 10 and 110.";
        return false;
    }

    // Validate Items
    if (items < 1 || items > 12)
    {
        message = "Items must be between 1 and 12.";
        return false;
    }

    // Store Customer Data
    customers[customerCount].zipCode = zipCode;
    customers[customerCount].age = age;
    customers[customerCount].items = items;

    customerCount++;

    message = "Customer added successfully!";

    return true;
}