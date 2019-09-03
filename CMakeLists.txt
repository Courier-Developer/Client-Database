cmake_minimum_required(VERSION 3.14)
project(DB)

set(CMAKE_CXX_STANDARD 14)

AUX_SOURCE_DIRECTORY(src DIR_SRC)

LINK_DIRECTORIES(lib)

add_executable(DB ${DIR_SRC} main.cpp)

TARGET_LINK_LIBRARIES(DB sqlite3)
#add_executable(Test main.cpp ${DIR_CLS})