#include "StaffMenu.h"

namespace {
    Staff* findAt(List<Staff>& staffs) {
        while (true) {
            try {
                int position = stoi(Input::read("Nhap thu tu Nhan Vien: ", true));
                Staff* result = staffs.findAt(position);
                if (!result)
                    Print::warning(NOT_FOUND);
                return result;
            } catch (...) {
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

void StaffMenu::show(List<Staff>& sources) {
    while (true) {
        Print::title("QUAN LY NHAN VIEN");
        cout << "1. Xem danh sach" << endl;
        cout << "2. Them Nhan Vien moi" << endl;
        cout << "3. Tim Nhan Vien theo thu tu" << endl;
        cout << "4. Tim kiem Nhan Vien theo Ten" << endl;
        cout << "5. Tim Nhan Vien co luong cao nhat" << endl;
        cout << "6. Tim Nhan Vien co luong thap nhat" << endl;
        cout << "7. Sap xep Nhan Vien theo luong tang dan" << endl;
        cout << "8. Sap xep Nhan Vien theo luong giam dan" << endl;
        cout << "9. Thong ke Nhan Vien co luong > 10000000" << endl;
        cout << "A. Thong ke Nhan Vien chua co luong" << endl;
        cout << "B. Tinh tong luong cua tat ca nhan vien" << endl;
        cout << "C. Tinh TB luong cua tat ca nhan vien" << endl;
        cout << "D. Chinh sua Nhan Vien theo thu tu" << endl;
        cout << "E. Chinh sua Nhan Vien theo Ma" << endl;
        cout << "F. Xoa Nhan Vien theo thu tu" << endl;
        cout << "G. Xoa Nhan Vien theo Ma" << endl;
        cout << "0. Tro ve" << endl;
        cout << endl << PRESS_OPTION;
        char k = Input::getch();
        switch ((int)k - 48) {
        case 1:
            Print::title("DANH SACH NHAN VIEN");
            sources.display();
            break;
        case 2: {
            Print::title("TAO NHAN VIEN MOI");
            Staff::create(sources);
            Print::success(ACTIVE_SUCCESS);
            break;
        }
        case 3: {
            Print::title("TIM NHAN VIEN THEO THU TU");
            Staff* data = findAt(sources);
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
            sources.display([keyword](Staff d) {
                return d.name.find(keyword) != string::npos;
                });
            break;
        }
        case 5: {
            Print::title("TIM NHAN VIEN CO LUONG CAO NHAT");
            Staff* data = sources.find([](Staff a, Staff b) {
                return a.salary > b.salary;
                });
            if (data) {
                sources.display([data](Staff d) {
                    return d.salary == data->salary;
                    });
            } else {
                Print::warning(NOT_FOUND);
			}
            break;
        }
        case 6: {
            Print::title("TIM NHAN VIEN CO LUONG THAP NHAT");
            Staff* data = sources.find([](Staff a, Staff b) {
                return a.salary < b.salary;
                });
            if (data) {
                sources.display([data](Staff d) {
                    return d.salary == data->salary;
                    });
            } else {
				Print::warning(NOT_FOUND);
			}
            break;
        }
        case 7: {
            Print::title("SAP XEP NHAN VIEN THEO LUONG TANG DAN");
            sources.sort([](Staff a, Staff b) {
                return a.salary > b.salary;
                });
            Print::success(ACTIVE_SUCCESS, 1000);
            Print::removeLine(2);
            sources.display();
            break;
        }
        case 8: {
            Print::title("SAP XEP NHAN VIEN THEO LUONG GIAM DAN");
            sources.sort([](Staff a, Staff b) {
                return a.salary < b.salary;
                });
            Print::success(ACTIVE_SUCCESS, 1000);
            Print::removeLine(2);
            sources.display();
            break;
        }
        case 9: {
            Print::title("THONG KE NHAN VIEN CO LUONG > 10000000");
            sources.display([](Staff d) {
                return d.salary > 10000000;
                });
            break;
        }
        case 17: case 49: { // A
            Print::title("THONG KE NHAN VIEN CHUA CO LUONG");
            sources.display([](Staff d) {
                return d.salary == 0;
                });
            break;
        }
        case 18: case 50: { // B
            Print::title("TINH TONG LUONG CUA TAT CA NHAN VIEN");
            int total = sources.sum<int>([](Staff d) {
                return d.salary;
                });
            cout << "Tong luong: " << total << endl;
            Print::pressAnyKey();
            break;
        }
        case 19: case 51: { // C
            Print::title("TINH TB LUONG CUA TAT CA NHAN VIEN");
            int average = sources.sum<int>([](Staff d) {
                return d.salary;
                }) / sources.size;
            cout << "Trung binh luong: " << average << endl;
            Print::pressAnyKey();
            break;
        }
        case 20: case 52: {  // D
            Print::title("CHINH SUA NHAN VIEN THEO THU TU");
            Staff* data = findAt(sources);
            if (data) {
                Staff::edit(*data, sources);
            }
            break;
        }
        case 21: case 53: {  // E
            Print::title("CHINH SUA NHAN VIEN THEO MA");
            Staff* data = findById(sources);
            if (data) {
                Staff::edit(*data, sources);
            }
            break;
        }
        case 22: case 54: {  // F
            Print::title("XOA NHAN VIEN THEO THU TU");
            Staff* data = findAt(sources);
            if (data) {
                Staff::remove(*data, sources);
            }
            break;
        }
        case 23: case 55: {  // G
            Print::title("XOA NHAN VIEN THEO MA");
            Staff* data = findById(sources);
            if (data) {
                Staff::remove(*data, sources);
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
