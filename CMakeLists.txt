cmake_minimum_required(VERSION 3.31)
project(intro_cc C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(intro_cc
        include/student_manager.h
        include/application.h
        include/pool.h

        main.c
        student_manager.c

        include/utils.h
        include/map.h
        include/ui.h
)
