#include "CustomerMenu.h"
#include "Input.h"
#include "Print.h"
#include <limits>

namespace {
    Customer* findAt(List<Customer>& customers) {
        while (true) {
            try {
                int position = stoi(Input::read("Nhap thu tu Khach Hang: ", true));
                Customer* result = customers.findAt(position);
                if (!result)
                    Print::warning(NOT_FOUND);
                return result;
            }
            catch (...) {
                Print::removeLine(2);
            }
        }
    }

    Customer* findById(List<Customer>& customers) {
        string id = Input::read("Nhap ma Khach Hang: ", true);
        Customer* result = customers.find([id](Customer d) {
            return d.id == id;
            });
        if (!result)
            Print::warning(NOT_FOUND);
        return result;
    }
}

void CustomerMenu::show(List<Customer>& customers) {
    while (true) {
        Print::title("QUAN LY KHACH HANG");
        cout << "1. Xem danh sach" << endl;
        cout << "2. Them Khach Hang moi" << endl;
        cout << "3. Tim Khach Hang theo thu tu" << endl;
        cout << "4. Tim kiem Khach Hang theo Ten" << endl;
        cout << "5. Chinh sua Khach Hang theo thu tu" << endl;
        cout << "6. Chinh sua Khach Hang theo Ma" << endl;
        cout << "7. Xoa Khach Hang theo thu tu" << endl;
        cout << "8. Xoa Khach Hang theo Ma" << endl;
        cout << "0. Tro ve" << endl;
        cout << endl << PRESS_OPTION;
        char k;
        cin >> k;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch ((int)k - 48) {
        case 1:
            Print::title("DANH SACH KHACH HANG");
            customers.display();
            break;
        case 2: {
            Print::title("TAO KHACH HANG MOI");
            auto model = Customer::create();
            bool isAny = customers.any([model](Customer d) {
                return d.id == model.id;
                });
            if (!isAny) {
                customers.add(model);
                customers.saveFile();
                Print::success(ACTIVE_SUCCESS);
            }
            else {
                Print::danger("Them Khach Hang moi that bai do trung Ma");
            }
            break;
        }
        case 3: {
            Print::title("TIM KHACH HANG THEO THU TU");
            Customer* data = findAt(customers);
            if (data) {
                data->printData();
                Print::pressAnyKey();
            }
            break;
        }
        case 4: {
            Print::title("TIM KIEM KHACH HANG THEO TEN");
            string keyword;
            keyword = Input::read("Nhap ten khach hang can tim: ", true);
            customers.display([keyword](Customer d) {
                return d.name.find(keyword) != string::npos;
                });
            break;
        }
        case 5: {
            Print::title("CHINH SUA KHACH HANG THEO THU TU");
            Customer* data = findAt(customers);
            if (data) {
                Customer::edit(*data);
                customers.saveFile();
                Print::success(EDIT_SUCCESS);
            }
            break;
        }
        case 6: {
            Print::title("CHINH SUA KHACH HANG THEO MA");
            Customer* data = findById(customers);
            if (data) {
                Customer::edit(*data);
                customers.saveFile();
                Print::success(EDIT_SUCCESS);
            }
            break;
        }
        case 7: {
            Print::title("XOA KHACH HANG THEO THU TU");
            Customer* data = findAt(customers);
            if (data) {
                customers.remove([&](Customer d) { return d.id == data->id; });
                customers.saveFile();
                Print::success(DELETE_SUCCESS);
            }
            break;
        }
        case 8: {
            Print::title("XOA KHACH HANG THEO MA");
            Customer* data = findById(customers);
            if (data) {
                string deleteId = data->id;
                customers.remove([&](Customer d) { return d.id == deleteId; });
                customers.saveFile();
                Print::success(DELETE_SUCCESS);
            }
            break;
        }
        case 0: case -21: // 0 or ESC
            return;
        default:
            Print::invalid();
            break;
        }
    }
}
