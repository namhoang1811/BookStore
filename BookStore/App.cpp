#include "App.h"

void App::menu() {
    while (true) {
        Print::title("MENU CHUONG TRINH CHINH");
        cout << "1. Quan ly Sach" << endl;
        cout << "2. Quan ly Khach Hang" << endl;
        cout << "0. Thoat" << endl;
        cout << endl << "Ban vua bam phim: ";
        char k = _getch();
        switch ((int)k - 48) {
        case 1: BookMenu::show(books); break;
        case 0:
            Print::clearScreen();
            cout << "Cam on da su dung chuong trinh. Tam biet!";
            return;
        }
    }
}

void App::load() {
	for (int i = 0; i < 5; i++) {
        Book book;
        book.id = "B00" + to_string(i + 1);
        book.name = "Sach " + to_string(i + 1);
        book.author = "Tac gia " + to_string(i + 1);
        book.year = 2000 + i;
        book.price = 10000 + i * 5000;
        book.count = 10 + i * 2;
        books.addLast(book);
    }
}

void App::run() {
    load();
    menu();
}

