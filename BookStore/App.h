#pragma once
#include "BookMenu.h"

struct App {
    List<Book> books;
    // List<Staff> listStaff;

    void init();
    void run();  // Hàm chạy chính
};