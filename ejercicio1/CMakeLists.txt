cmake_minimum_required(VERSION 3.5)

project(ejercicio1 LANGUAGES C)

add_executable(ejercicio1 main.c
    imagen.h
)

include(GNUInstallDirs)
install(TARGETS ejercicio1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
