add_library(lab1_lib src/array_ops.cpp src/io.cpp)
target_include_directories(lab1_lib PUBLIC include)

add_executable(lab1 src/main.cpp)
target_link_libraries(lab1 PRIVATE lab1_lib)

add_executable(lab1_testing test/array_test.cpp)
target_link_libraries(lab1_testing PRIVATE lab1_lib GTest::gtest_main)
enable_testing()
add_test(NAME Lab01Tests COMMAND lab1_testing)