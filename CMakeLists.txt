cmake_minimum_required(VERSION 4.0)
project(projektinzynieriaoprogramowania)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

add_library(pliki_system
        System.cpp
        Uzytkownik.cpp
        Wykladowca.cpp
        Student.cpp
        Przedmiot.cpp
        Test.cpp
)

add_executable(projektinzynieriaoprogramowania
        main.cpp
)
target_link_libraries(projektinzynieriaoprogramowania pliki_system)

add_executable(TestyMain
        Testy/TestyMain.cpp
)
target_link_libraries(TestyMain pliki_system)

enable_testing()
add_test(NAME TestyMain COMMAND TestyMain)
