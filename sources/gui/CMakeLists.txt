set(TARGET_NAME study-groups)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(${TARGET_NAME}
    main.cpp
    Core.h
    Core.cpp
    ImportanceModel.h
    ImportanceModel.cpp
    GradesModel.h
    GradesModel.cpp
    res.qrc
)

target_link_libraries(${TARGET_NAME} PRIVATE core Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::QuickControls2)