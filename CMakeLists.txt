cmake_minimum_required(VERSION 2.4)
####################################################################
# Init Definition
####################################################################
INCLUDE(init.CMakeLists.txt)
INCLUDE(libUnihan-common.CMakeLists.txt)

####################################################################
# Project basic information
####################################################################
PROJECT(libUnihan)
SET(PROJECT_DESCRIPTION "C library for Unihan character database in fifth normal form")
SET(CMAKE_C_FLAGS "-Wall -g")

SET(RELEASE_FILE ${CMAKE_SOURCE_DIR}/RELEASE-NOTES.txt)
SET(RPM_RELEASE_FILE ${CMAKE_SOURCE_DIR}/SPECS/RPM-RELEASE-NOTES.txt)
SETTING_FILE_GET_ATTRIBUTE(PRJ_VER_PATTERN "PRJ_VER" ${RELEASE_FILE})
#MESSAGE("PRJ_VER_PATTERN=${PRJ_VER_PATTERN}")
SETTING_FILE_GET_ATTRIBUTE(PRJ_VER_RELEASE "RPM_RELEASE" ${RPM_RELEASE_FILE})

SET(SO_VER_MAJOR "1")
SET(SO_VER_MINOR "0")

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
SET(DEVELOPER_SETTING_FILE "DEVELOPER_SETTING_NO_PACK")
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
INCLUDE(common.CMakeLists.txt)

####################################################################
# Post Include setting
####################################################################

####################################################################
# RPM configuration
####################################################################
FILE(READ ${CMAKE_SOURCE_DIR}/SPECS/RPM-ChangeLog RPM_CHANGELOG)
GENERATE_SPEC(SPECS/${PROJECT_NAME}.spec.in)

####################################################################
# Definitions
####################################################################
ADD_DEFINITIONS(-DPRJ_VERSION='"${PRJ_VER_FULL}"')
ADD_DEFINITIONS(-DPKGDATADIR='"${PROJECT_DATADIR}"')
ADD_DEFINITIONS(-DSYSTEMDIR='"${PROJECT_DATADIR}"')
ADD_DEFINITIONS(-DSQLITE_MAX_ATTACHED=30)

####################################################################
# Package Dependencies
####################################################################
FIND_PACKAGE(PkgConfig)
PKG_CHECK_MODULES(GLIB2 REQUIRED glib-2.0)
PKG_CHECK_MODULES(SQLITE3 sqlite3)

####################################################################
# Sub directories
####################################################################
#SET(TRANSLATED zh_CN zh_TW)
#ADD_SUBDIRECTORY(po)
ADD_SUBDIRECTORY(src bin)
ADD_SUBDIRECTORY(test)

####################################################################
# Packing
####################################################################

#====================================================================
# Files to be install.
#
SET(MAIN_DOCS AUTHORS README ChangeLog NEWS COPYING COPYING.LESSER)

INSTALL(FILES ${MAIN_DOCS}
    DESTINATION "${PROJECT_DOCDIR}")

#INSTALL(DIRECTORY icons
#    DESTINATION  ${PROJECT_DATADIR})

#====================================================================
# CPack configuration
#

SET(CPACK_RESOURCE_FILE_LICENSE
    ${CMAKE_CURRENT_SOURCE_DIR}/COPYING)
SET(PRJ_COMMON_IGNORE_FILES
    "/docs/"
    "\\\\.cache$"  "\\\\.spec$"
    "ibus-chewing-engine.*\\\\.[ch]$" "maker-dialog.*\\\\.[ch]$"
    "messages.po$"
    )

SET(CPACK_SOURCE_IGNORE_FILES ${CPACK_SOURCE_IGNORE_FILES} ${PRJ_COMMON_IGNORE_FILES} "/bin/"
    "/doc/"  "/www/" ".vis$"
    ".sqlite$" "test/check_phonetic$" "test/check_toneMark$"
    "test/unihan_field_validation$" "Doxyfile$" "UploadPkg.batch$"
    "/UnihanDb/"
    "libUnihan.spec$")

SET(CPACK_PACKAGE_IGNORE_FILES ${CPACK_BINARY_IGNORE_FILES} ${PRJ_COMMON_IGNORE_FILES} "/src/"
    "/test/"
    "\\\\.spec$" "\\\\.in$" "\\\\.pot$")

INCLUDE(CPack)

####################################################################
# Test Suites.
####################################################################
ENABLE_TESTING()

ADD_TEST(check_str_functions_regex_eval
    ${PROJECT_BINARY_DIR}/test/check_str_functions 0)

#ADD_TEST(check_unihan_functions_0
#    ${PROJECT_BINARY_DIR}/test/check_unihan_functions 0)

ADD_TEST(check_phonetic_pinyin_always
    ${PROJECT_BINARY_DIR}/test/check_phonetic 0)
ADD_TEST(check_phonetic_pinyin_original
    ${PROJECT_BINARY_DIR}/test/check_phonetic 1)
ADD_TEST(check_phonetic_pinyin_unihan
    ${PROJECT_BINARY_DIR}/test/check_phonetic 2)
ADD_TEST(check_phonetic_pinyin_trailing
    ${PROJECT_BINARY_DIR}/test/check_phonetic 3)
ADD_TEST(check_phonetic_pinyin_inputMethod
    ${PROJECT_BINARY_DIR}/test/check_phonetic 4)
ADD_TEST(check_phonetic_pinyin_none
    ${PROJECT_BINARY_DIR}/test/check_phonetic 5)
ADD_TEST(check_phonetic_zhuyin_always
    ${PROJECT_BINARY_DIR}/test/check_phonetic 6)

ADD_TEST(toneMark_pinyin_always_f
    ${PROJECT_BINARY_DIR}/test/check_toneMark 0 test)
ADD_TEST(toneMark_pinyin_always_t
    ${PROJECT_BINARY_DIR}/test/check_toneMark 1 test)
ADD_TEST(toneMark_pinyin_original_f
    ${PROJECT_BINARY_DIR}/test/check_toneMark 2 test)
ADD_TEST(toneMark_pinyin_original_t
    ${PROJECT_BINARY_DIR}/test/check_toneMark 3 test)
ADD_TEST(toneMark_pinyin_unihan_f
    ${PROJECT_BINARY_DIR}/test/check_toneMark 4 test)
ADD_TEST(toneMark_pinyin_unihan_t
    ${PROJECT_BINARY_DIR}/test/check_toneMark 5 test)
ADD_TEST(toneMark_pinyin_trailing_f
    ${PROJECT_BINARY_DIR}/test/check_toneMark 6 test)
ADD_TEST(toneMark_pinyin_trailing_t
    ${PROJECT_BINARY_DIR}/test/check_toneMark 7 test)
ADD_TEST(toneMark_pinyin_inputMethod_f
    ${PROJECT_BINARY_DIR}/test/check_toneMark 8 test)
ADD_TEST(toneMark_pinyin_inputMethod_t
    ${PROJECT_BINARY_DIR}/test/check_toneMark 9 test)
ADD_TEST(toneMark_pinyin_none_f
    ${PROJECT_BINARY_DIR}/test/check_toneMark 10 test)
ADD_TEST(toneMark_pinyin_none_t
    ${PROJECT_BINARY_DIR}/test/check_toneMark 11 test)
ADD_TEST(toneMark_zhuyin_always
    ${PROJECT_BINARY_DIR}/test/check_toneMark 12 test)
ADD_TEST(toneMark_zhuyin_original
    ${PROJECT_BINARY_DIR}/test/check_toneMark 13 test)
ADD_TEST(toneMark_zhuyin_inputMethod
    ${PROJECT_BINARY_DIR}/test/check_toneMark 14 test)
ADD_TEST(toneMark_zhuyin_numberical
    ${PROJECT_BINARY_DIR}/test/check_toneMark 15 test)

