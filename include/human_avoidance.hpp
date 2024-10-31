/**
 * @file human_avoidance.hpp
 * @author  Mohammed Munawwar (mmunawwa@umd.edu)
 * @brief Stub implementation for avoidance warning functionality
 * @version 1.0
 * @date 2024-10-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include <array>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

/**
 * @brief A class for human avoidance functionality
 *
 * The HumanAvoidance class provides functionality for detecting humans
 * and calculating their positions relative to a robot's coordinate system.
 * Further, if a human is detected around a certain radius, the red marker
 * is shown giving the warning in the output.
 */
class HumanAvoidance {
 private:
  const unsigned int averageHeight = 175;  // Average human height in cm

 public:
  int frame_id;

  /**
   * @brief Default constructor for the class
   */
  HumanAvoidance();

  /**
   * @brief Calculates the distance of a detected human from the camera
   *
   * @param box_h Height of the bounding box around the detected human
   * @param frame_h Input frame height
   * @return float The calculated distance in meters
   */

  float calculate_distance(int box_h, int frame_h);

  /**
   * @brief Transforms human coordinates from camera to robot coordinate system
   *
   * @param z Distance of the human from the camera
   * @param box Bounding box of the detected human in the camera frame
   * @param frame The current video frame
   * @return std::vector<float> A vector containing the x, y, z coordinates in
   * the robot's frame
   */

  std::vector<float> camera2robot(float z, cv::Rect box, cv::Mat frame);

  ~HumanAvoidance();
};