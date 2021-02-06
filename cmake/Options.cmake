################################################################################
##                                    ctlepage
##
## This file is distributed under the 4-clause Berkeley Software Distribution
## License. See LICENSE for details.
################################################################################
# User-settable options
option(CTLEPAGE_BUILD_TESTS "Build ctlepage unit tests" ON)

# Internals options
set(CTLEPAGE_CXX_STANDARD "cxx_std_20" CACHE INTERNAL "CXX Standard used to build ctlepage")
