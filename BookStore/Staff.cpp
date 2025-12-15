#include "Staff.h"

Staff Staff::create() {
    Staff model;
    Input::in(model.id, "Nhap Ma NV: ", true);
    Input::in(model.name, "Nhap Ten NV: ", true);
    Input::in(model.phone, "Nhap So dien thoai: ");
    Input::in(model.position, "Nhap Chuc vu: ");
    Input::in(model.salary, "Nhap Luong: ");
    return model;
}

void Staff::edit(Staff& source) {
    Input::in(source.name, "Nhap Ten NV: ", true);
    Input::in(source.phone, "Nhap So dien thoai: ");
    Input::in(source.position, "Nhap Chuc vu: ");
    Input::in(source.salary, "Nhap Luong: ");
}

// Sắp xếp theo lương tăng dần
bool Staff::sortBySalaryAsc(Staff a, Staff b) {
    return a.salary > b.salary;
}

// Sắp xếp theo lương giảm dần
bool Staff::sortBySalaryDesc(Staff a, Staff b) {
    return a.salary < b.salary;
}
