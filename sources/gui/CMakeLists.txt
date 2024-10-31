set(TARGET_NAME study-groups)

add_executable(${TARGET_NAME}
    main.cpp
)

find_package(Qt6 REQUIRED COMPONENTS Gui Qml Quick)

target_link_libraries(${TARGET_NAME} PRIVATE core)