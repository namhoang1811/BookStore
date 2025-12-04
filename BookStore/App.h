#pragma once
#include "BookMenu.h"

struct App {
    List<Book> books;
    // List<Staff> listStaff;

    void menu();
    void run();  // Hàm chạy chính
};