#include "Book.h"
#include "DateTime.h"

namespace {
    Book createEdit(Book source, bool isCreate) {
        if (isCreate) {
            cout << "Nhap Ma sach: ";
            getline(cin, source.id);
        }
        cout << "Nhap Ten sach: ";
        getline(cin, source.name);
        cout << "Nhap Tac gia: ";
        getline(cin, source.author);
        while (true) {
            cout << "Nhap Nam XB: ";
            cin >> source.year;
            if (source.year >= 0 && source.year <= DateTime::getCurrentYear())
                break;
            Print::invalid();
        }
        while (true) {
            cout << "Nhap Gia ban: ";
            cin >> source.price;
            if (source.price >= 0)
                break;
            Print::invalid();
        }
        while (true) {
            cout << "Nhap So luong ton: ";
            cin >> source.count;
            if (source.count >= 0)
                break;
            Print::invalid();
        }
        return source;
    }
}

void Book::printData() {
    cout << left << setw(10) << id << setw(30) << name << setw(15) << price << endl;
}

Book Book::create() {    
    Book model;
    return createEdit(model, true);
}

void Book::edit(Book source) {
    createEdit(source, false);
}
