cmake_minimum_required(VERSION 3.31)
project(exercicios_algoritimos C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(exercicios_algoritimos
        include/student_manager.h
        include/application.h
        include/pool.h

        main.c
        student_manager.c

        include/utils.h
        include/map.h
        include/ui.h
)
