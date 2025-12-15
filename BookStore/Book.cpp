#include "Book.h"
#include "DateTime.h"

namespace {
	// Hàm dùng chung cho tạo và chỉnh sửa
    Book createEdit(Book& source, bool isCreate) {        
        if (isCreate)
            Input::in(source.id, "Nhap Ma sach: ", true);
        Input::in(source.name, "Nhap Ten sach: ");
        Input::in(source.author, "Nhap Tac gia: ");
        while (true) {
            if (!isCreate)
                Input::autoTyping(to_string(source.year));
            try {     
                string val = !isCreate ? to_string(source.year) : "";
                source.year = stoi(Input::read("Nhap Nam XB: ", val, true));
                if (source.year >= 0 && source.year <= DateTime::nowYear())
                    break;
            } catch(...){}
            Print::invalid();
        }
        while (true) {
            try {  
                string val = !isCreate ? to_string(source.price) : "";
                source.price = stod(Input::read("Nhap Gia ban: ", val, true));
                if (source.price >= 0)
                    break;
            } catch (...) {}
            Print::invalid();
        }
        while (true) {
            try {
                string val = !isCreate ? to_string(source.quantity) : "";
                source.quantity = stoi(Input::read("Nhap So luong ton: ", val, true));
                if (source.quantity >= 0)
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