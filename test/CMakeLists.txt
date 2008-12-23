# Location of library include files
INCLUDE_DIRECTORIES(${GLIB2_INCLUDE_DIRS} ${SQLITE3_INCLUDE_DIRS} ../src .)

# Library location for the linker
LINK_DIRECTORIES(${GLIB2_LIBRARY_DIRS} ${SQLITE3_LIBRARY_DIRS} ../bin)


# Source
SET(check_functions_SRCS 
    check_functions.c check_functions.h
)


# Test programs
#ADD_EXECUTABLE(check_unihan_functions  check_unihan_functions.c)
ADD_EXECUTABLE(check_phonetic  check_phonetic.c 
    ${check_functions_SRCS})
ADD_EXECUTABLE(check_toneMark  check_toneMark.c )
#ADD_EXECUTABLE(unihan_field_validation  ../src/unihan_converter.c)
ADD_EXECUTABLE(check_str_functions check_str_functions.c
    ${check_functions_SRCS})

#TARGET_LINK_LIBRARIES(check_unihan_functions Unihan)
TARGET_LINK_LIBRARIES(check_phonetic Unihan)
TARGET_LINK_LIBRARIES(check_toneMark Unihan)
#TARGET_LINK_LIBRARIES(unihan_field_validation Unihan)
TARGET_LINK_LIBRARIES(check_str_functions Unihan_supporting)








