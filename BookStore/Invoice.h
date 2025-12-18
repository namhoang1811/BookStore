#pragma once
#include "Base.h"
#include "Book.h"
#include "Customer.h"

struct InvoiceDetail {
    string bookId;
    int quantity = 0;
    double price = 0;

    InvoiceDetail() {}
    InvoiceDetail(string bookId, int quantity, double price) {
        this->bookId = bookId;
        this->quantity = quantity;
        this->price = price;
    }
};

// Dạy cho File cách GHI InvoiceDetail
template <>
inline void File::writeOne<InvoiceDetail>(ofstream& out, const InvoiceDetail& item) {
    File::writeOne(out, item.bookId);
    File::writeOne(out, item.quantity);
    File::writeOne(out, item.price);
}

// Dạy cho File cách ĐỌC InvoiceDetail
template <>
inline void File::readOne<InvoiceDetail>(ifstream& in, InvoiceDetail& item) {
    File::readOne(in, item.bookId);
    File::readOne(in, item.quantity);
    File::readOne(in, item.price);
}

struct Invoice : Base {
    string customerId;
    string dateTime;
    double total;
    vector<InvoiceDetail> details;

    Invoice() {
		total = 0;
    }
    Invoice(string id, string name, string customerId, string dateTime, double total, vector<InvoiceDetail> details) {
        this->id = id;
        this->name = name;
        this->customerId = customerId;
        this->dateTime = dateTime;
        this->total = total;
        this->details = details;
    }

    static void create(List<Invoice>& sources, List<Book>& books, List<Customer>& customers);
    static void edit(Invoice& invoice, List<Invoice>& sources, List<Book>& books, List<Customer>& customers);
    static void remove(Invoice& invoice, List<Invoice>& sources, List<Book>& books);

    void printHeader() override {
        cout << left << setw(10) << "MA" << setw(30) << "TEN HOA DON" << setw(20) << "MA KHACH HANG" << setw(20) << "NGAY TAO" << setw(15) << "TONG TIEN" << endl;
    }
    void printData(bool isHeader = true) override {
        if (isHeader)
            printHeader();
        cout << left << setw(10) << id << setw(30) << name << setw(20) << customerId << setw(20) << dateTime << setw(15) << total << endl;
    }

    void serialize(ofstream& out) override {
        File::save(out, id, name, customerId, dateTime, total, details);
    }

    void deserialize(ifstream& in) override {
        File::load(in, id, name, customerId, dateTime, total, details);
    }
};