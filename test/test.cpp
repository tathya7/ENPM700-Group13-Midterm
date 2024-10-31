/**
 * @file test.cpp
 * @author Tathya Bhatt (tathyab@umd.edu)
 * @brief Unit tests implementation of different functionalities
 * @version 1.0
 * @date 2024-10-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <gtest/gtest.h>
#include <opencv2/core/hal/interface.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include "human_avoidance.hpp"
#include "human_detector.hpp"

/**
 * @brief Test fixture for HumanDetector class
 */

class HumanDetectorTest : public ::testing::Test {
 protected:
  /**
   * @brief Setting up the test fixture
   */
  void SetUp() override {
    detector = new HumanDetector();
    singleImg = "/home/tathyab/midterm_703/ex3.jpeg";

    img_size = cv::Size(640, 480);
    input_fr = cv::Mat::zeros(img_size, CV_8UC3);
    cv::rectangle(input_fr, cv::Rect(100, 100, 200, 300),
                  cv::Scalar(255, 255, 255), -1);
    classes = {"person", "car", "bicycle"};
  }
   /**
   * @brief Tear down the test fixture
   */
  void TearDown() override { delete detector; }

  // Pointer to HumanDetector object
  HumanDetector *detector;
  // Path to a single test image
  std::string singleImg;
  // Input frame to test
  cv::Mat input_fr;
  // Size of the input image
  cv::Size img_size;
  // Output images from the detector
  std::vector<cv::Mat> out_imgs;
  // List of object classes
  std::vector<std::string> classes;
};

/**
 * @brief Test case for validating frame size and processing
 * 
 * This test checks if the ImgProcessor method of HumanDetector
 * correctly processes a valid input frame.
 * 
 * @test
 * - Creates a zero-filled frame and a test frame from a file
 * - Processes the test frame using ImgProcessor
 * - Verifies the output frame dimensions (540x360)
 */
// TEST_F(HumanDetectorTest, ValidFrame) {
//   cv::Mat zero_frame = cv::Mat::zeros(480, 640, CV_8UC3);
//   cv::VideoCapture test_frame;

//   test_frame.open("/home/tathyab/midterm_703/ex1.jpg");

//   cv::Mat output_frame = detector->ImgProcessor(test_frame);

//   EXPECT_EQ(output_frame.cols, 540);
//   EXPECT_EQ(output_frame.rows, 360);
// }

/**
 * @brief Test fixture for HumanAvoidance class
 * 
 * This test suite contains unit tests for the HumanAvoidance class.
 */
class HumanAvoidanceTest : public ::testing::Test {
 protected:
  /**
   * @brief Set up the test fixture
   * 
   * Initializes a HumanAvoidance object and sets the box height.
   */
  void SetUp() override {
    avoider = new HumanAvoidance();
    box_height = 35;
  }

  void TearDown() override { delete avoider; }

  HumanAvoidance *avoider;
  int box_height;
};

/**
 * @brief Test case for measuring height calculation
 * 
 * This test verifies the calculate_distance method of HumanAvoidance
 * by checking if it correctly calculates the height based on the
 * bounding box height and a given angle.
 * 
 * @test
 * - Calculates the height using calculate_distance
 * - Rounds the result to the nearest integer
 * - Expects the calculated height to be 1
 */
TEST_F(HumanAvoidanceTest, MeasureHeight) {
  float calculated_height = avoider->calculate_distance(box_height, 40);
  calculated_height = std::round(calculated_height);
  EXPECT_EQ(calculated_height, 1);
}

/**
 * @brief Test case for coordinate transformation
 * 
 * This test checks the camera2robot method of HumanAvoidance
 * to ensure it correctly transforms camera coordinates to robot coordinates.
 * 
 * @test
 * - Loads a test image
 * - Creates a bounding box
 * - Calls camera2robot to transform coordinates
 * - Verifies the size of the returned coordinate vector
 * - Checks the values of the transformed coordinates
 */
// TEST_F(HumanAvoidanceTest, TestCoordinate) {
//   cv::Mat frame = cv::imread("/home/tathyab/midterm_703/ex3.jpeg");
//   cv::Rect box = cv::Rect(0, 10, 10, 0);
//   std::vector<float> coord = avoider->camera2robot(1, box, frame);

//   ASSERT_EQ(coord.size(), 3) << "Coordinate vector should have 3 elements";

//   EXPECT_EQ(coord[0], -16.0f);
//   EXPECT_EQ(coord[1], -10.0f);
//   EXPECT_EQ(coord[2], -1.0f);
// }
