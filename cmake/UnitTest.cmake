################################################################################
##                                    ctlepage
##
## This file is distributed under the 4-clause Berkeley Software Distribution
## License. See LICENSE for details.
################################################################################
if(NOT CTLEPAGE_BUILD_TESTS)
    macro(enable_unit_test)
    endmacro()
    function(add_unit_test)
    endfunction()

    return()
endif()

macro(enable_unit_test)
    find_package(GTest REQUIRED)

    enable_testing()
endmacro()

function(add_unit_test TEST_TARGET)
    add_executable(unittest-${TEST_TARGET} ${ARGN})
    target_compile_features(unittest-${TEST_TARGET} PRIVATE ${CTLEPAGE_CXX_STANDARD})
    target_link_libraries(unittest-${TEST_TARGET} GTest::GTest GTest::Main)
    gtest_discover_tests(unittest-${TEST_TARGET} EXTRA_ARGS --gtest_color=yes)
endfunction()
