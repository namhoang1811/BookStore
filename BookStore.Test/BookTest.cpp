#include "pch.h"
#include "CppUnitTest.h"
#include "../BookStore/Book.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BookStoreTest {
	TEST_CLASS(BookTest) {
	public:		
        // Test 1: Kiểm tra thêm sách và kích thước danh sách
        TEST_METHOD(TestAddBookIncreasesSize) {
            List<Book> list;
            Book b1("B01", "Test Book 1", "Author A", 2020, 100, 50000);
            list.add(b1);
            // Size phải bằng 1
            Assert::AreEqual(1, list.size);
            Book b2("B02", "Test Book 2", "Author B", 2021, 200, 20000);
            list.add(b2);
            // Size phải bằng 2
            Assert::AreEqual(2, list.size);
        }

        // Test 2: Kiểm tra tìm giá lớn nhất
        TEST_METHOD(TestFindMaxPrice) {
            List<Book> list;
            list.add(Book("1", "A", "", 2000, 50, 10000));
            list.add(Book("2", "B", "", 2000, 20, 200000)); // Max
            list.add(Book("3", "C", "", 2000, 100, 50000));
            Book* maxBook = list.find([](Book a, Book b) {
                return a.price > b.price;
                });
            // Giá tìm được phải là 2000000.0
            Assert::AreEqual(200000.0, maxBook->price);
        }

        // Test 3: Kiểm tra Xóa
        TEST_METHOD(TestDeleteHead) {
            List<Book> list;
            list.add(Book("B01", "", "", 2012, 1, 20000));
            list.add(Book("B02", "", "", 2010, 2, 40000));
            list.add(Book("B03", "", "", 2014, 2, 25000));
            bool result = list.remove([](Book d) {
				return d.id == "B01";
                });
            Assert::IsTrue(result);
            Assert::AreEqual(2, list.size);
            Assert::AreEqual(std::string("B02"), list.head->data.id);
        }
	};
}
