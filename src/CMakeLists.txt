# Location of library include files
INCLUDE_DIRECTORIES(${GLIB2_INCLUDE_DIRS} ${SQLITE3_INCLUDE_DIRS})

# Library location for the linker
LINK_DIRECTORIES(${GLIB2_LIBRARY_DIRS} ${SQLITE3_LIBRARY_DIRS})

#==================================================================
# Function check
#

INCLUDE (CheckLibraryExists)
CHECK_LIBRARY_EXISTS(glib-2.0 g_string_chunk_clear "" HAVE_G_STRING_CHUNK_CLEAR)
CHECK_LIBRARY_EXISTS(sqlite3 sqlite3_open_v2 "" HAVE_SQLITE3_OPEN_V2)
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

# Unihan_SQL_gen.c is already included in Unihan.c,
# no need to be in libUnihan_SRCS

#SET(libUnihan_SRCS Unihan.c Unihan.h Unihan_enum.h
#    Unihan_phonetic.c Unihan_phonetic.h
#)

SET(libUnihan_SRCS
    Unihan_phonetic.c Unihan_phonetic.h Unihan.h
)

SET(libUnihan_builder_SRCS
    Unihan_builtin.c Unihan_builtin.h
)

SET(supporting_SRCS allocate.c allocate.h
    collection.c collection.h
    file_functions.c file_functions.h
    sqlite_functions.c sqlite_functions.h
    str_functions.c str_functions.h
    verboseMsg.c verboseMsg.h)

SET(DOCUMENTED_HEADERS Unihan.h Unihan_enum.h Unihan_phonetic.h Unihan_types.h
    allocate.h collection.h file_functions.h sqlite_functions.h str_functions.h verboseMsg.h)


ADD_LIBRARY(Unihan_supporting SHARED ${supporting_SRCS})
ADD_LIBRARY(Unihan SHARED ${libUnihan_SRCS} )
ADD_LIBRARY(Unihan_builder SHARED ${libUnihan_builder_SRCS} )
SET_TARGET_PROPERTIES(Unihan Unihan_supporting Unihan_builder PROPERTIES
    VERSION "${SO_VER_MAJOR}.${SO_VER_MINOR}"
    SOVERSION "${SO_VER_MAJOR}")


# executable built from some source
ADD_EXECUTABLE(unihan_converter  unihan_converter.c )
#ADD_EXECUTABLE(unihan_query	 unihan_query.c)
#ADD_EXECUTABLE(unihan_rebuild_cache unihan_rebuild_cache.c)


# Link the executable to the library.
TARGET_LINK_LIBRARIES(Unihan_supporting ${SQLITE3_LIBRARIES} ${GLIB2_LIBRARIES})
TARGET_LINK_LIBRARIES(Unihan ${SQLITE3_LIBRARIES} ${GLIB2_LIBRARIES}
    Unihan_supporting)
TARGET_LINK_LIBRARIES(Unihan_builder ${SQLITE3_LIBRARIES} ${GLIB2_LIBRARIES}
    Unihan_supporting Unihan)
TARGET_LINK_LIBRARIES(unihan_converter Unihan_supporting Unihan Unihan_builder)
#TARGET_LINK_LIBRARIES(unihan_query Unihan_supporting Unihan)
#TARGET_LINK_LIBRARIES(unihan_rebuild_cache Unihan_supporting Unihan)

IF(NOT DEFINED LIB_INSTALL_DIR)
    IF( $ENV{MACHTYPE} MATCHES "64")
	SET(LIB_INSTALL_DIR lib64)
	ADD_DEFINITIONS(-DLIB_INSTALL_DIR='"${LIB_INSTALL_DIR}"')
    ELSE( $ENV{MACHTYPE} MATCHES "64")
	SET(LIB_INSTALL_DIR lib)
	ADD_DEFINITIONS(-DLIB_INSTALL_DIR='"${LIB_INSTALL_DIR}"')
    ENDIF( $ENV{MACHTYPE} MATCHES "64")
ENDIF(NOT DEFINED LIB_INSTALL_DIR)


#INSTALL(TARGETS unihan_converter unihan_query unihan_rebuild_cache Unihan Unihan_supporting
INSTALL(TARGETS Unihan_supporting
     RUNTIME DESTINATION bin
     LIBRARY DESTINATION ${LIB_INSTALL_DIR}
)

INSTALL(FILES ${DOCUMENTED_HEADERS}
    DESTINATION include/${PROJECT_NAME}
)



