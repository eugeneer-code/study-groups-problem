set(TARGET_NAME tests)

find_package(Qt6 REQUIRED COMPONENTS Test)

enable_testing(true)

qt_add_executable(${TARGET_NAME}
    CoreTest.h
    CoreTest.cpp
    main.cpp
)
add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})

target_link_libraries(${TARGET_NAME} PRIVATE core Qt6::Test Qt6::Core)