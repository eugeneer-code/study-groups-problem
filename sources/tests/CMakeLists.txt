set(TARGET_NAME tests)

add_executable(${TARGET_NAME}
    main.cpp
    microtest.h
)

target_link_libraries(${TARGET_NAME} PRIVATE core)