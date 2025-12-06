#include "Book.h"
#include "DateTime.h"

namespace {
    Book createEdit(Book& source, bool isCreate) {        
        if (isCreate) {
            cout << "Nhap Ma sach: ";
            getline(cin, source.id);        
        }
        cout << "Nhap Ten sach: ";
		Input::autoType(source.name);
        getline(cin, source.name);
        cout << "Nhap Tac gia: ";
        Input::autoType(source.author);
        getline(cin, source.author);
        while (true) {
            cout << "Nhap Nam XB: ";
            try {
                if(!isCreate)
                    Input::autoType(to_string(source.year));
                source.year = stoi(Input::read());
                if (source.year >= 0 && source.year <= DateTime::nowYear())
                    break;
            } catch(...){}
            Notify::invalid();
        }
        while (true) {
            cout << "Nhap Gia ban: ";
            try {
                if (!isCreate)
                    Input::autoType(to_string(source.price));
                source.price = stod(Input::read());
                if (source.price >= 0)
                    break;
            } catch (...) {}
            Notify::invalid();
        }
        while (true) {
            cout << "Nhap So luong ton: ";
            try {
                if (!isCreate)
                    Input::autoType(to_string(source.count));
                source.count = stoi(Input::read());
                if (source.count >= 0)
                    break;
            } catch (...) {}
            Notify::invalid();
        }
        return source;
    }
}

Book Book::create() {    
    Book model;
    return createEdit(model, true);
}

void Book::edit(Book& source) {
    createEdit(source, false);
}