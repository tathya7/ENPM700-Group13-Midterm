#pragma once

#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv4/opencv2/core/utility.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include "opencv2/core/mat.hpp"

class HumanDetector {
private:
    int frame_width = 640;         // Default width, can be changed
    int yolo_width = 640;
    int frame_height = 480;        // Default height, can be changed
    int yolo_height = 640;
    float nmsthresh = 0.4;         // Default NMS threshold
    float confidenceThresh = 0.5;  // Default confidence threshold
    float score_threshold = 0.5;   // Default score threshold
    std::string image_path;        // To store the input image path
    cv::Mat frame;                 // To hold the image frame

public:
    HumanDetector();

    std::string getImgPath(std::string& imgpath);   // Updated to return the image path

    cv::Mat ImgProcessor(cv::VideoCapture &capture_frame);

    void drawBbox(int classid,
                  float confidence,
                  int left,
                  int top,
                  int right,
                  int bottom,
                  cv::Mat &frame, 
                  const std::vector<std::string> &classes,
                  int uniq_id);

    cv::Mat rmOverlap(cv::Mat &input_frame, cv::Size &img, std::vector<cv::Mat> &out_imgs, std::vector<std::string> &classes);

    void detect(std::string &input_source);

    ~HumanDetector();
};
