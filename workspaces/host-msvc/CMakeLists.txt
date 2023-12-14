# CMakeList.txt : CMake project for Application, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)

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
    $<$<CONFIG:DEBUG>:_DEBUG>     # MSVC enables assert
)

# TODO: uncomment the following target modules directive when
# working with modules

# add_library(modules OBJECT 
#   src/MeasurementType.ixx 
#   src/Measurement.ixx
#   src/Measurements.ixx
# )

# add_library(modules OBJECT 
#   src/alarm-base.ixx
#   src/alarm-helper.ixx
#   src/alarm-extra.ixx
#   src/alarm.ixx
# )

# add_library(modules OBJECT 
#   src/alarm.ixx
#   src/handler.ixx
# )

if (TARGET modules)
  target_include_directories(modules PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
  )
endif()

# WARNING: wildcards are expanded at generate time, not build time
# regenerate the build if new source files are added

file (GLOB USER_SRC 
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(Application ${USER_SRC})

target_include_directories(Application PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/include
)

if (TARGET modules)
    target_link_libraries(Application PRIVATE modules)
endif()
