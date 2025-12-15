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
    Customer createEdit(Customer& source, bool isCreate) {        
        if (isCreate) {
            Input::in(source.id, "Nhap Ma KH: ", true);
			// Ngẫu nhiên điểm tích lũy khi tạo mới
			source.points = randomInt(0, 1000);
        }
        Input::in(source.name, "Nhap Ten KH: ", true);
        Input::in(source.phone, "Nhap So dien thoai: ");
        Input::in(source.address, "Nhap Dia chi: ");
        return source;
    }
}

Customer Customer::create() {
    Customer model;
    return createEdit(model, true);
}

void Customer::edit(Customer& source) {
    createEdit(source, false);
}
