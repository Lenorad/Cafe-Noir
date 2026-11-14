#pragma once

const int MAX_CUSTOMERS = 100;

struct Customer
{
    int zipCode;
    int age;
    int items;
};

void RenderCustomerInput(
    Customer customers[],
    int& customerCount
);