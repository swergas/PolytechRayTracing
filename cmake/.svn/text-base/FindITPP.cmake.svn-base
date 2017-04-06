### FindITPP.cmake --- Search for the it++ lib
## 
## Author: Jean-Christophe Lombardo
## Copyright (C) 2011 - Jean-Christophe Lombardo, Inria
## Created: Thu Jun  9 17:19:56 2011
## Last-Updated:  Thu Jun  9 17:24:10 2011
##           By: Jean-Christophe Lombardo
##
######################################################################
#  ITPP_INCLUDE_DIR - where to find itpp/itbase.h, etc.
#  ITPP_LIBRARY   - List of libraries when using apf.
#  ITPP_FOUND       - True if apf is found.

set(ITPP_DIR $ENV{ITPP__DIR} CACHE PATH "ITPP root dir (if not standard)")

find_path(ITPP_INCLUDE_DIR itpp/itbase.h
        PATHS ${ITPP_DIR}/include
)

find_library(ITPP_LIBRARY NAMES itpp
        PATHS
            ${ITPP_DIR}/lib
)

# handle the QUIETLY and REQUIRED arguments and set ITPP_FOUND to TRUE if 
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ITPP DEFAULT_MSG
    ITPP_LIBRARY ITPP_INCLUDE_DIR
)

## -*- tab-width: 4; indent-tabs-mode: nil c-basic-offset: 4 -*-
## vim:cindent:ts=4:sw=4:et:tw=80:sta:

