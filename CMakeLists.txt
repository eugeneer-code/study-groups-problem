cmake_minimum_required(VERSION 3.18)
project(study_groups_problem)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core)
set(CMAKE_AUTOMOC ON)

option(STUDY_GROUPS_BUILD_TESTS "Build library unit tests" ON)

add_subdirectory(sources)