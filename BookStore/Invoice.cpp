#include "Invoice.h"
#include "DateTime.h"

namespace {
    // Hàm dùng chung cho tạo và chỉnh sửa
    Invoice createEdit(Invoice& invoice, List<Invoice>& sources, List<Book>& books, List<Customer>& customers, bool isCreate) {
        while (isCreate) {
            try {
                Input::in(invoice.id, "Nhap Ma hoa don: ", true);
                if (!sources.any([invoice](Invoice d) {
                    return d.id == invoice.id;
                    })) {
                    break;
                }
            } catch (...) {}
            Print::invalid();
        }
        Input::in(invoice.name, "Nhap Ten hoa don: ", true);
        while (isCreate) {
            try {
                Input::in(invoice.customerId, "Nhap Ma khach hang: ", true);
                if (!customers.any([invoice](Customer d) {
                    return d.id == invoice.customerId;
                    })) {
                    break;
                }
            } catch (...) {}
            Print::invalid();
        }
		// Trường hợp chỉnh sửa không cho phép thay đổi Chi tiết
        if(!isCreate)
			return invoice;

        invoice.dateTime = DateTime::nowString();
		int length = 0;
        while (isCreate) {
            try {
                length = stoi(Input::read("Nhap So luong Chi tiet: ", true));
                if (length >= 0)
                    break;
            } catch (...) {}
            Print::invalid();
        }
        for (int i = 0; i < length; i++) {
            cout << "Chi tiet hoa don - Mat hang " + to_string(i + 1);
            if (isCreate) {
                InvoiceDetail detail;
                invoice.details.push_back(detail);
            }
            InvoiceDetail& detail = invoice.details[i];
            while (true) {
                try {
                    Input::in(detail.bookId, "Nhap Ma sach: ", true);
                    if (!books.any([detail](Book d) {
                        return d.id == detail.bookId;
                        })) {
                        break;
                    }
                } catch (...) {}
                Print::invalid();
            }
            while (true) {
                try {
                    string val = !isCreate ? to_string(detail.quantity) : "";
                    detail.quantity = stoi(Input::read("Nhap So luong: ", val, true));
                    if (detail.quantity > 0) {
                        Book* book = books.find([detail](Book d) {
                            return d.id == detail.bookId;
                            });
                        if (book && detail.quantity > book->quantity) {
                            Print::invalid("So luong ton khong du");
                            continue;
                        }
						break;
                    }
                } catch (...) {}
                Print::invalid();
            }
            while (true) {
                try {
                    Book* book = books.find([detail](Book d) {
                        return d.id == detail.bookId;
						});
                    string val = !isCreate ? to_string(detail.price) : book ? to_string(book->price) : "";
                    detail.price = stod(Input::read("Nhap Don gia: ", val, true));
                    if (detail.price >= 0)
                        break;
                } catch (...) {}
                Print::invalid();
            }
			invoice.total += detail.quantity * detail.price;
        }
        return invoice;
    }

    void resetBooksQuantity(const Invoice& invoice, List<Book>& books) {
        for (const InvoiceDetail& detail : invoice.details) {
            Book* book = books.find([detail](Book b) {
                return b.id == detail.bookId;
                });
            if (book) {
                book->quantity += detail.quantity;
            }
        }
    }
}

void Invoice::create(List<Invoice>& sources, List<Book>& books, List<Customer>& customers) {
    Invoice model;
    createEdit(model, sources, books, customers, true);
    sources.add(model);
    for (const auto& item : model.details) {
        Book* book = books.find([item](Book d) {
            return d.id == item.bookId;
			});
		book->quantity -= item.quantity;
    }
    sources.saveFile();
	books.saveFile();
}

void Invoice::edit(Invoice& invoice, List<Invoice>& sources, List<Book>& books, List<Customer>& customers) {
    createEdit(invoice, sources, books, customers, false);
}
void Invoice::remove(Invoice& invoice, List<Invoice>& sources, List<Book>& books) {
    bool isDelete = sources.remove([&](Invoice d) { return d.id == invoice.id; });
    if (isDelete) {
        resetBooksQuantity(invoice, books);
        sources.saveFile();
        books.saveFile();
        Print::success(DELETE_SUCCESS);
    }
}
