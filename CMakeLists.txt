cmake_minimum_required(VERSION 3.23)
project(bankmanager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

include_directories(./src)

# Bankmanager configuration below

# Split core and no-core since no-core module need test
# core and no-core will be static-linked to a executable file
file(GLOB_RECURSE BANK_SRC
        src/*.cpp
        src/*.hpp)
foreach (FILE_PATH ${BANK_SRC})
    file(RELATIVE_PATH REL_FILE_PATH ${PROJECT_SOURCE_DIR} ${FILE_PATH})
    if (NOT ${REL_FILE_PATH} MATCHES "src/core/main.cpp")
        list(APPEND BANK_SRC_NOCORE ${FILE_PATH})
    else ()
        list(APPEND BANK_SRC_CORE ${FILE_PATH})
    endif ()
endforeach ()
add_library(${PROJECT_NAME}_nocore STATIC ${BANK_SRC_NOCORE})
add_executable(${PROJECT_NAME} ${BANK_SRC_CORE})
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_nocore)
target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++ -static)

# Test configuration

# init gtest
enable_testing()
include(FetchContent)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# add testcase
file(GLOB_RECURSE TESTCASE_SRC
        tests/*.cpp)
foreach (FILE_PATH ${TESTCASE_SRC})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${FILE_PATH})
    message("Testcase: " ${FILE_NAME})

    add_executable(${FILE_NAME}
            ${FILE_PATH})
    target_link_libraries(
            ${FILE_NAME}
            GTest::gtest_main
            ${PROJECT_NAME}_nocore
    )
    gtest_discover_tests(${FILE_NAME})
endforeach ()