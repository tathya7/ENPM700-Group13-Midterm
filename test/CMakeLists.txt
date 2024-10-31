set(GTEST_SHUFFLE 1)

find_package( OpenCV REQUIRED )

add_executable(cpp-test
  
  main.cpp
  test.cpp
  ../app/human_detector.cpp
  ../app/human_avoidance.cpp
  )

target_include_directories(cpp-test PUBLIC
  # list of include directories:
  ../vendor/googletest/googletest/include
  ${CMAKE_SOURCE_DIR}/include
  ${OpenCV_INCLUDE_DIRS}
  )

# Any dependent libraires needed to build this target.
target_link_libraries(cpp-test PUBLIC
  # list of libraries:
  gtest
  ${OpenCV_LIBS}
  )

# Enable CMake’s test runner to discover the tests included in the
# binary, using the GoogleTest CMake module.
gtest_discover_tests(cpp-test)
