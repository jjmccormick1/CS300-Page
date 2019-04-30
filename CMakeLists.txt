cmake_minimum_required(VERSION 3.13)
project(CS300-Page C)

set(CMAKE_C_STANDARD 11)

add_executable(disk disk.c disk.h)
add_executable(gen gen.c)
add_executable(sched sched.c sched.h proc.c proc.h procgen.c procgen.h page.c page.h)
target_link_libraries(sched m)
add_executable(procgen procgen.c procgen.h)