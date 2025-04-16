cmake_minimum_required(VERSION 3.2)

set(ProjectName Decimal)

project(${ProjectName} VERSION 0.1 LANGUAGES C)

add_executable(debug
bcd.c 
test.c 
decimal_main.c 
mantissa.c 
)

add_executable(test_decimal
bcd.c 
check.c 
decimal_main.c 
mantissa.c 
)

target_link_libraries(debug PRIVATE m)
target_link_libraries(test_decimal PRIVATE m check subunit rt pthread )