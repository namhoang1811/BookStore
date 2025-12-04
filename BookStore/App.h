#pragma once
#include "BookMenu.h"

struct App {
    List<Book> books;
    // List<Staff> listStaff;
    void load(); // Giả lập dữ liệu
    void run();      // Hàm chạy chính

    void menu();
};