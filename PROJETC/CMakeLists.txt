cmake_minimum_required(VERSION 3.21)
project(ProjetC C)

set(CMAKE_C_STANDARD 99)

add_executable(ProjetC main.c Adverbe.c Adverbe.h Nom.c Nom.h Verbe.c Verbe.h)
