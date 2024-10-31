/**
 * @file test.cpp
 * @brief Unit tests implementation for HumanAvoidance and HumanDetector functionalities.
 * @version 1.0
 * @date 2024-10-28
 *
 * @note Requires Google Test framework and OpenCV library.
 * 
 * @author Tathya Bhatt
 */

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "human_avoidance.hpp"
#include "human_detector.hpp"

/**
 * @brief Test fixture for the HumanAvoidance class.
 */
class HumanAvoidanceTest : public ::testing::Test {
protected:
    HumanAvoidance humanAvoidance; ///< Instance of HumanAvoidance used in tests
};

/**
 * @brief Tests the calculate_distance function with known values.
 */
TEST_F(HumanAvoidanceTest, CalculateDistanceTest) {
    int box_h = 365;  ///< Bounding box height in pixels
    int frame_h = 480; ///< Frame height in pixels

    // Expected distance calculation based on predefined formula
    double height_mm = (25 * box_h) / frame_h;  
    double z = (175 * 16) / height_mm;
    double expected_distance = z / 100;  ///< Expected distance in meters

    // Call calculate_distance and compare with expected value
    float distance = humanAvoidance.calculate_distance(box_h, frame_h);
    EXPECT_NEAR(distance, expected_distance, 0.01);  ///< Allow small margin of error
}

/**
 * @brief Tests the camera2robot function with a known bounding box and frame.
 */
TEST_F(HumanAvoidanceTest, CameraToRobotTest) {
    float z = 313; ///< Example distance in meters
    cv::Rect box(126, 23, 151, 316); ///< Bounding box coordinates
    cv::Mat frame = cv::imread("../../input/1.png");

    ASSERT_FALSE(frame.empty()) << "Failed to load test image.";
    EXPECT_NO_FATAL_FAILURE(humanAvoidance.camera2robot(z, box, frame));
}

/**
 * @brief Test fixture for the HumanDetector class.
 */
class HumanDetectorTest : public ::testing::Test {
protected:
    HumanDetector detector; ///< Instance of HumanDetector used in tests
};

/**
 * @brief Helper function to create a dummy YOLO output for testing.
 * @param rows Number of rows in YOLO output
 * @param cols Number of columns in YOLO output
 * @return cv::Mat Simulated YOLO output matrix
 */
cv::Mat createDummyYOLOOutput(int rows, int cols) {
    cv::Mat yolo_output(rows, cols, CV_32FC1);
    float* data = reinterpret_cast<float*>(yolo_output.data);
    for (int i = 0; i < rows; ++i) {
        data[0] = 0.5f;  
        data[1] = 0.5f;
        data[2] = 0.2f;
        data[3] = 0.4f;
        data[4] = 0.9f;
        data[5] = 0.8f;
        data += cols;
    }
    return yolo_output;
}

/**
 * @brief Tests setting and getting image path in HumanDetector.
 */
TEST_F(HumanDetectorTest, GetImgPathTest) {
    std::string img_path = "./ex2.jpeg";
    std::string result = detector.getImgPath(img_path);
    EXPECT_EQ(result, img_path);
}

/**
 * @brief Tests processing an empty frame in ImgProcessor of HumanDetector.
 */
TEST_F(HumanDetectorTest, ImgProcessorEmptyFrameTest) {
    cv::VideoCapture capture;
    EXPECT_NO_FATAL_FAILURE(detector.ImgProcessor(capture));
}

/**
 * @brief Tests drawing a bounding box with valid inputs in HumanDetector's drawBbox method.
 */
TEST_F(HumanDetectorTest, DrawBboxTest) {
    cv::Mat frame(480, 640, CV_8UC3); ///< Example frame size
    std::vector<std::string> classes = {"person"};
    EXPECT_NO_FATAL_FAILURE(detector.drawBbox(0, 0.9f, 100, 100, 200, 200, frame, classes, 1));
}

/**
 * @brief Tests the rmOverlap method of HumanDetector with dummy YOLO output.
 */
TEST_F(HumanDetectorTest, RmOverlapTest) {
    cv::Mat input_frame(480, 640, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Size img_size(640, 480);
    std::vector<cv::Mat> out_imgs;
    out_imgs.push_back(createDummyYOLOOutput(25200, 85));
    std::vector<std::string> classes = {"person"};
    
    cv::Mat result_frame = detector.rmOverlap(input_frame, img_size, out_imgs, classes);
    ASSERT_FALSE(result_frame.empty());
}

/**
 * @brief Tests the detect method with an image input.
 */
TEST_F(HumanDetectorTest, DetectImageTest) {
    std::string test_image_path = "../../input/1.png";
    // cv::Mat test_image = cv::imread(test_image_path);
    // ASSERT_FALSE(test_image.empty()) << "Test image not found at " << test_image_path;
    EXPECT_NO_FATAL_FAILURE(detector.detect(test_image_path, true));
}

/**
 * @brief Tests the detect method with a video input.
 */
TEST_F(HumanDetectorTest, DetectValidVideoTest) {
    std::string test_video_path = "../../input/test_video.mp4";
    // cv::VideoCapture cap(test_video_path);
    // ASSERT_TRUE(cap.isOpened()) << "Test video not found at " << test_video_path;
    EXPECT_NO_FATAL_FAILURE(detector.detect(test_video_path, true));
    // cap.release();
}
