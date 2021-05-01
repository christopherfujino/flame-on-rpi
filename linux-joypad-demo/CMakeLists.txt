cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(joystick VERSION 1.0.0 LANGUAGES C)
add_library(joystick SHARED main.c)
add_executable(main main.c)

set_target_properties(joystick PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    OUTPUT_NAME "joystick_library"
)
