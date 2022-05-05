################################################################################
##                                    lepage
##
## This file is distributed under the 3-clause Berkeley Software Distribution
## License. See LICENSE for details.
################################################################################
cmake_minimum_required(VERSION 3.19)

project(lepage CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(Options)
include(utils)
include(UnitTest)
include(CodeCoverage)

enable_unit_test(GOOGLETEST_VERSION "main")
enable_code_coverage()

include_directories(src)
add_subdirectory(src/lepage)