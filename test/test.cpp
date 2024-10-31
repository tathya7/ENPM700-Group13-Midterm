/**
 * @file test.cpp
 * @brief Unit tests implementation for HumanAvoidance and HumanDetector functionalities.
 * @version 1.0
 * @date 2024-10-28
 * 
 * @author Tathya Bhatt
 * @copyright Copyright (c) 2024
 */

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "human_avoidance.hpp"
#include "human_detector.hpp"

// Test fixture for HumanAvoidance class
class HumanAvoidanceTest : public ::testing::Test {
protected:
    HumanAvoidance humanAvoidance;
};

// Test the calculate_distance function with known values
TEST_F(HumanAvoidanceTest, CalculateDistanceTest) {
    int box_h = 365;  // Example bounding box height in pixels
    int frame_h = 480; // Example frame height in pixels

    // Expected distance calculation
    double height_mm = (25 * box_h) / frame_h;  
    double z = (175 * 16) / height_mm;  
    double expected_distance = z / 100; // Convert mm to meters

    // Call calculate_distance and compare with expected value
    float distance = humanAvoidance.calculate_distance(box_h, frame_h);
    EXPECT_NEAR(distance, expected_distance, 0.01); // Allow small margin of error
}

// // Test the camera2robot function with known values
// TEST_F(HumanAvoidanceTest, CameraToRobotTest) {
//     float z = 313; // Example distance in meters
//     cv::Rect box(126, 23, 151, 316); // Example bounding box
//     cv::Mat frame = cv::imread("./ex1.jpg");

//     // Ensure that frame is loaded correctly
//     ASSERT_FALSE(frame.empty()) << "Failed to load test image.";

//     // Call camera2robot and capture result
//     std::vector<float> result = humanAvoidance.camera2robot(z, box, frame);

//     // Check if the result has correct size and values within expected range
//     ASSERT_EQ(result.size(), 3) << "Result vector should have 3 elements.";
// }

// Test fixture for HumanDetector class
class HumanDetectorTest : public ::testing::Test {
protected:
    HumanDetector detector;
};

// Test setting and getting image path in HumanDetector
TEST_F(HumanDetectorTest, GetImgPathTest) {
    std::string img_path = "./ex2.jpeg";
    
    // Call getImgPath and verify the returned path matches the input path
    std::string result = detector.getImgPath(img_path);
    
    EXPECT_EQ(result, img_path);
}

// Test processing an empty frame in ImgProcessor of HumanDetector
TEST_F(HumanDetectorTest, ImgProcessorEmptyFrameTest) {
    cv::VideoCapture capture;
    
    // Create an empty frame scenario by not opening any video source
    cv::Mat result_frame = detector.ImgProcessor(capture);
    
    EXPECT_NO_FATAL_FAILURE(detector.ImgProcessor(capture));
}

// Test drawing a bounding box with valid inputs in HumanDetector's drawBbox method
TEST_F(HumanDetectorTest, DrawBboxTest) {
    cv::Mat frame(480, 640, CV_8UC3); // Example frame size
    std::vector<std::string> classes = {"person"};
    
    // Ensure no fatal failure occurs when drawing a bounding box on the frame
    EXPECT_NO_FATAL_FAILURE(detector.drawBbox(0, 0.9f, 100, 100, 200, 200, frame, classes, 1));

    // Optionally check if pixels within the bounding box area have been modified (i.e., drawn)
}

TEST_F(HumanDetectorTest, rmOverlapTest) {

}

// ______________________________________________________________________________________________________________________________________________

    // Helper function to create a dummy YOLO output
    cv::Mat createDummyYOLOOutput(int rows, int cols) {
        cv::Mat yolo_output(rows, cols, CV_32FC1);
        float* data = reinterpret_cast<float*>(yolo_output.data);

        // Simulate some detections with random values
        for (int i = 0; i < rows; ++i) {
            data[0] = 0.5f;  // centerX (normalized)
            data[1] = 0.5f;  // centerY (normalized)
            data[2] = 0.2f;  // width (normalized)
            data[3] = 0.4f;  // height (normalized)
            data[4] = 0.9f;  // confidence
            data[5] = 0.8f;  // class score

            data += cols;
        }

        return yolo_output;
    }


// Test rmOverlap method of HumanDetector
TEST_F(HumanDetectorTest, RmOverlapTest) {
    // Create a dummy input frame (640x480)
    cv::Mat input_frame(480, 640, CV_8UC3, cv::Scalar(0, 0, 0));

    // Define image size
    cv::Size img_size(640, 480);

    // Create dummy YOLO output (simulating detections)
    std::vector<cv::Mat> out_imgs;
    out_imgs.push_back(createDummyYOLOOutput(25200, 85));  // YOLO output dimensions

    // Define classes
    std::vector<std::string> classes = {"person"};

    // Call rmOverlap function
    cv::Mat result_frame = detector.rmOverlap(input_frame, img_size, out_imgs, classes);

    // Verify that the result frame is not empty
    ASSERT_FALSE(result_frame.empty());

    // Optionally check that some pixels within the bounding box area have been modified
    // cv::Vec3b color = result_frame.at<cv::Vec3b>(240, 320);  // Sample pixel inside the bounding box
    // EXPECT_NE(color[0], 0);  // Expect that the pixel has been modified (not black anymore)

    // Check if bounding boxes are drawn by comparing pixel values within expected regions
}


// TEST_F(HumanDetectorTest, DetectImageTest) {
//     // Path to a test image (make sure this file exists)
//     std::string test_image_path = "./ex2.jpeg";

//     // Ensure that the file exists before running the test
//     cv::Mat test_image = cv::imread(test_image_path);
//     ASSERT_FALSE(test_image.empty()) << "Test image not found at " << test_image_path;

//     // Call detect method and ensure no fatal failures occur
//     EXPECT_NO_FATAL_FAILURE(detector.detect(test_image_path));
// }
// ___________________________________________________________

// TEST_F(HumanDetectorTest, DetectValidImageTest) {
//     // Path to a test image (make sure this file exists)
//     std::string test_image_path = "../../test_data/ex1.jpg";

//     // Ensure that the file exists before running the test
//     cv::Mat test_image = cv::imread(test_image_path);
//     ASSERT_FALSE(test_image.empty()) << "Test image not found at " << test_image_path;

//     // Call detect method and ensure no fatal failures occur
//     EXPECT_NO_FATAL_FAILURE(detector.detect(test_image_path));
// }

// TEST_F(HumanDetectorTest, DetectValidVideoTest) {
//     // Path to a test video (make sure this file exists)
//     std::string test_video_path = "./test_video.mp4";

//     // Ensure that the file exists before running the test
//     cv::VideoCapture cap(test_video_path);
//     ASSERT_TRUE(cap.isOpened()) << "Test video not found at " << test_video_path;

//     // Call detect method and ensure no fatal failures occur
//     EXPECT_NO_FATAL_FAILURE(detector.detect(test_video_path));

//     cap.release();  // Close the video capture after testing
// }