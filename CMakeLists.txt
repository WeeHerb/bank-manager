cmake_minimum_required(VERSION 3.23)
project(bankman)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(./tui)

aux_source_directory(./src BANK_SRC)

add_executable(${PROJECT_NAME} ${BANK_SRC})
add_dependencies(${PROJECT_NAME} tui)
target_include_directories(${PROJECT_NAME} PUBLIC ./tui/src)
target_link_libraries(${PROJECT_NAME} PUBLIC tui)






