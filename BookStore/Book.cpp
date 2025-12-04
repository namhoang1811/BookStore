#include "Book.h"
#include "DateTime.h"

void Book::printData() {
    cout << left << setw(10) << id << setw(30) << name << setw(15) << price << endl;
}

Book Book::create() {    
    Book book;
    cout << "Nhap Ma sach: ";
    getline(cin, book.id);
    cout << "Nhap Ten sach: ";
    getline(cin, book.name);
    cout << "Nhap Tac gia: ";
    getline(cin, book.author);
    while (true) {
        cout << "Nhap Nam XB: ";
		cin >> book.year;
        if(book.year >= 0 && book.year <= DateTime::getCurrentYear())
            break;
        Print::invalid();
    }
    while (true) {
        cout << "Nhap Gia ban: ";
        cin >> book.price;
        if (book.price >= 0)
            break;
        Print::invalid();
    }
    while (true) {
        cout << "Nhap So luong ton: ";
        cin >> book.count;
        if (book.count >= 0)
            break;
        Print::invalid();
    }
    return book;
}
