# Location of library include files
INCLUDE_DIRECTORIES(${GLIB2_INCLUDE_DIRS} ${SQLITE3_INCLUDE_DIRS} ../src)

# Library location for the linker
LINK_DIRECTORIES(${GLIB2_LIBRARY_DIRS} ${SQLITE3_LIBRARY_DIRS} ../lib)

# Test programs
ADD_EXECUTABLE(check_functions  check_functions.c)
ADD_EXECUTABLE(check_phonetic  check_phonetic.c)
ADD_EXECUTABLE(check_toneMark  check_toneMark.c)
ADD_EXECUTABLE(unihan_field_validation  ../src/unihan_converter.c)
TARGET_LINK_LIBRARIES(check_functions Unihan)
TARGET_LINK_LIBRARIES(check_phonetic Unihan)
TARGET_LINK_LIBRARIES(check_toneMark Unihan)
TARGET_LINK_LIBRARIES(unihan_field_validation Unihan)





