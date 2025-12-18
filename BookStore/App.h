#pragma once
#include "BookMenu.h"
#include "CustomerMenu.h"
#include "StaffMenu.h"
#include "InvoiceMenu.h"
#include "Init.h"

struct App {
    List<Book> books;
    List<Customer> customers;
    List<Staff> staffs;
    List<Invoice> invoices;

    void menu() {
        while (true) {
            Print::title("MENU CHUONG TRINH CHINH");
            cout << "1. Quan ly Sach" << endl;
            cout << "2. Quan ly Nhan Vien" << endl;
            cout << "3. Quan ly Khach Hang" << endl;
            cout << "4. Quan ly Hoa don" << endl;
            cout << "5. Khoi tao du lieu mau" << endl;
            cout << "0. Thoat" << endl;
            cout << endl << PRESS_OPTION;
            char k = Input::getch();
            switch ((int)k - 48) {
            case 1: BookMenu::show(books); break;
            case 2: StaffMenu::show(staffs); break;
            case 3: CustomerMenu::show(customers); break;
            case 4: InvoiceMenu::show(invoices, books, customers); break;
            case 5: Init::run(invoices, books, customers, staffs); break;
            case 0: case -21: // 0 or ESC
                Print::removeLine(1);
                cout << "Cam on da su dung chuong trinh!" << endl;
                return;
            }
        }
    }
    void run() {  // Hàm chạy chính
        books.loadFile();
        customers.loadFile();
        staffs.loadFile();
        invoices.loadFile();
        menu();
    }
};