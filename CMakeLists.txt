cmake_minimum_required(VERSION 2.4)
if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 NEW)
      cmake_policy(SET CMP0005 OLD)
endif(COMMAND cmake_policy)

#Project name
PROJECT(libUnihan)
SET(CMAKE_C_FLAGS "-Wall")
SET(PRJ_VER_MAJOR "0")
SET(PRJ_VER_MINOR "5")
SET(PRJ_VER_PATCH "2")
SET(PRJ_VER ${PRJ_VER_MAJOR}.${PRJ_VER_MINOR}.${PRJ_VER_PATCH})
SET(DB_VER "5.1.0")
SET(DB_PATCH_LEVEL "7")
SET(DB_PRJ_NAME  "UnihanDb")
SET(DB_NAME "Unihan.db")

IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
    ADD_DEFINITIONS(-DCMAKE_INSTALL_PREFIX='"/usr"')
    SET(CMAKE_INSTALL_PREFIX /usr)
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)

IF(NOT DEFINED datadir)
    ADD_DEFINITIONS(-Ddatadir='"${CMAKE_INSTALL_PREFIX}/share"')
    SET(datadir ${CMAKE_INSTALL_PREFIX}/share)
ENDIF(NOT DEFINED datadir)

IF(NOT DEFINED docdir)
    ADD_DEFINITIONS(-Ddocdir='"${datadir}/doc"')
    SET(docdir ${datadir}/doc)
ENDIF(NOT DEFINED docdir)


SET(DB_DIR ${datadir}/${DB_PRJ_NAME})
ADD_DEFINITIONS(-DUNIHAN_DEFAULT_DB='"${DB_DIR}/${DB_NAME}"')


# Source code subdirectories
ADD_SUBDIRECTORY(src bin)
ADD_SUBDIRECTORY(test)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})

FIND_PACKAGE(PkgConfig)
PKG_CHECK_MODULES(GLIB2 glib-2.0)
PKG_CHECK_MODULES(SQLITE3 sqlite3)

ADD_CUSTOM_TARGET(${DB_NAME}
    COMMAND /bin/ln -sf ${DB_NAME}.${DB_VER}-${DB_PATCH_LEVEL} ${DB_NAME}
    DEPENDS ${DB_NAME}.${DB_VER}-${DB_PATCH_LEVEL})

SET(MAIN_DOCS AUTHORS README ChangeLog NEWS COPYING COPYING.LESSER )

INSTALL(FILES ${MAIN_DOCS} 
    DESTINATION "${docdir}/${PROJECT_NAME}-${PRJ_VER}")

#ADD_CUSTOM_COMMAND(OUTPUT ${DB_NAME}
#    COMMAND /bin/ln -sf ${DB_NAME}.${DB_VER} ${DB_NAME}
#    DEPENDS ${DB_NAME}.${DB_VER})
# COMMAND(ln -s  ${DB_NAME}.${DB_VER} ${DB_NAME})

###==================================================================
# RPM targets
#

ADD_CUSTOM_TARGET(srpm
    COMMAND make package_source
    COMMAND mkdir -p SOURCES
    COMMAND ln -sf ../${PROJECT_NAME}-${PRJ_VER}-Source.tar.gz SOURCES/${PROJECT_NAME}-${PRJ_VER}-Source.tar.gz
    COMMAND mkdir -p SRPMS
    COMMAND rpmbuild -bs SPECS/libUnihan.spec --rcfile rpmrc
)

ADD_CUSTOM_TARGET(rpm
    COMMAND make package_source
    COMMAND mkdir -p SOURCES
    COMMAND ln -sf ../${PROJECT_NAME}-${PRJ_VER}-Source.tar.gz SOURCES/${PROJECT_NAME}-${PRJ_VER}-Source.tar.gz
    COMMAND mkdir -p SRPMS
    COMMAND mkdir -p RPMS/i386
    COMMAND mkdir -p RPMS/x86_64
    COMMAND mkdir -p BUILD
    COMMAND rpmbuild -ba SPECS/libUnihan.spec --rcfile rpmrc
)
###==================================================================
# Database related targets.
#
SET(DB_DOCS README-db ChangeLog-db)

ADD_CUSTOM_TARGET(package_db_doc
    COMMAND /bin/tar czvf "${DB_PRJ_NAME}-doc-${DB_VER}.tar.gz" ${DB_DOCS}
)

ADD_CUSTOM_TARGET(package_db
    COMMAND mkdir -p "${DB_PRJ_NAME}-${DB_VER}-${DB_PATCH_LEVEL}" 
    COMMAND cp "${DB_NAME}.${DB_VER}-${DB_PATCH_LEVEL}" "${DB_PRJ_NAME}-${DB_VER}-${DB_PATCH_LEVEL}" 
    COMMAND cp ${DB_DOCS}  "${DB_PRJ_NAME}-${DB_VER}-${DB_PATCH_LEVEL}" 
    COMMAND /bin/tar czvf "${DB_PRJ_NAME}-${DB_VER}-${DB_PATCH_LEVEL}.tar.gz" "${DB_PRJ_NAME}-${DB_VER}-${DB_PATCH_LEVEL}"
    COMMAND rm -fr "${DB_PRJ_NAME}-${DB_VER}-${DB_PATCH_LEVEL}"
)

ADD_CUSTOM_TARGET(install_db
    COMMAND mkdir -p "${DB_DIR}" 
    COMMAND cp "${DB_NAME}.${DB_VER}-${DB_PATCH_LEVEL}" ${DB_DIR}
    COMMAND ln -sf "${DB_NAME}.${DB_VER}-${DB_PATCH_LEVEL}" ${DB_DIR}/${DB_NAME}
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
SET(COMMON_IGNORE_FILES "/CMakeFiles/" "_CPack_Packages/" "/Testing/"
    ".cmake$"   ".directory$" "CMakeCache.txt"
    "/.svn/"  "/CVS/" "~$" ".swp$" ".log$" ".gz$"
    "/src/config.h$")

SET(RPM_IGNORE_FILES "/SOURCES/" "/SRPMS/" "/RPMS/" "/BUILD/")

SET(PRJ_COMMON_IGNORE_FILES ${COMMON_IGNORE_FILES} ${RPM_IGNORE_FILES}
    "/doc/"  "/www/" ".vis$"
    ".db$" "test/check_phonetic$" "test/check_toneMark$"
    "test/unihan_field_validation$" "Doxyfile$")

SET(CPACK_SOURCE_IGNORE_FILES ${PRJ_COMMON_IGNORE_FILES} "/bin/" ".db" "-db")
SET(CPACK_PACKAGE_IGNORE_FILES ${PRJ_COMMON_IGNORE_FILES} "/src/" "/test/"
    ".spec$" "Doxyfile.in$")
SET(CPACK_SOURCE_GENERATOR "TGZ")


INCLUDE(CPack)

### Document generation
FIND_PACKAGE(Doxygen)
IF (EXISTS ${DOXYGEN})
  ADD_CUSTOM_TARGET(Doxyfile
      COMMAND sed "s/_PRJ_VER/${PRJ_VER}/" Doxyfile.in > Doxyfile
  )
  ADD_CUSTOM_TARGET(doxygen    
    COMMAND "${DOXYGEN}" "Doxyfile"
    DEPENDS Doxyfile
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
  INSTALL(DIRECTORY doc/html
    DESTINATION "${docdir}/${PROJECT_NAME}-${PRJ_VER}"
  )
ENDIF (EXISTS ${DOXYGEN})

### For Uninstall
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")


### For testing
ENABLE_TESTING()
ADD_TEST(check_functions_0 
    ${PROJECT_BINARY_DIR}/test/check_functions 0)

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

