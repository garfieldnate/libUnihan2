cmake_minimum_required(VERSION 2.4)

####################################################################
# Project basic information
####################################################################
PROJECT(UnihanDb)
SET(CMAKE_C_FLAGS "-Wall")
SET(PRJ_VER_MAJOR "5")
SET(PRJ_VER_MINOR "1")
SET(PRJ_VER_PATCH "0")
SET(PRJ_VER_RELEASE "8")

# For CVS changelog
SET(CHANGE_SUMMARY "This release fixes the no API documents, also corrects some functions in  collection.[ch], file_functions.[ch]")

SET(SUPPORTED_DIST_TAGS F-9 F-10 EL-5) 
SET(BODHI_DIST_TAGS fc9 fc10)


####################################################################
# Includes
####################################################################



#==================================================================
# Include common.CMakeLists.txt
#
SET(IS_NOARCH)
SET(GENERATE_UPLOADPKG_BATCH TRUE)
SET(GENERATE_SPEC TRUE)
INCLUDE(common.CMakeLists.txt)

SET(DB_DIR ${datadir}/${DB_PRJ_NAME})
ADD_DEFINITIONS(-DPRJ_VER='"${PRJ_VER_FULL}"')

#==================================================================
# Include libUnihan-common.CMakeLists.txt
#
INCLUDE(libUnihan-common.CMakeLists.txt)


####################################################################
# Required header files and library
####################################################################


FIND_PACKAGE(PkgConfig)
PKG_CHECK_MODULES(GLIB2 glib-2.0)
PKG_CHECK_MODULES(SQLITE3 sqlite3)

FIND_PATH(UNIHAN_H_DIR NAMES Unihan.h PATHS /usr/include /usr/include/libUnihan
    /usr/local/include /usr/local/include/libUnihan)
# Location of library include files
INCLUDE_DIRECTORIES(${GLIB2_INCLUDE_DIRS} ${SQLITE3_INCLUDE_DIRS} ../src
    ${UNIHAN_H_DIR})


# Library location for the linker
LINK_DIRECTORIES(${GLIB2_LIBRARY_DIRS} ${SQLITE3_LIBRARY_DIRS} ../bin)


#==================================================================
# Source code and documents
#

SET(EXECUTABLE_OUTPUT_PATH bin)
SET(LIBRARY_OUTPUT_PATH bin)

SET(UnihanDb_SRCS unihan_search_db.c)

# executable built from some source
ADD_EXECUTABLE(unihan_search_db  ${UnihanDb_SRCS})

# Link the executable to the library.
TARGET_LINK_LIBRARIES(unihan_search_db Unihan)

SET(MAIN_DOCS README ChangeLog NEWS )

INSTALL(FILES ${MAIN_DOCS} 
    DESTINATION "${docdir}/${PROJECT_NAME}-${PRJ_VER}")


INSTALL(TARGETS unihan_search_db
     RUNTIME DESTINATION bin
)


#====================================================================
# CPack configuration
#

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "libUnihan: A C library for Unihan Database")
SET(CPACK_PACKAGE_VENDOR "Red Hat, APAC, Inc.")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
SET(PRJ_COMMON_IGNORE_FILES ${COMMON_IGNORE_FILES} ${RPM_IGNORE_FILES}
    "Unihan.spec$")

SET(CPACK_SOURCE_IGNORE_FILES ${PRJ_COMMON_IGNORE_FILES} "/bin/" ".db-"
    ".db$" ".cache$")
SET(CPACK_PACKAGE_IGNORE_FILES ${PRJ_COMMON_IGNORE_FILES}  ".in$" )
INCLUDE(CPack)


ADD_CUSTOM_TARGET(ChangeLog
    COMMAND echo "* ${DATE} - ${AUTHORS} <${MAINTAINER_EMAIL}> - ${PRJ_VER_FULL}" > ChangeLog
    COMMAND cat ChangeLog.in >> ChangeLog
    DEPENDS ChangeLog.in
    COMMENT "Making ChangeLog"
    VERBATIM
    )
ADD_DEPENDENCIES(pack_src ChangeLog)

