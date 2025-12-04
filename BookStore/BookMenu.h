#pragma once // Chỉ thị tiền xử lý để tránh include nhiều lần
#include "Book.h"
#include "BaseMenu.h"

struct BookMenu : BaseMenu {
    static void show(List<Book> sources);
};
