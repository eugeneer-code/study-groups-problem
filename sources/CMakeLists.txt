add_subdirectory(core)
add_subdirectory(console)

if(STUDY_GROUPS_BUILD_GUI)
    add_subdirectory(gui)
endif()

if(STUDY_GROUPS_BUILD_TESTS)
    add_subdirectory(tests)
endif()

# Установка С++ зависимостей для Windows
if(WIN32)
    set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
    include(InstallRequiredSystemLibraries)
    install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION .)
endif()