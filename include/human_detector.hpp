/**
 * @file human_detector.hpp
 * @author Mohammed Munawwar (mmunawwa@umd.edu)
 * @brief Detection code implementation to get the output result of the algorithm
 * @version 1.0
 * @date 2024-10-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include <array>
#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>
#include <opencv4/opencv2/core/utility.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <string>
#include <vector>

#include "opencv2/core/mat.hpp"

/**
 * @brief A class for detecting humans in images or video frames
 *
 * The HumanDetector class provides functionality for processing images,
 * detecting humans, and drawing bounding boxes around detected humans.
 * It uses the model and includes methods for non-maximum
 * suppression and overlap removal.
 */

class HumanDetector {
 private:
  int frame_width = 640;  // Default width, can be changed
  int yolo_width = 640;
  int frame_height = 480;  // Default height, can be changed
  int yolo_height = 640;
  float nmsthresh = 0.4;         // Default NMS threshold
  float confidenceThresh = 0.5;  // Default confidence threshold
  float score_threshold = 0.5;   // Default score threshold
  std::string image_path;        // To store the input image path
  cv::Mat frame;                 // To hold the image frame

 public:
  HumanDetector();

  /**
   * @brief Get the path of the input image
   * @param imgpath Reference to the string containing the image path
   * @return std::string The image path
   */
  std::string getImgPath(std::string &imgpath);

  /**
   * @brief Process the input frame for human detection
   * @param capture_frame Reference to the VideoCapture object containing the
   * frame
   * @return cv::Mat Processed frame
   */
  cv::Mat ImgProcessor(cv::VideoCapture &capture_frame);

  /**
   * @brief Draw bounding box around detected human
   * @param classid ID of the detected class
   * @param confidence Confidence score of the detection
   * @param left Left coordinate of the bounding box
   * @param top Top coordinate of the bounding box
   * @param right Right coordinate of the bounding box
   * @param bottom Bottom coordinate of the bounding box
   * @param frame Reference to the frame to draw on
   * @param classes Vector of class names
   * @param uniq_id Unique identifier for the detection
   */
  void drawBbox(int classid, float confidence, int left, int top, int right,
                int bottom, cv::Mat &frame,
                const std::vector<std::string> &classes, int uniq_id);

  /**
   * @brief Remove overlapping bounding boxes
   * @param input_frame Reference to the input frame
   * @param img Size of the image
   * @param out_imgs Vector of output images
   * @param classes Vector of class names
   * @return Frame with overlapping boxes removed
   */
  cv::Mat rmOverlap(cv::Mat &input_frame, cv::Size &img,
                    std::vector<cv::Mat> &out_imgs,
                    std::vector<std::string> &classes);

  /**
   * @brief Perform human detection on the input source
   * @param input_source Reference to the string containing the input source
   * path
   */
  void detect(std::string &input_source, bool is_test_mode);

  ~HumanDetector();
};
