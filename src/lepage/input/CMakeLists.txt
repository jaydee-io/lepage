################################################################################
##                                    lepage
##
## This file is distributed under the 3-clause Berkeley Software Distribution
## License. See LICENSE for details.
################################################################################

add_library(${CMAKE_PROJECT_NAME}-input INTERFACE
    # Interfaces
    InputBuffer.h
    # Data structures
    Lexeme.h
    SourceLocation.h
    # Implementations
    SourceLocationProvider.h
    SingleInputBuffer.h
)
target_link_libraries(${CMAKE_PROJECT_NAME}-input INTERFACE ${CMAKE_PROJECT_NAME}-details)
target_code_coverage(${CMAKE_PROJECT_NAME}-input INTERFACE)

# Unit tests
set(UNITTESTS_NAME lepage_input_tests)
add_unit_test(TARGET ${UNITTESTS_NAME}
    SourceLocationProvider.test.cpp
    SingleInputBuffer.test.cpp
)
target_compile_features(${UNITTESTS_NAME} PRIVATE ${LEPAGE_CXX_STANDARD})
target_link_libraries(${UNITTESTS_NAME} PRIVATE ${CMAKE_PROJECT_NAME}-input)
