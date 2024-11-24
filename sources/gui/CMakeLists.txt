set(TARGET_NAME study-groups)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(${TARGET_NAME} WIN32
    main.cpp
    Core.h
    Core.cpp
    ImportanceModel.h
    ImportanceModel.cpp
    GradesModel.h
    GradesModel.cpp
    GroupsModel.h
    GroupsModel.cpp
    SolveWrapper.h
    SolveWrapper.cpp
    Bruteforce.h
    Bruteforce.cpp
    BFResultModel.h
    BFResultModel.cpp
    BFCalc.h
    BFCalc.cpp
    res.qrc
)

target_link_libraries(${TARGET_NAME} PRIVATE core Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::QuickControls2)

install(TARGETS ${TARGET_NAME} DESTINATION .)

# Установка библиотек Qt для Windows
if(WIN32)
    # Поиск пути до windeployqt
    if(NOT TARGET Qt6::windeployqt)
        get_target_property(_qt6_qmake_location Qt6::qmake IMPORTED_LOCATION)
        execute_process(
            COMMAND "${_qt6_qmake_location}" -query QT_INSTALL_PREFIX
            RESULT_VARIABLE return_code
            OUTPUT_VARIABLE qt6_install_prefix
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        set(imported_location "${qt6_install_prefix}/bin/windeployqt.exe")
        if(EXISTS ${imported_location})
            add_executable(Qt6::windeployqt IMPORTED)
            set_target_properties(Qt6::windeployqt PROPERTIES IMPORTED_LOCATION ${imported_location})
        endif()
    endif()

    # Копирование зависимостей во временную папку
    add_custom_command(TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_BINARY_DIR}/windeployqt"
        COMMAND Qt6::windeployqt --dir "${CMAKE_CURRENT_BINARY_DIR}/windeployqt" "$<TARGET_FILE:${TARGET_NAME}>" --qmldir ${CMAKE_CURRENT_SOURCE_DIR}
    )

    # Установка зависимостей
    install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/windeployqt/" DESTINATION .)
endif()