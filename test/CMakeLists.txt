include(AddGoogleTest)

add_executable(unit_test "tube_test.cpp")

target_link_libraries(unit_test PRIVATE tube GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_test)
