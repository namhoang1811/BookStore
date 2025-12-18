#include "Book.h"
#include "DateTime.h"

namespace {
	// Hàm dùng chung cho tạo và chỉnh sửa
    Book createEdit(Book& book, List<Book>& sources, bool isCreate) {
        while (isCreate) {
            try {
                Input::in(book.id, "Nhap Ma sach: ", true);
                if (!sources.any([book](Book d) {
                    return d.id == book.id;
                    })) {
                    break;
                }
            } catch (...) {}
            Print::invalid();
        }
        Input::in(book.name, "Nhap Ten sach: ", true);
        Input::in(book.author, "Nhap Tac gia: ");
        while (true) {
            if (!isCreate)
                Input::autoTyping(to_string(book.year));
            try {     
                string val = !isCreate ? to_string(book.year) : "";
                book.year = stoi(Input::read("Nhap Nam XB: ", val, true));
                if (book.year >= 0 && book.year <= DateTime::nowYear())
                    break;
            } catch(...){}
            Print::invalid();
        }
        while (true) {
            try {  
                string val = !isCreate ? to_string(book.price) : "";
                book.price = stod(Input::read("Nhap Gia ban: ", val, true));
                if (book.price >= 0)
                    break;
            } catch (...) {}
            Print::invalid();
        }
        while (true) {
            try {
                string val = !isCreate ? to_string(book.quantity) : "";
                book.quantity = stoi(Input::read("Nhap So luong ton: ", val, true));
                if (book.quantity >= 0)
                    break;
            } catch (...) {}
            Print::invalid();
        }
        return book;
    }
}

void Book::create(List<Book>& sources) {
    Book model;
    createEdit(model, sources, true);
    sources.add(model);
    sources.saveFile();
    Print::success(ACTIVE_SUCCESS);
}

void Book::edit(Book& book, List<Book>& sources) {
    createEdit(book, sources, false);
    sources.saveFile();
    Print::success(EDIT_SUCCESS);
}

void Book::remove(Book& book, List<Book>& sources) {
    bool isDeleted = sources.remove([&book](Book d) {
        return d.id == book.id;
        });
    if (isDeleted) {
        sources.saveFile();
        Print::success(DELETE_SUCCESS);
    }
}