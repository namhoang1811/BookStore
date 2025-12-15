#include "StaffMenu.h"
#include "Input.h"
#include "Print.h"
#include <limits>

namespace {
    Staff* findAt(List<Staff>& staffs) {
        while (true) {
            try {
                int position = stoi(Input::read("Nhap thu tu Nhan Vien: ", true));
                Staff* result = staffs.findAt(position);
                if (!result)
                    Print::warning(NOT_FOUND);
                return result;
            }
            catch (...) {
                Print::removeLine(2);
            }
        }
    }

    Staff* findById(List<Staff>& staffs) {
        string id = Input::read("Nhap ma Nhan Vien: ", true);
        Staff* result = staffs.find([id](Staff d) {
            return d.id == id;
            });
        if (!result)
            Print::warning(NOT_FOUND);
        return result;
    }
}

void StaffMenu::show(List<Staff>& staffs) {
    while (true) {
        Print::title("QUAN LY NHAN VIEN");
        cout << "1. Xem danh sach" << endl;
        cout << "2. Them Nhan Vien moi" << endl;
        cout << "3. Tim Nhan Vien theo thu tu" << endl;
        cout << "4. Tim kiem Nhan Vien theo Ten" << endl;
        cout << "5. Chinh sua Nhan Vien theo thu tu" << endl;
        cout << "6. Chinh sua Nhan Vien theo Ma" << endl;
        cout << "7. Xoa Nhan Vien theo thu tu" << endl;
        cout << "8. Xoa Nhan Vien theo Ma" << endl;
        cout << "9. Sap xep theo Luong tang dan" << endl;
        cout << "0. Tro ve" << endl;
        cout << endl << PRESS_OPTION;
        char k = Input::getch();
        switch ((int)k - 48) {
        case 1:
            Print::title("DANH SACH NHAN VIEN");
            staffs.display();
            break;
        case 2: {
            Print::title("TAO NHAN VIEN MOI");
            auto model = Staff::create();
            bool isAny = staffs.any([model](Staff d) {
                return d.id == model.id;
                });
            if (!isAny) {
                staffs.add(model);
                staffs.saveFile();
                Print::success(ACTIVE_SUCCESS);
            } else {
                Print::danger("Them Nhan Vien moi that bai do trung Ma");
            }
            break;
        }
        case 3: {
            Print::title("TIM NHAN VIEN THEO THU TU");
            Staff* data = findAt(staffs);
            if (data) {
                data->printData();
                Print::pressAnyKey();
            }
            break;
        }
        case 4: {
            Print::title("TIM KIEM NHAN VIEN THEO TEN");
            string keyword;
            keyword = Input::read("Nhap ten nhan vien can tim: ", true);
            staffs.display([keyword](Staff d) {
                return d.name.find(keyword) != string::npos;
                });
            break;
        }
        case 5: {
            Print::title("CHINH SUA NHAN VIEN THEO THU TU");
            Staff* data = findAt(staffs);
            if (data) {
                Staff::edit(*data);
                staffs.saveFile();
                Print::success(EDIT_SUCCESS);
            }
            break;
        }
        case 6: {
            Print::title("CHINH SUA NHAN VIEN THEO MA");
            Staff* data = findById(staffs);
            if (data) {
                Staff::edit(*data);
                staffs.saveFile();
                Print::success(EDIT_SUCCESS);
            }
            break;
        }
        case 7: {
            Print::title("XOA NHAN VIEN THEO THU TU");
            Staff* data = findAt(staffs);
            if (data) {
                staffs.remove([&](Staff d) { return d.id == data->id; });
                staffs.saveFile();
                Print::success(DELETE_SUCCESS);
            }
            break;
        }
        case 8: {
            Print::title("XOA NHAN VIEN THEO MA");
            Staff* data = findById(staffs);
            if (data) {
                string deleteId = data->id;
                staffs.remove([&](Staff d) { return d.id == deleteId; });
                staffs.saveFile();
                Print::success(DELETE_SUCCESS);
            }
            break;
        }
        case 9: {
            Print::title("SAP XEP THEO LUONG TANG DAN");
            staffs.sort(Staff::sortBySalaryAsc);
            staffs.display();
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
