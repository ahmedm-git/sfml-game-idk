# tests/CMakeLists.txt
enable_testing()
add_executable(test_suite test_main.cpp)
target_link_libraries(test_suite PRIVATE CMakeSFMLProjectLib)
add_test(NAME TestSuite COMMAND test_suite)
