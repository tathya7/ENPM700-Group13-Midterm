#include <iostream>
#include <ostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>

#include "human_avoidance.hpp"
#include "human_detector.hpp"

int main(int argc, char** argv) {
  std::string camera_device = argv[1];

  HumanDetector detection;

  while (1) {
    detection.detect(camera_device);
  }

  return 0;
}