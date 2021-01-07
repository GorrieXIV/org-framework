cmake_minimum_required(VERSION 3.5)

# # # # # # # # # # # # # # # # # #
project(orgengine)
# # # # # # # # # # # # # # # # # #

set(orgengine_VERSION_MAJOR 0)
set(orgengine_VERSION_MINOR 2)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_OSX_SYSROOT /)
set(CMAKE_OSX_DEPLOYMENT_TARGET)

cmake_policy(SET CMP0063 NEW)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/etc/cmake)

include(cxx)

set_cxx_ver(14)
enable_testing()

if(USE_LOCAL_LIBS)
    add_subdirectory(json)
else()
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

set(INSTALL_BIN_DIR "bin/")

add_subdirectory(src)
