cmake_minimum_required(VERSION 4.1)
project(BookStore)

set(CMAKE_CXX_STANDARD 14)

include_directories(BookStore)

add_executable(BookStore
        BookStore/App.h
        BookStore/Base.cpp
        BookStore/Base.h
        BookStore/BaseMenu.h
        BookStore/Book.cpp
        BookStore/Book.h
        BookStore/BookMenu.cpp
        BookStore/BookMenu.h
        BookStore/Customer.cpp
        BookStore/Customer.h
        BookStore/CustomerMenu.cpp
        BookStore/CustomerMenu.h
        BookStore/Staff.cpp
        BookStore/Staff.h
        BookStore/StaffMenu.cpp
        BookStore/StaffMenu.h
        BookStore/Const.h
        BookStore/DateTime.cpp
        BookStore/DateTime.h
        BookStore/File.h
        BookStore/Input.h
        BookStore/List.h
        BookStore/main.cpp
        BookStore/Print.cpp
        BookStore/Print.h)

# Test executable for Customer struct
add_executable(CustomerTest
        BookStore/CustomerTest.cpp
        BookStore/Customer.cpp
        BookStore/Customer.h
        BookStore/Base.cpp
        BookStore/Base.h
        BookStore/DateTime.cpp
        BookStore/DateTime.h
        BookStore/Print.cpp
        BookStore/Print.h
        BookStore/File.h
        BookStore/Input.h
        BookStore/Const.h)

enable_testing()
add_test(NAME CustomerTest COMMAND CustomerTest)
