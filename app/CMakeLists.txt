# Any C++ source files needed to build this target (shell-app).
add_executable(shell-app
  # list of source cpp files:
  main.cpp
  human_detector.cpp
  human_avoidance.cpp
  )

add_library(detector_lib SHARED human_detector.cpp)
add_library(avoidance_lib SHARED human_avoidance.cpp)
# Any include directories needed to build this target.
# Note: we do not need to specify the include directories for the
# dependent libraries, they are automatically included.
target_include_directories(shell-app PUBLIC
  # list inclue directories:
  ${CMAKE_SOURCE_DIR}/include
)

target_include_directories(detector_lib PUBLIC
  # list inclue directories:
  ${OpenCV_INCLUDE_DIRS}
)

target_include_directories(avoidance_lib PUBLIC
  # list inclue directories:
  ${OpenCV_INCLUDE_DIRS}
)

find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(shell-app ${OpenCV_LIBS})
target_link_libraries(detector_lib ${OpenCV_LIBS})
target_link_libraries(avoidance_lib ${OpenCV_LIBS})
