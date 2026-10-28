cmake_minimum_required(VERSION 3.14)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  if(EXISTS "${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake")
    include("${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake")
  elseif(EXISTS "${CMAKE_BINARY_DIR}/conan_toolchain.cmake")
    include("${CMAKE_BINARY_DIR}/conan_toolchain.cmake")
  endif()
endif()

# # # # # # # # # # # # # # # # # #
project(orgengine VERSION 0.2.0 LANGUAGES CXX)
# # # # # # # # # # # # # # # # # #

set(orgengine_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(orgengine_VERSION_MINOR ${PROJECT_VERSION_MINOR})

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_OSX_SYSROOT /)
set(CMAKE_OSX_DEPLOYMENT_TARGET)

cmake_policy(SET CMP0063 NEW)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/etc/cmake)

include(cxx)

set_cxx_ver(14)
enable_testing()

set(INSTALL_BIN_DIR "bin/")

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_subdirectory(src)

install(EXPORT orgengineTargets
    FILE orgengineTargets.cmake
    NAMESPACE orgengine::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/orgengine"
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/orgengineConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/orgengineConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/orgengine"
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/orgengineConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMinorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/orgengineConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/orgengineConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/orgengine"
)
