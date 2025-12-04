#include "App.h"

void App::menu() {
    while (true) {
        Print::title("MENU CHUONG TRINH CHINH");
        cout << "1. Quan ly Sach" << endl;
        cout << "2. Quan ly Khach Hang" << endl;
        cout << "0. Thoat" << endl;
        cout << endl << PRESS_OPTION;
        char k = _getch();
        switch ((int)k - 48) {
        case 1: BookMenu::show(books); break;
        case 0:
            Print::clearScreen();
            Notify::primary("Cam on da su dung chuong trinh!", 0);
            return;
        }
    }
}

void App::run() {
	// Load dữ liệu từ file
    books.loadFile();

    menu();
}

