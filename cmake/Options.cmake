################################################################################
##                                    lepage
##
## This file is distributed under the 3-clause Berkeley Software Distribution
## License. See LICENSE for details.
################################################################################
# User-settable options
option(LEPAGE_BUILD_TESTS "Build lepage unit tests" ON)

# Internals options
set(LEPAGE_CXX_STANDARD "cxx_std_20" CACHE INTERNAL "CXX Standard used to build lepage")
