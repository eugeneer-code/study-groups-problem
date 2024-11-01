cmake_minimum_required(VERSION 3.18)
project(study_groups_problem)

set(CMAKE_CXX_STANDARD 17)

option(STUDY_GROUPS_BUILD_TESTS "Build library unit tests" OFF)
option(STUDY_GROUPS_BUILD_GUI "Build gui application" OFF)

add_subdirectory(sources)