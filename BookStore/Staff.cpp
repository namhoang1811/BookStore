#include "Staff.h"

namespace {
    // Hàm dùng chung cho tạo và chỉnh sửa
    Staff createEdit(Staff& staff, List<Staff>& sources, bool isCreate) {
        while (isCreate) {
            try {
                Input::in(staff.id, "Nhap Ma NV: ", true);
                if (!sources.any([staff](Staff d) {
                    return d.id == staff.id;
                    })) {
                    break;
                }
            } catch (...) {}
            Print::invalid();
        }
        Input::in(staff.name, "Nhap Ten NV: ", true);
        Input::in(staff.phone, "Nhap So dien thoai: ");
        Input::in(staff.position, "Nhap Chuc vu: ");
        Input::in(staff.salary, "Nhap Luong: ");
        return staff;
    }
}

void Staff::create(List<Staff>& sources) {
    Staff model;
    createEdit(model, sources, true);
    sources.add(model);
    sources.saveFile();
}

void Staff::edit(Staff& staff, List<Staff>& sources) {
    createEdit(staff, sources, false);
}

void Staff::remove(Staff& staff, List<Staff>& sources) {
    bool isDelete = sources.remove([&](Staff d) { return d.id == staff.id; });
    if (isDelete) {
        sources.saveFile();
        Print::success(DELETE_SUCCESS);
    }
}

// Sắp xếp theo lương tăng dần
bool Staff::sortBySalaryAsc(Staff a, Staff b) {
    return a.salary > b.salary;
}

// Sắp xếp theo lương giảm dần
bool Staff::sortBySalaryDesc(Staff a, Staff b) {
    return a.salary < b.salary;
}
