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

# Пусть для установки по умолчанию
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "default install path" FORCE)
endif()