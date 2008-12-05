# Location of library include files
INCLUDE_DIRECTORIES(${GLIB2_INCLUDE_DIRS} ${SQLITE3_INCLUDE_DIRS} ../src)

# Library location for the linker
LINK_DIRECTORIES(${GLIB2_LIBRARY_DIRS} ${SQLITE3_LIBRARY_DIRS} ../bin)

# Test programs
#ADD_EXECUTABLE(check_unihan_functions  check_unihan_functions.c)
#ADD_EXECUTABLE(check_phonetic  check_phonetic.c)
#ADD_EXECUTABLE(check_toneMark  check_toneMark.c)
#ADD_EXECUTABLE(unihan_field_validation  ../src/unihan_converter.c)
ADD_EXECUTABLE(check_str_functions check_str_functions.c)

#TARGET_LINK_LIBRARIES(check_unihan_functions Unihan)
#TARGET_LINK_LIBRARIES(check_phonetic Unihan)
#TARGET_LINK_LIBRARIES(check_toneMark Unihan)
#TARGET_LINK_LIBRARIES(unihan_field_validation Unihan)
TARGET_LINK_LIBRARIES(check_str_functions Unihan_supporting)


ADD_TEST(check_str_functions_regex_eval
    ${PROJECT_BINARY_DIR}/test/check_str_functions 0)

#ADD_TEST(check_unihan_functions_0 
#    ${PROJECT_BINARY_DIR}/test/check_unihan_functions 0)

#ADD_TEST(check_phonetic_pinyin_always 
#    ${PROJECT_BINARY_DIR}/test/check_phonetic 0) 
#ADD_TEST(check_phonetic_pinyin_original
#    ${PROJECT_BINARY_DIR}/test/check_phonetic 1) 
#ADD_TEST(check_phonetic_pinyin_unihan
#    ${PROJECT_BINARY_DIR}/test/check_phonetic 2) 
#ADD_TEST(check_phonetic_pinyin_trailing
#    ${PROJECT_BINARY_DIR}/test/check_phonetic 3) 
#ADD_TEST(check_phonetic_pinyin_inputMethod
#    ${PROJECT_BINARY_DIR}/test/check_phonetic 4) 
#ADD_TEST(check_phonetic_pinyin_none
#    ${PROJECT_BINARY_DIR}/test/check_phonetic 5) 
#ADD_TEST(check_phonetic_zhuyin_always
#    ${PROJECT_BINARY_DIR}/test/check_phonetic 6) 

#ADD_TEST(toneMark_pinyin_always_f 
#    ${PROJECT_BINARY_DIR}/test/check_toneMark 0 test) 
#ADD_TEST(toneMark_pinyin_always_t 
#    ${PROJECT_BINARY_DIR}/test/check_toneMark 1 test) 
#ADD_TEST(toneMark_pinyin_original_f 
#    ${PROJECT_BINARY_DIR}/test/check_toneMark 2 test) 
#ADD_TEST(toneMark_pinyin_original_t
#    ${PROJECT_BINARY_DIR}/test/check_toneMark 3 test) 
#ADD_TEST(toneMark_pinyin_unihan_f
#    ${PROJECT_BINARY_DIR}/test/check_toneMark 4 test) 
#ADD_TEST(toneMark_pinyin_unihan_t
#    ${PROJECT_BINARY_DIR}/test/check_toneMark 5 test) 
#ADD_TEST(toneMark_pinyin_trailing_f
#    ${PROJECT_BINARY_DIR}/test/check_toneMark 6 test) 
#ADD_TEST(toneMark_pinyin_trailing_t
#    ${PROJECT_BINARY_DIR}/test/check_toneMark 7 test) 
#ADD_TEST(toneMark_pinyin_inputMethod_f
#    ${PROJECT_BINARY_DIR}/test/check_toneMark 8 test) 
#ADD_TEST(toneMark_pinyin_inputMethod_t
#    ${PROJECT_BINARY_DIR}/test/check_toneMark 9 test) 
#ADD_TEST(toneMark_pinyin_none_f
#    ${PROJECT_BINARY_DIR}/test/check_toneMark 10 test) 
#ADD_TEST(toneMark_pinyin_none_t
#    ${PROJECT_BINARY_DIR}/test/check_toneMark 11 test) 
#ADD_TEST(toneMark_zhuyin_always
#    ${PROJECT_BINARY_DIR}/test/check_toneMark 12 test) 
#ADD_TEST(toneMark_zhuyin_original
#    ${PROJECT_BINARY_DIR}/test/check_toneMark 13 test) 
#ADD_TEST(toneMark_zhuyin_inputMethod
#    ${PROJECT_BINARY_DIR}/test/check_toneMark 14 test) 
#ADD_TEST(toneMark_zhuyin_numberical
#    ${PROJECT_BINARY_DIR}/test/check_toneMark 15 test) 






