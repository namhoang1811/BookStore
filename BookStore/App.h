#pragma once
#include "BookMenu.h"
#include <limits>

struct App {
    List<Book> books;
    // List<Staff> staffs;

    void menu() {
        while (true) {
            Print::title("MENU CHUONG TRINH CHINH");
            cout << "1. Quan ly Sach" << endl;
            cout << "2. Quan ly Nhan Vien" << endl;
            cout << "3. Quan ly Khach Hang" << endl;
            cout << "4. Quan ly Hoa don" << endl;
            cout << "5. Thong tin" << endl;
            cout << "0. Thoat" << endl;
            cout << endl << PRESS_OPTION;
            char k;
            cin >> k;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch ((int)k - 48) {
            case 1: BookMenu::show(books); break;
            case 0: case -21: // 0 or ESC
                Print::removeLine(1);
                cout << "Cam on da su dung chuong trinh!" << endl;
                return;
            }
        }
    }
    void run() {  // Hàm chạy chính
        books.loadFile();
        menu();
    }
};