####################################################################
# Project basic information
####################################################################
PROJECT(libUnihan)
SET(CMAKE_C_FLAGS "-Wall")
SET(PRJ_VER_MAJOR "0")
SET(PRJ_VER_MINOR "5")
SET(PRJ_VER_PATCH "4")
SET(PRJ_VER_RELEASE "0")
SET(PRJ_VER ${PRJ_VER_MAJOR}.${PRJ_VER_MINOR}.${PRJ_VER_PATCH})
SET(PRJ_VER_FULL  ${PRJ_VER_MAJOR}.${PRJ_VER_MINOR}.${PRJ_VER_PATCH}-${PRJ_VER_RELEASE})
SET(DB_VER "5.1.0")
SET(DB_RELEASE "7")
SET(DB_PRJ_NAME  "UnihanDb")
SET(DB_NAME "Unihan.db")

SET(SUPPORTED_DIST_TAGS F-9 F-10 EL-5) 
SET(BODHI_DIST_TAGS fc9 fc10)

# For CVS changelog
SET(CVS_CHANGELOG "This release fixes the no API documents, also corrects some functions in  collection.[ch], file_functions.[ch]")



####################################################################
# Project independent
####################################################################

cmake_minimum_required(VERSION 2.4)
if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 NEW)
      cmake_policy(SET CMP0005 OLD)
endif(COMMAND cmake_policy)
SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
    ADD_DEFINITIONS(-DCMAKE_INSTALL_PREFIX='"/usr"')
    SET(CMAKE_INSTALL_PREFIX /usr)
ENDIF()

IF(NOT DEFINED datadir)
    ADD_DEFINITIONS(-Ddatadir='"${CMAKE_INSTALL_PREFIX}/share"')
    SET(datadir ${CMAKE_INSTALL_PREFIX}/share)
ENDIF()

IF(NOT DEFINED docdir)
    ADD_DEFINITIONS(-Ddocdir='"${datadir}/doc"')
    SET(docdir ${datadir}/doc)
ENDIF()


###==================================================================
# Find parameters configuration
#
#  Note: CMake 2.4 does not support STRING(STRIP ..)

SET (SPEC_FILE_WARNING "This file is generated, please modified the .spec.in file instead!")
CONFIGURE_FILE(SPECS/libUnihan.spec.in SPECS/libUnihan.spec)

EXECUTE_PROCESS(COMMAND rpm -q --qf "%{release} " --specfile SPECS/${PROJECT_NAME}.spec 
    COMMAND head -n 1
    COMMAND sed -e "s/ .*//"
    OUTPUT_VARIABLE RPM_RELEASE)

#====================================================================
#  Developer can edit a DEVELOPER_SETTING file, 
#  which defines the developer specific information,
#  So they can upload to hosting service provider.
#
#  DEVELOPER_SETTING format
#  SSH_USER=<user_name>
#  SSH_ARGS=<additional args>
#  KOJI_CVS_PATH=<path for koji CVS>
#
#  KOJI_CVS_PATH is for Fedora/EPEL users, it has no effect on other systems.
#

IF(EXISTS  DEVELOPER_SETTING)
    EXECUTE_PROCESS(COMMAND  grep SSH_USER DEVELOPER_SETTING
	COMMAND sed -e "s/SSH_USER=//"
	COMMAND tr \\n \\t
	COMMAND sed  -e s/\\t//
	OUTPUT_VARIABLE SSH_USER
	)

    EXECUTE_PROCESS(COMMAND  grep SSH_ARGS DEVELOPER_SETTING
	COMMAND sed -e "s/SSH_ARGS=//"
	COMMAND tr \\n \\t
	COMMAND sed  -e s/\\t//
	OUTPUT_VARIABLE SSH_ARGS
	RESULT_VARIABLE NO_SSH_ARGS
	)
    IF(NOT ${NO_SSH_ARGS})
	IF ("${SSH_ARGS}" STREQUAL "")
	    SET(SFTP_SSH_ARGS "")
	ELSE ()
	    SET(SFTP_SSH_ARGS -F ${SSH_ARGS})
	    MESSAGE("SFTP_SSH_ARGS=${SFTP_SSH_ARGS}")
	ENDIF ()
    ELSE()
	SET(SFTP_SSH_ARGS "")
    ENDIF()

    EXECUTE_PROCESS(COMMAND  grep KOJI_CVS_PATH DEVELOPER_SETTING
	COMMAND sed -e "s/KOJI_CVS_PATH=//"
	COMMAND tr \\n \\t
	COMMAND sed  -e s/\\t//
	OUTPUT_VARIABLE KOJI_CVS_PATH
	RESULT_VARIABLE NO_KOJI_CVS_PATH
	)
    
    IF(NOT DEFINED ${KOJI_CVS_PATH})
	SET(KOJI_CVS_PATH "./")
    ELSEIF (${KOJI_CVS_PATH} STREQUAL "")
	SET(KOJI_CVS_PATH "./")
    ENDIF()

ENDIF(EXISTS  DEVELOPER_SETTING)

CONFIGURE_FILE(Doxyfile.in Doxyfile)
CONFIGURE_FILE(UploadPkg.batch.in UploadPkg.batch)

#====================================================================
# CPack configuration
#
SET(COMMON_IGNORE_FILES "/CMakeFiles/" "_CPack_Packages/" "/Testing/"
    ".cmake$"   ".directory$" "CMakeCache.txt"
    "/.svn/"  "/CVS/" "~$" ".swp$" ".log$" ".gz$"
    "/src/config.h$") 

SET(RPM_IGNORE_FILES "/SOURCES/" "/SRPMS/" "/RPMS/" "/BUILD/")

#==================================================================
# Make uninstall
#
CONFIGURE_FILE(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    )

#====================================================================
# RPM targets
#

SET (SRPM_FILE SRPMS/${PROJECT_NAME}-${PRJ_VER}-${RPM_RELEASE}.src.rpm)

ADD_CUSTOM_TARGET(srpm
    COMMAND make package_source
    COMMAND mkdir -p SOURCES
    COMMAND ln -sf ../${PROJECT_NAME}-${PRJ_VER}-Source.tar.gz SOURCES/${PROJECT_NAME}-${PRJ_VER}-Source.tar.gz
    COMMAND mkdir -p SRPMS
    COMMAND rpmbuild -bs SPECS/${PROJECT_NAME}.spec --rcfile rpmrc
    )

ADD_CUSTOM_TARGET(rpm
    COMMAND make package_source
    COMMAND mkdir -p SOURCES
    COMMAND ln -sf ../${PROJECT_NAME}-${PRJ_VER}-Source.tar.gz SOURCES/${PROJECT_NAME}-${PRJ_VER}-Source.tar.gz
    COMMAND mkdir -p SRPMS
    COMMAND mkdir -p RPMS/i386
    COMMAND mkdir -p RPMS/x86_64
    COMMAND mkdir -p BUILD
    COMMAND rpmbuild -ba SPECS/${PROJECT_NAME}.spec --rcfile rpmrc
    )

ADD_CUSTOM_TARGET(rpm_mock_i386 make srpm
    COMMAND mkdir -p RPMS/i386
    COMMAND mock -r  fedora-9-i386 --resultdir=RPMS/i386 ${SRPM_FILE}
    )

ADD_CUSTOM_TARGET(rpm_mock_x86_64 make srpm
    COMMAND mkdir -p RPMS/x86_64
    COMMAND mock -r  fedora-9-x86_64 --resultdir=RPMS/x86_64 ${SRPM_FILE}
    )

ADD_CUSTOM_TARGET(rpmlint find . 
    -name '${PROJECT_NAME}*-${PRJ_VER}-${RPM_RELEASE}.*.rpm' 
    -print -exec rpmlint '{}' '\\;'
    )




####################################################################
# Project specific
####################################################################

SET(DB_DIR ${datadir}/${DB_PRJ_NAME})
ADD_DEFINITIONS(-DPRJ_VER='"${PRJ_VER_FULL}"')
ADD_DEFINITIONS(-DUNIHAN_DEFAULT_DB='"${DB_DIR}/${DB_NAME}"')

#
# UNIHAN_DB_DEFAULT_PATH stores the system-wide setting DB files.
#
ADD_DEFINITIONS(-DUNIHAN_DB_DEFAULT_PATH='"${DB_DIR}"')

#
# DB files in UNIHAN_DB_SEARCH_PATH will be searched and set by unihan_search_db.
# Use path separator (';' for Windows, while ':' for Unix and others) to 
# separate multiple directories.
#
ADD_DEFINITIONS(-DUNIHAN_DB_SEARCH_PATH='"${DB_DIR}"')



#==================================================================
# Source code subdirectories
#
ADD_SUBDIRECTORY(src bin)
ADD_SUBDIRECTORY(test)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})

FIND_PACKAGE(PkgConfig)
PKG_CHECK_MODULES(GLIB2 glib-2.0)
PKG_CHECK_MODULES(SQLITE3 sqlite3)


ADD_CUSTOM_TARGET(${DB_NAME}
    COMMAND /bin/ln -sf ${DB_NAME}.${DB_VER}-${DB_RELEASE} ${DB_NAME}
    DEPENDS ${DB_NAME}.${DB_VER}-${DB_RELEASE})


SET(MAIN_DOCS AUTHORS README ChangeLog NEWS COPYING COPYING.LESSER )

INSTALL(FILES ${MAIN_DOCS} 
    DESTINATION "${docdir}/${PROJECT_NAME}-${PRJ_VER}")


#====================================================================
# CPack configuration
#
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "libUnihan")
SET(CPACK_PACKAGE_VENDOR "Red Hat, APAC, Inc.")
SET(CPACK_GENERATOR "TGZ")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
SET(CPACK_RESOURCE_FILE_LICENSE
    ${CMAKE_CURRENT_SOURCE_DIR}/COPYING)
SET(CPACK_RESOURCE_FILE_LICENSE
    ${CMAKE_CURRENT_SOURCE_DIR}/COPYING.LESSER)
SET(CPACK_PACKAGE_VERSION_MAJOR ${PRJ_VER_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${PRJ_VER_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${PRJ_VER_PATCH})
SET(PRJ_COMMON_IGNORE_FILES ${COMMON_IGNORE_FILES} ${RPM_IGNORE_FILES}
    "/doc/"  "/www/" ".vis$"
    ".db$" "test/check_phonetic$" "test/check_toneMark$"
    "test/unihan_field_validation$" "Doxyfile$" "UploadPkg.batch$"
    "libUnihan.spec$"
    "DEVELOPER_SETTING")

SET(CPACK_SOURCE_IGNORE_FILES ${PRJ_COMMON_IGNORE_FILES} "/bin/" ".db" "-db")
SET(CPACK_PACKAGE_IGNORE_FILES ${PRJ_COMMON_IGNORE_FILES} "/src/" "/test/"
    ".spec$" "Doxyfile.in$")
SET(CPACK_SOURCE_GENERATOR "TGZ")


INCLUDE(CPack)

ADD_CUSTOM_TARGET(pkg_remove_old find . 
    -name '${PROJECT_NAME}*.tar.gz' ! -name '${PROJECT_NAME}-${PRJ_VER}-*.tar.gz'
    -print -delete
    COMMAND find . 
    -name '${PROJECT_NAME}*.rpm' ! -name
    '${PROJECT_NAME}*-${PRJ_VER_FULL}.*.rpm'
    -print -delete
    COMMENT "Removing the old tar.gz and rpms.."
    )

#====================================================================
# Document generation
#
FIND_PACKAGE(Doxygen)
IF (EXISTS ${DOXYGEN})
  ADD_CUSTOM_TARGET(doxygen    
    COMMAND "${DOXYGEN}" "Doxyfile"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
  INSTALL(DIRECTORY doc/html
    DESTINATION "${docdir}/${PROJECT_NAME}-${PRJ_VER}"
  )
ENDIF (EXISTS ${DOXYGEN})


#====================================================================
# Koji (Fedora build system)
#

IF (DEFINED KOJI_CVS_PATH)
    SET(KOJI_SUBMISSION_CMD "")
    IF (NOT DEFINED ${KOJI_CVS_PATH})
	SET(KOJI_BUILD_CMD "")
    ELSE (NOT DEFINED ${KOJI_CVS_PATH})
	SET(KOJI_BUILD_CMD "cd ${KOJI_CVS_PATH}; ")
    ENDIF (NOT DEFINED ${KOJI_CVS_PATH})

    SET (KOJI_SUBMISSION_CMD
	"${KOJI_CVS_PATH}/${PROJECT_NAME}/common/cvs-import.sh -m \"${CVS_CHANGELOG}\" ${SRPM_FILE}" )

    SET (KOJI_BUILD_CMD
	"cd ${KOJI_CVS_PATH}/${PROJECT_NAME} && cd devel && make build && cd ..")

    FOREACH(DIST_TAG ${SUPPORTED_DIST_TAGS})
	SET (KOJI_SUBMISSION_CMD 
	    "${KOJI_SUBMISSION_CMD}\; ${KOJI_CVS_PATH}/${PROJECT_NAME}/common/cvs-import.sh -b ${DIST_TAG} -m \"${CVS_CHANGELOG}\" ${SRPM_FILE}")

	SET (KOJI_BUILD_CMD
	    "${KOJI_BUILD_CMD} && cd ${DIST_TAG} && make build && cd ..")
    ENDFOREACH(DIST_TAG ${SUPPORTED_DIST_TAGS})

    #MESSAGE(KOJI_SUBMISSION_CMD=${KOJI_SUBMISSION_CMD})
    ADD_CUSTOM_TARGET(koji_submit
	COMMAND eval ${KOJI_SUBMISSION_CMD}
	COMMAND cd ${KOJI_CVS_PATH}/${PROJECT_NAME} &&  cvs up
	DEPENDS DEVELOPER_SETTING  ${SRPM_FILE} ${KOJI_CVS_PATH}
	COMMENT "Submitting to Koji"
	VERBATIM
	)

    #MESSAGE("KOJI_BUILD_CMD=${KOJI_BUILD_CMD}")
    ADD_CUSTOM_TARGET(koji_build
	COMMAND eval "${KOJI_BUILD_CMD}"
	COMMENT "Building on Koji"
	VERBATIM
	)

    FOREACH(BODHI_TAG ${BODHI_DIST_TAGS})
	IF (DEFINED BODHI_NEW_CMD)
	    SET (BODHI_NEW_CMD "${BODHI_NEW_CMD} && ")
	ELSE ()
	    SET (BODHI_NEW_CMD "")
	ENDIF ()
	SET (BODHI_NEW_CMD 
	    "${BODHI_NEW_CMD} bodhi --new --type=bugfix --comment=\"${CVS_CHANGELOG}\" ${PROJECT_NAME}-${PRJ_VER_FULL}.${BODHI_TAG}")
    ENDFOREACH(BODHI_TAG ${BODHI_DIST_TAGS})


    #MESSAGE(BODHI_NEW_CMD=${BODHI_NEW_CMD})
    ADD_CUSTOM_TARGET(bodhi_new
	COMMAND eval "${BODHI_NEW_CMD}"
	COMMENT "Send the new package to bodhi"
	VERBATIM
	)
ENDIF(DEFINED KOJI_CVS_PATH)

###==================================================================
# Upload the package releases to hosting service provider (Source forge).
#

IF(DEFINED ${SSH_USER})
    SET(UPLOAD_SITE frs.sourceforge.net)
    SET(HOSTING_SERVICE_PROVIDER "Source forge")

    ADD_CUSTOM_TARGET(upload_pkg_release
	COMMAND  sftp -b UploadPkg.batch ${SFTP_SSH_ARGS} ${SSH_USER}@${UPLOAD_SITE}
	DEPENDS DEVELOPER_SETTING UploadPkg.batch.in
	COMMENT "Uploading the package releases to ${HOSTING_SERVICE_PROVIDER}...")

ENDIF(DEFINED ${SSH_USER})

#====================================================================
# Database related targets.
#
SET(DB_DOCS README-db ChangeLog-db)

ADD_CUSTOM_TARGET(package_db_doc
    COMMAND /bin/tar czvf "${DB_PRJ_NAME}-doc-${DB_VER}.tar.gz" ${DB_DOCS}
    )

ADD_CUSTOM_TARGET(package_db
    COMMAND mkdir -p "${DB_PRJ_NAME}-${DB_VER}-${DB_RELEASE}" 
    COMMAND cp "${DB_NAME}.${DB_VER}-${DB_RELEASE}" "${DB_PRJ_NAME}-${DB_VER}-${DB_RELEASE}" 
    COMMAND cp ${DB_DOCS}  "${DB_PRJ_NAME}-${DB_VER}-${DB_RELEASE}" 
    COMMAND /bin/tar czvf "${DB_PRJ_NAME}-${DB_VER}-${DB_RELEASE}.tar.gz" "${DB_PRJ_NAME}-${DB_VER}-${DB_RELEASE}"
    COMMAND rm -fr "${DB_PRJ_NAME}-${DB_VER}-${DB_RELEASE}"
    )

ADD_CUSTOM_TARGET(install_db
    COMMAND mkdir -p "${DB_DIR}" 
    COMMAND cp "${DB_NAME}.${DB_VER}-${DB_RELEASE}" ${DB_DIR}
    COMMAND ln -sf "${DB_NAME}.${DB_VER}-${DB_RELEASE}" ${DB_DIR}/${DB_NAME}
    COMMAND mkdir -p "${docdir}/${DB_PRJ_NAME}" 
    COMMAND cp README-db "${docdir}/${DB_PRJ_NAME}" 
    COMMAND cp ChangLog-db "${docdir}/${DB_PRJ_NAME}" 
    )

ADD_CUSTOM_TARGET(srpm_db
    COMMAND ln -sf ../${DB_PRJ_NAME}-doc-${DB_VER}.tar.gz SOURCES/${DB_PRJ_NAME}-doc-${DB_VER}.tar.gz
    COMMAND rpmbuild -bs SPECS/UnihanDb.spec --rcfile rpmrc
    )

ADD_CUSTOM_TARGET(rpm_db
    COMMAND ln -sf ../${DB_PRJ_NAME}-doc-${DB_VER}.tar.gz SOURCES/${DB_PRJ_NAME}-doc-${DB_VER}.tar.gz
    COMMAND mkdir -p RPMS/noarch
    COMMAND rpmbuild -ba SPECS/UnihanDb.spec --rcfile rpmrc
    )

ADD_DEPENDENCIES(srpm_db package_db_doc)
ADD_DEPENDENCIES(rpm_db package_db_doc)


###==================================================================
# Test Suites.
#
ENABLE_TESTING()
ADD_TEST(check_unihan_functions_0 
    ${PROJECT_BINARY_DIR}/test/check_unihan_functions 0)

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

