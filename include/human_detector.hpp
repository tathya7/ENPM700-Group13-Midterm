#pragma once
#include <vector>
#include <opencv2/opencv.hpp>

/**
 * @brief Create a HumanDetection class to implement human detection module for the mobile robot. This will help the robot 
 * in maneuvering safely in an environment with constant human presence, ensuring safety of both the robot and the humans around it. 
 */
class HumanDetection {
 private:
  /**
   * @brief Representing current frame from the monocular camera
   */
  cv::Mat current_frame;

  /**
   * @brief This represents the detected human bounding boxes (x, y, width, height)
   */
  std::vector<cv::Rect> human_bounding_boxes;

  /**
   * @brief Confidence threshold for human detection
   */
  double detection_confidence_threshold;

  /**
   * @brief Function to preprocess the camera frame for detecting humans
   */
  void preprocess_frame();

  /**
   * @brief Function to detect humans in the current frame
   */
  void detect_humans();

 public:
  /**
   * @brief Construct a new HumanDetection object
   * 
   * @param confidence_threshold Confidence threshold for detection
   */
  HumanDetection(double confidence_threshold);

  /**
   * @brief Select a frame as the current frame for processing
   * 
   */
  void set_current_frame(const cv::Mat& frame);

  /**
   * @brief A function to process the current frame to detect humans
   */
  void process_frame();

  /**
   * @brief Get the bounding boxes of detected humans
   * 
   */
  std::vector<cv::Rect> get_human_bounding_boxes() const;
};
