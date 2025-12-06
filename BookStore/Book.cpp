#include "Book.h"
#include "DateTime.h"

namespace {
    Book createEdit(Book& source, bool isCreate) {        
        if (isCreate) {
            cout << "Nhap Ma sach: ";
            getline(cin, source.id);        
        }
        cout << "Nhap Ten sach: ";
		Input::autoTyping(source.name);
        getline(cin, source.name);
        cout << "Nhap Tac gia: ";
        Input::autoTyping(source.author);
        getline(cin, source.author);
        while (true) {
            cout << "Nhap Nam XB: ";
            if (!isCreate)
                Input::autoTyping(to_string(source.year));
            try {                
                source.year = stoi(Input::read());
                if (source.year >= 0 && source.year <= DateTime::nowYear())
                    break;
            } catch(...){}
            Print::invalid();
        }
        while (true) {
            cout << "Nhap Gia ban: ";
            if (!isCreate)
                Input::autoTyping(to_string(source.price));
            try {                
                source.price = stod(Input::read());
                if (source.price >= 0)
                    break;
            } catch (...) {}
            Print::invalid();
        }
        while (true) {
            cout << "Nhap So luong ton: ";
            if (!isCreate)
                Input::autoTyping(to_string(source.count));
            try {                
                source.count = stoi(Input::read());
                if (source.count >= 0)
                    break;
            } catch (...) {}
            Print::invalid();
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