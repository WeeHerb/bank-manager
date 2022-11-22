cmake_minimum_required(VERSION 3.23)
project(bankmanager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

include_directories(./)

# AES module configuration below
file(GLOB AES_SRC
        aes/*.cpp
        test/*.cpp)
add_executable(aes-test ${AES_SRC})

# Core configuration below

file(GLOB BANK_SRC
        core/*.cpp core/**/*.cpp
        tui/*.cpp tui/**/*.cpp
        db/*.cpp db/**/*.cpp
        logger/*.cpp)

add_executable(${PROJECT_NAME} ${BANK_SRC})
target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++ -static)