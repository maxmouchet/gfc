cmake_minimum_required(VERSION 3.12)
project(gfc VERSION 0.1.1)

add_library(gfc src/gfc.c)
target_compile_options(gfc PRIVATE -Wall -Wextra -pedantic)
target_include_directories(gfc PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(gfc PRIVATE m)

add_executable(gfc_test src/gfc_test.c)
target_compile_options(gfc_test PRIVATE -Wall -Wextra -pedantic)
target_link_libraries(gfc_test PRIVATE gfc)
target_link_options(gfc_test PRIVATE -fsanitize=address -fsanitize=undefined)
