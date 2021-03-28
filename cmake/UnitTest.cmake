################################################################################
##                                    lepage
##
## This file is distributed under the 4-clause Berkeley Software Distribution
## License. See LICENSE for details.
################################################################################
if(NOT LEPAGE_BUILD_TESTS)
    macro(enable_unit_test)
    endmacro()
    function(add_unit_test)
    endfunction()

    return()
endif()

macro(find_googletest)
    # First, try the system wide installation
    find_package(GTest)
    if(GTEST_FOUND)
        set(LEPAGE_INTERNAL_UNIT_TESTS_LIBS GTest::GTest GTest::Main CACHE INTERNAL "INTERNAL Unit tests libraries to link")
    # If not available, try fetching from github
    else()
        message(STATUS "Fetching GoogleTest from GitHub")
        include(FetchContent)

        FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        release-1.10.0
        )
        
        FetchContent_GetProperties(googletest)
        if(NOT googletest_POPULATED)
            FetchContent_Populate(googletest)
            add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
        endif()
        message(STATUS "Fetching GoogleTest from GitHub - done")

        include(GoogleTest)
        set(LEPAGE_INTERNAL_UNIT_TESTS_LIBS gtest gmock gtest_main CACHE INTERNAL "INTERNAL Unit tests libraries to link")
    endif()
endmacro()

macro(enable_unit_test)
    find_googletest()
    enable_testing()
endmacro()

function(add_unit_test TEST_TARGET)
    add_executable(unittest-${TEST_TARGET} ${ARGN})
    target_compile_features(unittest-${TEST_TARGET} PRIVATE ${LEPAGE_CXX_STANDARD})
    target_link_libraries(unittest-${TEST_TARGET} ${LEPAGE_INTERNAL_UNIT_TESTS_LIBS})
    gtest_discover_tests(unittest-${TEST_TARGET} EXTRA_ARGS --gtest_color=yes)
endfunction()
