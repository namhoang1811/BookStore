#include "Customer.h"

Customer Customer::create() {
    Customer model;
    Input::in(model.id, "Nhap Ma KH: ", true);
    Input::in(model.name, "Nhap Ten KH: ", true);
    Input::in(model.phone, "Nhap So dien thoai: ");
    Input::in(model.address, "Nhap Dia chi: ");
    return model;
}

void Customer::edit(Customer& source) {
    Input::in(source.name, "Nhap Ten KH: ", true);
    Input::in(source.phone, "Nhap So dien thoai: ");
    Input::in(source.address, "Nhap Dia chi: ");
}
