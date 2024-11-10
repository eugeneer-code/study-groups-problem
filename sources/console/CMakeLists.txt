set(TARGET_NAME study-groups-cli)

add_executable(${TARGET_NAME}
    main.cpp
    Generator.h
    Generator.cpp
)

target_link_libraries(${TARGET_NAME} PRIVATE core)

install(FILES ${TARGET_NAME} DESTINATION .)