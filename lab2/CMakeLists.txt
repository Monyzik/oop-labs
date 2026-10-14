add_library(lab2_lib src/string.cpp)
target_include_directories(lab2_lib PUBLIC include)

add_executable(lab2 src/main.cpp)
target_link_libraries(lab2 PRIVATE lab2_lib)

add_executable(lab2_testing test/string_test.cpp)
target_link_libraries(lab2_testing PRIVATE lab2_lib GTest::gtest_main)
enable_testing()
add_test(NAME Lab02Tests COMMAND lab2_testing)