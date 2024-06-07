cmake_minimum_required (VERSION 3.28)

project ("Application")

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
	/std:c++latest
    /experimental:module
    /DWIN32 
    /D_WINDOWS 
    /W4 
    /GR 
    /EHsc
    $<$<CONFIG:DEBUG>:/Od>
    $<$<CONFIG:RELEASE>:/O2>
)

add_compile_definitions(
    $<$<CONFIG:DEBUG>:DEBUG>
)

add_library(alarm)
target_sources(alarm
  PUBLIC
    FILE_SET CXX_MODULES FILES
      ${CMAKE_SOURCE_DIR}/src/alarm.ixx
)

target_include_directories(alarm PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/include
)

add_library(handler)
target_sources(handler
  PUBLIC
    FILE_SET CXX_MODULES FILES
      ${CMAKE_SOURCE_DIR}/src/handler.ixx
)

target_include_directories(handler PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(handler PRIVATE alarm)

add_executable(Application 
  ${CMAKE_SOURCE_DIR}/src/alarm.cpp
  ${CMAKE_SOURCE_DIR}/src/handler.cpp
  ${CMAKE_SOURCE_DIR}/src/main.cpp
)

target_include_directories(Application PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(Application PRIVATE handler)

