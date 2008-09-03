# Location of library include files
INCLUDE_DIRECTORIES(${GLIB2_INCLUDE_DIRS} ${SQLITE3_INCLUDE_DIRS} ../src)

# Library location for the linker
LINK_DIRECTORIES(${GLIB2_LIBRARY_DIRS} ${SQLITE3_LIBRARY_DIRS} ../lib)


# executable built from some source
ADD_EXECUTABLE(check_phonetic  check_phonetic.c)
TARGET_LINK_LIBRARIES(check_phonetic Unihan)





