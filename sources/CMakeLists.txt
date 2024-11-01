add_subdirectory(core)
add_subdirectory(console)

if(STUDY_GROUPS_BUILD_GUI)
    add_subdirectory(gui)
endif()

if(STUDY_GROUPS_BUILD_TESTS)
    add_subdirectory(tests)
endif()