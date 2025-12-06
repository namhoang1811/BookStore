#include "App.h"

void App::init() {
    while (true) {
        Print::title("MENU CHUONG TRINH CHINH");
        cout << "1. Quan ly Sach" << endl;
        cout << "2. Quan ly Nhan Vien" << endl;
        cout << "3. Quan ly Khach Hang" << endl;
        cout << "4. Quan ly Hoa don" << endl;
        cout << "5. Thong tin" << endl;
        cout << "0. Thoat" << endl;
        cout << endl << PRESS_OPTION;
        char k = _getch();
        switch ((int)k - 48) {
        case 1: BookMenu::show(books); break;
        case 0:
            Print::title("MENU CHUONG TRINH CHINH");
            cout << "Cam on da su dung chuong trinh!";
            return;
        }
    }
}

void App::run() {
	// Load dữ liệu từ file
    books.loadFile();

    init();
}

