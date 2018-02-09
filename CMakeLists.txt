cmake_minimum_required(VERSION 3.7)
project(Guesser)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Debug/src/guesser.d
        Debug/src/guesser.o
        Debug/src/subdir.mk
        Debug/guesser
        Debug/makefile
        Debug/objects.mk
        Debug/sources.mk
        src/guesser.c)

add_executable(Guesser ${SOURCE_FILES})