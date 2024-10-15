cmake_minimum_required(VERSION 3.21)
project(target-system LANGUAGES C CXX)

add_library(modules OBJECT 
  ${PROJECT_SOURCE_DIR}/alarm-base.ixx
  ${PROJECT_SOURCE_DIR}/alarm-helper.ixx
  ${PROJECT_SOURCE_DIR}/alarm-extra.ixx
  ${PROJECT_SOURCE_DIR}/alarm.ixx
)

target_include_directories(modules PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/include
)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  target_compile_options(modules PRIVATE
    -xc++
  )
endif()
