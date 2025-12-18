#include "Book.h"
#include "Customer.h"
#include "Staff.h"
#include "Invoice.h"
#include "List.h"

using namespace std;

struct Init {
	static void run(List<Invoice>& invoices, List<Book>& books, List<Customer>& customers, List<Staff>& staffs) {
		Print::title("KHOI TAO DU LIEU");
		// Xóa dữ liệu hiện tại
		invoices.clear();
		books.clear();
		customers.clear();
		staffs.clear();
		// Thêm dữ liệu mẫu cho Nhân viên
		staffs.add(Staff("NV01", "Nguyen Van An", "0901234567", "Cua hang truong", 25000000));
		staffs.add(Staff("NV02", "Tran Thi Bich", "0912345678", "Ke toan truong", 18000000));
		staffs.add(Staff("NV03", "Le Van Cuong", "0923456789", "Thu ngan", 8500000));
		staffs.add(Staff("NV05", "Hoang Van Em", "0945678901", "Nhan vien kho", 9000000));
		staffs.add(Staff("NV06", "Vu Thi Hoa", "0956789012", "Tu van ban hang", 7500000));
		staffs.add(Staff("NV07", "Do Van Hung", "0967890123", "Bao ve", 6500000));
		staffs.saveFile();
		// Thêm dữ liệu mẫu cho Khách hàng
		customers.add(Customer("KH01", "Tran Van Thanh", 150, "0911223344", "Cau Giay, Ha Noi"));
		customers.add(Customer("KH02", "Le Thi Mai", 300, "0922334455", "Quan 1, TP.HCM"));
		customers.add(Customer("KH03", "Nguyen Van Hung", 50, "0933445566", "Hai Chau, Da Nang"));
		customers.add(Customer("KH04", "Pham Thu Huong", 0, "0944556677", "Ngo Quyen, Hai Phong"));
		customers.add(Customer("KH05", "Vo Van Nam", 1200, "0955667788", "Ninh Kieu, Can Tho"));
		customers.add(Customer("KH06", "Dang Thi Lan", 80, "0966778899", "Thu Dau Mot, Binh Duong"));
		customers.add(Customer("KH07", "Bui Van Tuan", 450, "0977889900", "Bien Hoa, Dong Nai"));
		customers.add(Customer("KH08", "Hoang Thi Yen", 210, "0988990011", "Dong Xoai, Binh Phuoc"));
		customers.saveFile();
		// Thêm dữ liệu mẫu cho Sách
		books.add(Book("B01", "Dac Nhan Tam", "Dale Carnegie", 2024, 100, 75000));
		books.add(Book("B02", "Nha Gia Kim", "Paulo Coelho", 2023, 50, 68000));
		books.add(Book("B03", "Tuoi Tre Dang Gia", "Rosie Nguyen", 2022, 200, 80000));
		books.add(Book("B04", "Ca Phe Cung Tony", "Tony Buoi Sang", 2021, 120, 90000));
		books.add(Book("B05", "Toi Thay Hoa Vang", "Nguyen Nhat Anh", 2020, 80, 110000));
		books.add(Book("B06", "Mat Biec", "Nguyen Nhat Anh", 2019, 90, 105000));
		books.add(Book("B07", "Harry Potter 1", "J.K. Rowling", 2000, 150, 200000));
		books.add(Book("B08", "Sherlock Holmes", "Conan Doyle", 1998, 60, 120000));
		books.add(Book("B09", "Doraemon Tap 1", "Fujiko F. Fujio", 2024, 500, 25000));
		books.add(Book("B10", "Conan Tap 100", "Gosho Aoyama", 2024, 300, 25000));
		books.add(Book("B11", "One Piece 99", "Oda Eiichiro", 2023, 250, 25000));
		books.add(Book("B12", "Dragon Ball Z", "Toriyama Akira", 1995, 100, 30000));
		books.saveFile();
		// Thêm dữ liệu mẫu cho Hóa đơn
		invoices.add(Invoice("HD01", "Hoa don ban le 01", "KH01","18/12/2025 10:30", 218000, {                       // Danh sách chi tiết (vector<InvoiceDetail>)
				InvoiceDetail("B01", 2, 75000),
				InvoiceDetail("B02", 1, 68000)
			} ));
		invoices.add(Invoice("HD02", "Hoa don ban le 02", "KH03", "19/12/2025 14:15", 110000, {
				InvoiceDetail("B05", 1, 110000)
			} ));
		invoices.add(Invoice("HD03", "Hoa don mua le", "KH02", "20/12/2025 09:15", 580000, {
			InvoiceDetail("B03", 5, 80000), 
			InvoiceDetail("B04", 2, 90000) 
			}));
		invoices.add(Invoice("HD04", "Hoa don si truyen tranh", "KH05", "21/12/2025 14:30", 500000, { 
			InvoiceDetail("B09", 10, 25000), 
			InvoiceDetail("B10", 5, 25000), 
			InvoiceDetail("B11", 5, 25000) 
			}));
		invoices.add(Invoice("HD05", "Hoa don tieu thuyet", "KH04", "22/12/2025 10:00", 215000, { 
			InvoiceDetail("B05", 1, 110000), 
			InvoiceDetail("B06", 1, 105000) 
			}));
		invoices.add(Invoice("HD06", "Hoa don VIP", "KH02", "23/12/2025 16:45", 940000, { 
			InvoiceDetail("B07", 7, 100000), 
			InvoiceDetail("B08", 2, 120000) 
			}));
		invoices.add(Invoice("HD07", "Hoa don qua tang", "KH06", "24/12/2025 08:30", 429000, { 
			InvoiceDetail("B01", 3, 75000), 
			InvoiceDetail("B02", 3, 68000) 
			}));
		invoices.saveFile();		
		Print::success("Khoi tao du lieu mau thanh cong!", 1500);
	}
};
