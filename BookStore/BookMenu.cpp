#include "BookMenu.h"

void BookMenu::show(List<Book> books) {
    while (true) {
        Print::title("QUAN LY SACH");
        cout << "1. Xem danh sach" << endl;
        cout << "2. Them Sach moi" << endl;
        cout << "2. Quan ly Khach Hang" << endl;
        cout << "0. Tro ve" << endl;
        cout << endl << "Ban vua bam phim: ";
        char k = _getch();
        switch ((int)k - 48) {
        case 1:
            Print::title("DANH SACH SACH");
            books.display(2);
            break;
        case 2:
            Print::title("TAO MOT SACH MOI");
            books.addLast(Book::create());
            break;
        case 3:
            Print::title("CHINH SUA SACH");
            books.addLast(Book::create());
            break;
        case 0:
            return;
        }
    }
}