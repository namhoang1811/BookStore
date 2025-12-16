#include "Staff.h"

namespace {
    // Hàm dùng chung cho tạo và chỉnh sửa
    Staff createEdit(Staff& source, bool isCreate) {        
        if (isCreate) {
            Input::in(source.id, "Nhap Ma NV: ", true);
        }
        Input::in(source.name, "Nhap Ten NV: ", true);
        Input::in(source.phone, "Nhap So dien thoai: ");
        Input::in(source.position, "Nhap Chuc vu: ");
        Input::in(source.salary, "Nhap Luong: ");
        return source;
    }
}

Staff Staff::create() {
    Staff model;
    return createEdit(model, true);
}

void Staff::edit(Staff& source) {
    createEdit(source, false);
}

// Sắp xếp theo lương tăng dần
bool Staff::sortBySalaryAsc(Staff a, Staff b) {
    return a.salary > b.salary;
}

// Sắp xếp theo lương giảm dần
bool Staff::sortBySalaryDesc(Staff a, Staff b) {
    return a.salary < b.salary;
}
