add_test(
	NAME
		AppTest
	COMMAND
		"${CMAKE_CTEST_COMMAND}"
			--build-and-test "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}"
			--build-generator "${CMAKE_GENERATOR}"
			--build-target test_app
			--test-command "$<TARGET_FILE:test_app>"
)

add_test(
	NAME
		BoardTest
	COMMAND
		"${CMAKE_CTEST_COMMAND}"
			--build-and-test "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}"
			--build-generator "${CMAKE_GENERATOR}"
			--build-target test_board
			--test-command "$<TARGET_FILE:test_board>"
)

add_test(NAME GameTest COMMAND "${CMAKE_COMMAND}" -E echo_append "q" | "$<TARGET_FILE:game>")

