cmake_minimum_required(VERSION 2.4)

####################################################################
# Project basic information
####################################################################
PROJECT(libUnihan)
SET(CMAKE_C_FLAGS "-Wall")
SET(PRJ_VER_MAJOR "0")
SET(PRJ_VER_MINOR "5")
SET(PRJ_VER_PATCH "4")
SET(PRJ_VER_RELEASE "0")
SET(SO_VER_MAJOR "0")
SET(SO_VER_MINOR "6")

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

SET(GENERATE_DOXYFILE TRUE )
SET(GENERATE_UPLOADPKG_BATCH TRUE)
SET(GENERATE_SPEC TRUE)
INCLUDE(common.CMakeLists.txt)
# MESSAGE("PRJ_VER_FULL=${PRJ_VER_FULL}")

#==================================================================
# Include libUnihan-common.CMakeLists.txt
#
INCLUDE(libUnihan-common.CMakeLists.txt)


####################################################################
# Definitions
####################################################################
ADD_DEFINITIONS(-DPRJ_VERSION='"${PRJ_VER_MAJOR}.${PRJ_VER_MINOR}.${PRJ_VER_PATCH}-${PRJ_VER_RELEASE}"')
ADD_DEFINITIONS(-DSQLITE_MAX_ATTACHED=30)

#==================================================================
# Source code subdirectories
#
FIND_PACKAGE(PkgConfig)
PKG_CHECK_MODULES(GLIB2 glib-2.0)
PKG_CHECK_MODULES(SQLITE3 sqlite3)

ADD_SUBDIRECTORY(src bin)
ADD_SUBDIRECTORY(test)

#ADD_CUSTOM_TARGET(${DB_NAME}
#    COMMAND /bin/ln -sf ${DB_NAME}.${DB_VER}-${DB_RELEASE} ${DB_NAME}
#    DEPENDS ${DB_NAME}.${DB_VER}-${DB_RELEASE})


SET(MAIN_DOCS AUTHORS README ChangeLog NEWS COPYING COPYING.LESSER )

INSTALL(FILES ${MAIN_DOCS} 
    DESTINATION "${docdir}/${PROJECT_NAME}-${PRJ_VER}")



#====================================================================
# CPack configuration
#

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "libUnihan: A C library for Unihan Database")
SET(CPACK_PACKAGE_VENDOR "Red Hat, APAC, Inc.")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
SET(CPACK_RESOURCE_FILE_LICENSE
    ${CMAKE_CURRENT_SOURCE_DIR}/COPYING)
SET(CPACK_RESOURCE_FILE_LICENSE
    ${CMAKE_CURRENT_SOURCE_DIR}/COPYING.LESSER)
SET(PRJ_COMMON_IGNORE_FILES ${COMMON_IGNORE_FILES} ${RPM_IGNORE_FILES}
    "/doc/"  "/www/" ".vis$"
    ".db$" "test/check_phonetic$" "test/check_toneMark$"
    "test/unihan_field_validation$" "Doxyfile$" "UploadPkg.batch$"
    "/UnihanDb/"
    "libUnihan.spec$")

SET(CPACK_SOURCE_IGNORE_FILES ${PRJ_COMMON_IGNORE_FILES} "/bin/" 
    "-db$" ".cache$")
SET(CPACK_PACKAGE_IGNORE_FILES ${PRJ_COMMON_IGNORE_FILES} "/src/" "/test/"
    ".spec$" ".in$" )

INCLUDE(CPack)


#====================================================================
# Upload the package releases to hosting service provider (Source forge).
#

ADD_CUSTOM_TARGET(ChangeLog
    COMMAND echo "* ${DATE} - ${AUTHORS} <${MAINTAINER_EMAIL}> - ${PRJ_VER_FULL}" > ChangeLog
    COMMAND cat ChangeLog.in >> ChangeLog
    DEPENDS ChangeLog.in
    COMMENT "Making ChangeLog"
    VERBATIM
    )

ADD_DEPENDENCIES(pack_src ChangeLog)


####################################################################
# Test Suites.
####################################################################
ENABLE_TESTING()

