FetchContent_Declare(
        googletest
        URL https://codeload.github.com/google/googletest/zip/refs/tags/v1.13.0
)

FetchContent_MakeAvailable(googletest)

target_link_libraries(${PROJECT_NAME}-TESTS
        gtest
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-TESTS)