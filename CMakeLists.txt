cmake_minimum_required(VERSION 3.14)
project(Client_Database)

set(CMAKE_CXX_STANDARD 14)

AUX_SOURCE_DIRECTORY(src DIR_SRC)
LINK_DIRECTORIES(lib)

add_executable(Client_Database ${DIR_SRC} main.cpp)
TARGET_LINK_LIBRARIES(Client_Database sqlite3)
#add_executable(Test main.cpp ${DIR_CLS})