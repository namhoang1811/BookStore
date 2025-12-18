#pragma once
#include "Invoice.h"
#include "BaseMenu.h"

struct InvoiceMenu : BaseMenu {
    static void show(List<Invoice>& sources, List<Book>& books, List<Customer>& customers);
};

