cmake_minimum_required(VERSION 2.4)
####################################################################
# Init Definition
####################################################################
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ../cmake_modules)
INCLUDE(../init.CMakeLists.txt)
INCLUDE(../libUnihan-common.CMakeLists.txt)

####################################################################
# Project basic information
####################################################################
PROJECT(UnihanDb)
SET(PROJECT_DESCRIPTION "The Unihan character database in fifth normal form")
SET(CMAKE_C_FLAGS "-Wall -g")

SET(RELEASE_FILE ${CMAKE_SOURCE_DIR}/RELEASE-NOTES.txt)
SET(RPM_RELEASE_FILE ${CMAKE_SOURCE_DIR}/SPECS/RPM-RELEASE-NOTES.txt)
SETTING_FILE_GET_ATTRIBUTE(PRJ_VER_PATTERN "PRJ_VER" ${RELEASE_FILE})
#MESSAGE("PRJ_VER_PATTERN=${PRJ_VER_PATTERN}")
SETTING_FILE_GET_ATTRIBUTE(PRJ_VER_RELEASE "RPM_RELEASE" ${RPM_RELEASE_FILE})

# For CVS/SVN/GIT change message
SETTING_FILE_GET_ATTRIBUTE(CHANGE_SUMMARY "SUMMARY" ${RELEASE_FILE})
#MESSAGE("### CHANGE_SUMMARY=${CHANGE_SUMMARY}")

# Changelog items
COMMAND_OUTPUT_TO_VARIABLE(CHANGELOG_ITEMS tail -n +5 ${RELEASE_FILE})
#MESSAGE("### CHANGELOG_ITEMS=${CHANGELOG_ITEMS}|")

STRING(COMPARE GREATER "${PRJ_VER_RELEASE}" "1" NEED_RPM_RELEASE_INFO)
IF(${NEED_RPM_RELEASE_INFO})
    SETTING_FILE_GET_ATTRIBUTE(RPM_RELEASE_SUMMARY "RPM_RELEASE_SUMMARY" ${RPM_RELEASE_FILE})
    COMMAND_OUTPUT_TO_VARIABLE(RPM_CHANGELOG_ITEMS tail -n +5 ${RPM_RELEASE_FILE})
ELSE(${NEED_RPM_RELEASE_INFO})
    SET(RPM_RELEASE_SUMMARY ${CHANGE_SUMMARY})
    SET(RPM_CHANGELOG_ITEMS ${CHANGELOG_ITEMS})
ENDIF(${NEED_RPM_RELEASE_INFO})
#MESSAGE("### RPM_RELEASE_SUMMARY=${RPM_RELEASE_SUMMARY}")
#MESSAGE("### RPM_CHANGELOG_ITEMS=|${RPM_CHANGELOG_ITEMS}|")

#==================================================================
# Developer setting.
#
SET(CVS_DIST_TAGS F-10 F-11 EL-5)
SET(HOSTING_SERVICE_PROVIDER "Source Forge")
SET(DEVELOPER_SETTING_FILE "../DEVELOPER_SETTING_NO_PACK")
SET(DEVELOPER_DEPENDS UploadPkg.batch.in)
IF(EXISTS ${DEVELOPER_SETTING_FILE})
    INCLUDE(Developer)
    CONFIGURE_FILE(UploadPkg.batch.in UploadPkg.batch)
    ADD_CUSTOM_TARGET(commit
	COMMAND svn commit -m "${CHANGE_SUMMARY}"
	COMMENT "Commit the changes"
	)

    SETTING_FILE_GET_ATTRIBUTE(SSH_USER "SSH_USER" ${DEVELOPER_SETTING_FILE})
    SETTING_FILE_GET_ATTRIBUTE(SSH_ARGS "SSH_ARGS" ${DEVELOPER_SETTING_FILE})

    DEVELOPER_UPLOAD(SERVERTYPE sftp
	USER ${SSH_USER}
	BATCH "UploadPkg.batch"
	SITE "frs.sourceforge.net"
	OPTIONS ${SSH_ARGS}
	)
ENDIF(EXISTS ${DEVELOPER_SETTING_FILE})

####################################################################
# Includes
####################################################################
#INCLUDE(Gettext)

#==================================================================
# Include common.CMakeLists.txt
#
INCLUDE(../common.CMakeLists.txt)

####################################################################
# Post Include setting
####################################################################

####################################################################
# RPM configuration
####################################################################
FILE(READ ${CMAKE_SOURCE_DIR}/SPECS/RPM-ChangeLog RPM_CHANGELOG)
GENERATE_SPEC(SPECS/project.spec.in)

####################################################################
# Definitions
####################################################################
ADD_DEFINITIONS(-DPRJ_VERSION='"${PRJ_VER_FULL}"')
ADD_DEFINITIONS(-DPKGDATADIR='"${PROJECT_DATADIR}"')
ADD_DEFINITIONS(-DSYSTEMDIR='"${PROJECT_DATADIR}"')

####################################################################
# Package Dependencies
####################################################################
FIND_PACKAGE(PkgConfig)
PKG_CHECK_MODULES(GLIB2 glib-2.0)
PKG_CHECK_MODULES(SQLITE3 sqlite3)
#PKG_CHECK_MODULES(LIBUNIHAN libunihan-1)

####################################################################
# Sub directories
####################################################################
#SET(TRANSLATED zh_CN zh_TW)

####################################################################
# Targets
####################################################################
#==================================================================
# Source code and documents
#

SET(EXECUTABLE_OUTPUT_PATH bin)
SET(LIBRARY_OUTPUT_PATH bin)

SET(UnihanDb_SRCS unihan_rebuild_cache.c)

# executable built from some source
#ADD_EXECUTABLE(unihan_rebuild_cache  ${UnihanDb_SRCS})

# Link the executable to the library.
#TARGET_LINK_LIBRARIES(unihan_rebuild_cache Unihan)
# Location of library include files
INCLUDE_DIRECTORIES(${GLIB2_INCLUDE_DIRS} ${SQLITE3_INCLUDE_DIRS} ${LIBUNIHAN_INCLUDE_DIRS} ../src)
# Library location for the linker
LINK_DIRECTORIES(${GLIB2_LIBRARY_DIRS} ${SQLITE3_LIBRARY_DIRS} ${LIBUNIHAN_LIBRARY_DIRS} ../bin)

####################################################################
# Packing
####################################################################

#====================================================================
# Files to be install.
#
SET(MAIN_DOCS README ChangeLog NEWS )
INSTALL(FILES ${MAIN_DOCS}
    DESTINATION "${docdir}/${PROJECT_NAME}-${PRJ_VER}")

#INSTALL(TARGETS unihan_rebuild_cache
#    RUNTIME DESTINATION bin
#    )

#INSTALL(DIRECTORY icons
#    DESTINATION  ${PROJECT_DATADIR})

#====================================================================
# CPack configuration
#

SET(CPACK_RESOURCE_FILE_LICENSE
    ${CMAKE_CURRENT_SOURCE_DIR}/copyright.html)
SET(PRJ_COMMON_IGNORE_FILES ${COMMON_IGNORE_FILES} ${RPM_IGNORE_FILES}
    "UnihanDb.spec$")

SET(CPACK_SOURCE_IGNORE_FILES ${PRJ_COMMON_IGNORE_FILES} "/bin/" ".db-"
    ".db$" ".cache$")
SET(CPACK_PACKAGE_IGNORE_FILES ${PRJ_COMMON_IGNORE_FILES}  ".in$" )
INCLUDE(CPack)

