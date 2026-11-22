#pragma once
#include "inputPanelUI.h" // struct Customer
#include <cstdio> // FILE
#include <cstring> // strcmp

#define MAX_LINE 100

struct Customer;

bool openFile();

int getNumOfCustomer();

Customer readData(int index);

void writeData(Customer customer);

void closeFile();