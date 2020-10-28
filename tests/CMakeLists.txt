cmake_minimum_required(VERSION 3.12)
project(HOSA_TESTS)

add_executable(${PROJECT_NAME} main.cpp ../hosa.h)
add_subdirectory(googletest)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_link_libraries(${PROJECT_NAME} PRIVATE gtest)