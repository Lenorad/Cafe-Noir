#pragma once

#include "CustomerInput.h"
#include <string>

bool AddCustomer(
    Customer customers[],
    int& customerCount,
    int zipCode,
    int age,
    int items,
    std::string& message
);