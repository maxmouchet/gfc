cmake_minimum_required(VERSION 3.12)
project(
  gfc
  VERSION 1.0.3
  LANGUAGES C
)

option(WITH_SANITIZER "Enable compiler sanitizers" OFF)

if(WITH_SANITIZER)
  set(SANITIZER_FLAGS "-fsanitize=address -fsanitize=undefined")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SANITIZER_FLAGS}")
endif()

add_library(gfc src/gfc.c)
target_compile_features(gfc PUBLIC c_std_99)
target_compile_options(gfc PRIVATE -Wall -Wextra -pedantic)
target_include_directories(gfc PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(gfc PRIVATE m)

add_executable(gfc_bench src/gfc_bench.c)
target_compile_options(gfc_bench PRIVATE -Wall -Wextra -pedantic)
target_link_libraries(gfc_bench PRIVATE gfc)

add_executable(gfc_test src/gfc_test.c)
target_compile_options(gfc_test PRIVATE -Wall -Wextra -pedantic)
target_link_libraries(gfc_test PRIVATE gfc)
