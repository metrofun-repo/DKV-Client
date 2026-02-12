file(GLOB TEST_SOURCES "unit/*.cpp")

add_executable(dkv_client_tests ${TEST_SOURCES})

target_link_libraries(dkv_client_tests
	PRIVATE
		GTest::gtest
		GTest::gtest_main
		dkv_client_core
)
set_property(TARGET dkv_client_tests PROPERTY FOLDER "Tests")
get_target_property(GTEST_INCLUDE_DIRS GTest::gtest INTERFACE_INCLUDE_DIRECTORIES)

target_include_directories(dkv_client_tests
	PRIVATE 
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/src
	${GTEST_INCLUDE_DIRS}
)

#include(GoogleTest) 
#gtest_discover_tests(dkv_client_tests)