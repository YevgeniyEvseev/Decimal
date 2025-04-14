cmake_minimum_required(VERSION 3.2)

set(project_name Decimal)

project(${project_name} VERSION 0.1 LANGUAGES C)

add_executable(${project_name}
main.c 
another.c 
bcd.c
arithmetic_decimal.c
)
