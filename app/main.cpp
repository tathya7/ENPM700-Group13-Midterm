/**
 * @file test.cpp
 * @author Tathya Bhatt (tathyab@umd.edu)
 * @brief Main app which does the actualizaiton
 * @version 1.0
 * @date 2024-10-28
 *
 * @copyright Copyright (c) 2024
 *
 */
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
    detection.detect(camera_device, false);
  }

  return 0;
}
