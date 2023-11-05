cmake_minimum_required(VERSION 3.16)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(ogre_study)

find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)

add_library(common INTERFACE)
target_compile_features(common INTERFACE cxx_std_20)
target_compile_options(common INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /utf-8 /GR- /EHa->
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-W -Wall -fno-rtti -fno-exceptions>)
target_link_libraries(common INTERFACE OgreBites)

add_subdirectory(first-step)
