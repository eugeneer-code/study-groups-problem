set(TARGET_NAME core)

add_library(${TARGET_NAME} STATIC
    SolveTree.h
    SolveTree.cpp
)

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})