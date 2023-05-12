cmake_minimum_required(VERSION 3.25)
project(complex_calculator C)

set(CMAKE_C_STANDARD 11)

include_directories(core)

add_executable(complex_calculator
        core/complex.c
        core/complex.h
        core/stack.c
        core/stack.h
        core/toPostfix.c
        main.c core/toPostfix.h core/utils.h core/utils.c core/varibleManager.h core/varibleManager.c core/token.h core/token.c core/operations.h core/operations.c)
