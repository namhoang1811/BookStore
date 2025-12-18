#include "Customer.h"
#include <random>

namespace {
	int randomInt(int from, int to) {
        random_device rd;  // Nguồn số ngẫu nhiên
        mt19937 gen(rd()); // Máy phát số ngẫu nhiên
        uniform_int_distribution<> distr(from, to); // Phân phối đều
        return distr(gen);
    }

    // Hàm dùng chung cho tạo và chỉnh sửa
    Customer createEdit(Customer& customer, List<Customer>& sources, bool isCreate) {
        while (isCreate) {
            try {
                Input::in(customer.id, "Nhap Ma Khach hang: ", true);
                if (!sources.any([customer](Customer d) {
                    return d.id == customer.id;
                    })) {
                    break;
                }
            } catch (...) {}
            Print::invalid();
        }
        if (isCreate) {
			// Ngẫu nhiên điểm tích lũy khi tạo mới
			customer.points = randomInt(0, 1000);
        }
        Input::in(customer.name, "Nhap Ten KH: ", true);
        Input::in(customer.phone, "Nhap So dien thoai: ");
        Input::in(customer.address, "Nhap Dia chi: ");
        return customer;
    }
}

void Customer::create(List<Customer>& sources) {
    Customer model;
    createEdit(model, sources, true);
    sources.add(model);
    sources.saveFile();
    Print::success(ACTIVE_SUCCESS);
}

void Customer::edit(Customer& customer, List<Customer>& sources) {
    createEdit(customer, sources, false);
    sources.saveFile();
    Print::success(EDIT_SUCCESS);
}

void Customer::remove(Customer& customer, List<Customer>& sources) {
    bool isDelete = sources.remove([&](Customer d) { return d.id == customer.id; });
    if (isDelete) {
        sources.saveFile();
        Print::success(DELETE_SUCCESS);
    }
}