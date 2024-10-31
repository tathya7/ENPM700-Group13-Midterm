![CICD Workflow status](https://github.com/mun0404/ENPM700-Group13-Midterm/actions/workflows/run-unit-test-and-upload-codecov.yml/badge.svg)

[![codecov](https://codecov.io/gh/mun0404/ENPM700-Group13-Midterm/graph/badge.svg?token=2W1XS59EG6)](https://codecov.io/gh/mun0404/ENPM700-Group13-Midterm)

# Human Detection and Localization

## Authors 
### Mohammed Munawwar (120340246) | Tathya Bhatt (120340246)

## Introduction
In this project, we implement real-time human detection, tracking, and avoidance using the YOLOv5s model. We use YOLO architecture to detect and track humans in video streams, as YOLO offers an excellent balance between speed and accuracy for real-time detection and tracking.

We divided the project into three parts: human detection, human avoidance, and robot controller. First, we use a monocular camera to detect and track humans in the frame. Then, we take the coordinates of the human position with respect to the camera so that the mobile robot can avoid collision with humans while operating in the real world.

## Table of Contents
- [Methodology](#methodology)
- [Development Process](#development-process)
- [System Requirements](#system-requirements)
- [Installation](#installation)
- [Standard Build and Execute via Command-line](#standard-build-and-execute-via-command-line)
- [License](#license)

## Methodology

Our human detection and tracking pipeline is as follows:

1. **Frame Capture**: Read frames from the video camera input.
2. **Preprocess the Frame**: Prepare the frame before applying the model to detect humans, ensuring optimal results.
3. **Human Detection**: Apply the YOLOv5s model to detect humans in each frame and draw bounding boxes around each person.
4. **Non-Maximum Suppression (NMS)**: Use NMS threshold to avoid overlapping boxes and prevent detecting the same person multiple times.
5. **Confidence Scores**: Add a confidence score label on each predicted bounding box to indicate model certainty for each detection.
6. **Coordinate Transformation**: Convert 2D pixel coordinates of bounding box centroids to 3D real-world coordinates using inverse perspective transformation.
7. **Robot Frame Conversion**: Convert 3D coordinates into the robot’s frame of reference using sensor height for accurate spatial tracking.

## Development Process

For this project, we followed the ***Agile Iterative Process (AIP)***, ensuring flexibility and continuous improvement throughout development. The [product backlog](https://docs.google.com/spreadsheets/d/1zITtZFIbhi-VyhSFAzy4M6afBLeduHdxMXDktULzxks/edit?gid=0#gid=0), [iteration backlogs](https://docs.google.com/spreadsheets/d/1zITtZFIbhi-VyhSFAzy4M6afBLeduHdxMXDktULzxks/edit?gid=1503816755#gid=1503816755), and [work logs](https://docs.google.com/spreadsheets/d/1zITtZFIbhi-VyhSFAzy4M6afBLeduHdxMXDktULzxks/edit?gid=1860513107#gid=1860513107) are maintained in a Google Sheet for transparency and efficient project management.

## System Requirements

To run this project, you will need:

- OpenCV (for image processing).
- YOLOv5s ONNX model for human detection.
- C++11 or later (for compiling the code).

## Installation
### OpenCV Installation
```bash
# Create a directory for OpenCV and navigate to it
mkdir opencv_install && cd opencv_install

# Clone the OpenCV repository
git clone https://github.com/opencv/opencv.git

# Checkout the desired version (e.g., 4.x)
cd opencv
git checkout 4.x

# Create a build directory and navigate to it
mkdir build && cd build

# Run cmake with C++17 standard
cmake -D CMAKE_CXX_STANDARD=17 ..

# Compile the code using available processors
make -j$(nproc)

# Install OpenCV
sudo make install

# Verify the installation by checking the OpenCV4 folder path
ls /usr/local/include/
```

## Standard Build and Execute via Command-line

```bash
# Download the code:
  git clone https://github.com/mun0404/ENPM700-Group13-Midterm.git

  cd ENPM700-Group13-Midterm/
  
# Configure the project:
  cmake -S ./ -B build/

# Compile and build the project:
  cmake --build build/

# Running the camera to track humans at real-time:
  ./build/app/shell-app /dev/video0

# Run the program to test it on an image:
  ./build/app/shell-app <path to the image>

# Run the program to test it on a video:
  ./build/app/shell-app <path to the video>

# Run tests:
  ctest --test-dir build/

# Build documentation:
  cmake --build build/ --target docs
  
# Clean build files:
  cmake --build build/ --target clean
  
# Clean everything and start over:
  rm -rf build/
```

## License

This project is licensed under the MIT License.

---

### Additional Resources

1. **Phase 0 Video**: [Link Placeholder]
2. **GitHub CI Badge**: [Link Placeholder]
3. **CodeCov Badge**: [Link Placeholder]
