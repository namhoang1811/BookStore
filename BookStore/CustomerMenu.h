#pragma once
#include "Customer.h"
#include "BaseMenu.h"

struct CustomerMenu : BaseMenu {
    static void show(List<Customer>& sources);
};
