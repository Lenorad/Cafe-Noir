#pragma once

struct customerData
{
    int zipcode, age, item;
};

bool openFile();

int getNumOfCustomer();

customerData readData(int index);

void writeData(customerData customer);

void closeFile();