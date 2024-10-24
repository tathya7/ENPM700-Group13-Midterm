# Any C++ source files needed to build this target (shell-app).
add_executable(shell-app
  # list of source cpp files:
  main.cpp
  detector.cpp
  stream_data.cpp
  )

# Any include directories needed to build this target.
# Note: we do not need to specify the include directories for the
# dependent libraries, they are automatically included.
target_include_directories(shell-app PUBLIC
  # list inclue directories:
  ${CMAKE_SOURCE_DIR}/include
)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(shell-app ${OpenCV_LIBS})
# Any dependent libraires needed to build this target.
# target_link_libraries(shell-app PUBLIC -static
#   # list of libraries
#   myLib1
#   myLib2
#   )

  
