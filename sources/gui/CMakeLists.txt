set(TARGET_NAME study-groups)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)
set(CMAKE_AUTOMOC ON)

add_executable(${TARGET_NAME}
    main.cpp
)

target_link_libraries(${TARGET_NAME} PRIVATE core Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick)