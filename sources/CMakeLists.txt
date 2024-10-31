add_subdirectory(core)
add_subdirectory(console)
add_subdirectory(gui)

if(STUDY_GROUPS_BUILD_TESTS)
    add_subdirectory(tests)
endif()