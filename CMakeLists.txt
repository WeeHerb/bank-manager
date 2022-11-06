cmake_minimum_required(VERSION 3.23)
project(bankmanager)

set(CMAKE_CXX_STANDARD 17)

include_directories(./)

file(GLOB BANK_SRC
        core/*.cpp core/**/*.cpp
        tui/*.cpp tui/**/*.cpp
        db/*.cpp db/**/*.cpp
        logger/*.cpp)

foreach(ITEM ${BANK_SRC})
    message(${ITEM})
endforeach()

add_executable(${PROJECT_NAME} ${BANK_SRC})