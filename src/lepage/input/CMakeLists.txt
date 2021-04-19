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

add_unit_test(unittest-input
    SourceLocationProvider.test.cpp
    SingleInputBuffer.test.cpp
)
target_compile_features(unittest-input PRIVATE ${LEPAGE_CXX_STANDARD})
