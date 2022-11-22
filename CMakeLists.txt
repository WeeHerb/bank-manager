cmake_minimum_required(VERSION 3.23)
project(bankmanager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

include_directories(./src)

# Core configuration below
file(GLOB_RECURSE BANK_SRC
        src/*.cpp
        src/*.hpp)

foreach (ITEM ${BANK_SRC})
    message(${ITEM})
endforeach ()

add_executable(${PROJECT_NAME} ${BANK_SRC})
target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++ -static)

# AES module configuration below

file(GLOB AES_SRC
        src/aes/*.cpp
        test/*.cpp)
add_executable(aes-test ${AES_SRC})