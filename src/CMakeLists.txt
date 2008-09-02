# Location of library include files
INCLUDE_DIRECTORIES(${GLIB2_INCLUDE_DIRS} ${SQLITE3_INCLUDE_DIRS})

# Library location for the linker
LINK_DIRECTORIES(${GLIB2_LIBRARY_DIRS} ${SQLITE3_LIBRARY_DIRS})

INCLUDE (CheckFunctionExists)
CHECK_FUNCTION_EXISTS(g_string_chunk_clear HAVE_G_STRING_CHUNK_CLEAR)
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)


# Unihan_SQL_gen.c is already included in Unihan.c,
# no need to be in libUnihan_SRCS
SET(libUnihan_SRCS Unihan.c Unihan.h Unihan_enum.h 
    Unihan_Phonetic.c Unihan_Phonetic.h)
SET(supporting_SRCS allocate.c allocate.h
    sqlite_functions.c sqlite_functions.h
    str_functions.c str_functions.h
    verboseMsg.c verboseMsg.h)

ADD_LIBRARY(Unihan SHARED ${libUnihan_SRCS} ${supporting_SRCS})
SET_TARGET_PROPERTIES(Unihan PROPERTIES 
    VERSION "${PRJ_VER_MAJOR}.${PRJ_VER_MINOR}"
    SOVERSION "${PRJ_VER_MAJOR}")


# executable built from some source
ADD_EXECUTABLE(unihan_converter  unihan_converter.c)
ADD_EXECUTABLE(unihan_query	 unihan_query.c)

# Link the executable to the library.
TARGET_LINK_LIBRARIES(Unihan ${SQLITE3_LIBRARIES}
    ${GLIB2_LIBRARIES})
TARGET_LINK_LIBRARIES(unihan_converter Unihan)
TARGET_LINK_LIBRARIES(unihan_query Unihan)

# unihan_field_validation is a symbolic link to unihan_converter
ADD_CUSTOM_TARGET(unihan_field_validation ALL
    COMMAND /bin/ln -sf unihan_converter unihan_field_validation
    WORKING_DIRECTORY bin)

IF(NOT DEFINED LIB_INSTALL_DIR)
    SET(LIB_INSTALL_DIR lib)
    ADD_DEFINITIONS(-DLIB_INSTALL_DIR='"${LIB_INSTALL_DIR}"')
ENDIF(NOT DEFINED LIB_INSTALL_DIR)


INSTALL(TARGETS unihan_converter unihan_query Unihan
     RUNTIME DESTINATION bin
     LIBRARY DESTINATION ${LIB_INSTALL_DIR}
)

INSTALL(PROGRAMS ../bin/unihan_field_validation
    DESTINATION bin
)

INSTALL(FILES Unihan.h Unihan_enum.h str_functions.h
    DESTINATION include/${PROJECT_NAME}
)



