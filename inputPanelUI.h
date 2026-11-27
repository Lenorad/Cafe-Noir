#pragma once
#include "csvIO.h"
#include "imgui.h"
#include <string>

struct Customer
{
    int zipCode, age, items;
};

void RenderCustomerInput(
    Customer customers[],
    int& customerCount
);