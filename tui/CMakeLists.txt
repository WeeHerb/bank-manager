cmake_minimum_required(VERSION 3.23)
project(final_homework_tui)

set(CMAKE_CXX_STANDARD 20)

aux_source_directory(./src  TUI_SRC)
include_directories(./src)

add_library(tui STATIC ${TUI_SRC})