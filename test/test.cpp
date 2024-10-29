// #include <gtest/gtest.h>
// // #include <gmock/gmock.h>
// #include "../include/detector.hpp"
// #include <opencv2/core.hpp>
// #include <opencv2/imgproc.hpp>
// #include <opencv2/dnn.hpp>

// // Test fixture for StreamData
// // class StreamDataTest : public ::testing::Test {
// // protected:
// //     StreamData streamData;
// // };

// // Test for setImgPath
// // TEST_F(StreamDataTest, SetImagePath) {
// //     std::string testPath = "/home/tathyab/ENPM700-Group13-Midterm/test1.jpeg";
// //     streamData.setImgPath(testPath);
// //     ASSERT_EQ(testPath, streamData.image_path) << "The image path should be set correctly.";
// // }

// // Test for getImage with a valid path
// // TEST_F(StreamDataTest, GetImage_ValidPath) {
// //     std::string testImage = "test_image.jpg";
// //     cv::CommandLineParser parser(0, nullptr, "{image|test_image.jpg|}");
// //     std::string result = streamData.getImage(parser);
// //     ASSERT_EQ(result, testImage) << "The returned image path should match the input.";
// // }

// // Test for getImage with an invalid path
// // TEST_F(StreamDataTest, GetImage_InvalidPath) {
// //     cv::CommandLineParser parser(0, nullptr, "{}");
// //     std::string result = streamData.getImage(parser);
// //     ASSERT_EQ(result, "Invalid Input") << "The returned result should indicate an invalid input.";
// // }

// // Test for ImgProcessor in read mode
// // TEST_F(StreamDataTest, ImgProcessor_ReadMode) {
// //     std::string testPath = "test_image.jpg";
// //     streamData.setImgPath(testPath);

// //     cv::Mat mockImage = cv::Mat::zeros(640, 480, CV_8UC3);
// //     cv::imwrite(testPath, mockImage);

// //     cv::Mat result = streamData.ImgProcessor('r');
// //     ASSERT_FALSE(result.empty()) << "The image should be successfully read.";

// //     std::remove(testPath.c_str());
// // }

// // Test fixture for Detector class
// // class DetectorTest : public ::testing::Test {
// // protected:
// //     Detector detector;
// //     cv::Mat frame;
// //     std::vector<std::string> classes;

// //     void SetUp() override {
// //         frame = cv::Mat::zeros(640, 640, CV_8UC3);
// //         classes = {"person", "bicycle", "car"};
// //     }
// // };

// // Test for drawBbox with valid input
// // TEST_F(DetectorTest, DrawBbox_ValidInput) {
// //     int classid = 0; // person
// //     float confidence = 0.8;
// //     int left = 50, top = 50, right = 150, bottom = 150;
// //     int person_id = 1;

// //     detector.drawBbox(classid, confidence, left, top, right, bottom, frame, classes, person_id);

// //     cv::Vec3b color = frame.at<cv::Vec3b>(75, 75);
// //     ASSERT_EQ(color[0], 50) << "The bounding box color should be detected.";
// // }

// // Test rmOverlap method for removing overlaps
// // TEST_F(DetectorTest, RmOverlap_RemovesOverlapsCorrectly) {
// //     cv::Mat input_img = cv::Mat::ones(640, 640, CV_8UC3);
// //     std::vector<cv::Mat> out_imgs;
// //     std::vector<std::string> classes = {"person", "car"};

// //     cv::Mat detection = cv::Mat::zeros(25200, 85, CV_32F);
// //     detection.at<float>(0, 4) = 0.5;
// //     detection.at<float>(0, 0) = 0.5;
// //     detection.at<float>(0, 1) = 0.5;
// //     detection.at<float>(0, 2) = 0.1;
// //     detection.at<float>(0, 3) = 0.1;
// //     out_imgs.push_back(detection);

// //     cv::Mat result = detector.rmOverlap(input_img, out_imgs, classes);
// //     ASSERT_FALSE(result.empty()) << "The resulting image should not be empty after processing.";
// // }

// // Test detect method
// // TEST_F(DetectorTest, DetectMethod) {
// //     cv::CommandLineParser parser(0, nullptr, "{image|test_image.jpg|}");

// //     class MockStreamData : public StreamData {
// //     public:
// //         std::string getImage(cv::CommandLineParser parser) override {
// //             return "test_image.jpg";
// //         }

// //         cv::Mat ImgProcessor(char mode) override {
// //             return cv::Mat::ones(640, 640, CV_8UC3);
// //         }
// //     };

// //     MockStreamData mockInput;
// //     detector.detect(parser);

// //     // Verification for integration tests can be added here
// // }

// // Main function to run all tests
// // int main(int argc, char** argv) {
// //     ::testing::InitGoogleTest(&argc, argv);
// //     return RUN_ALL_TESTS();
// // }
