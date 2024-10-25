#pragma once

#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

class HumanAvoidance {
  
  private:
    // int SIZE;
    // int object_id;
    // int float_id;
    const unsigned int averageHeight = 175; // Average human height in cm

  public:
    int frame_id;

    // Constructor and Destructor
    HumanAvoidance();

    // Calculates distance of the detected human from the camera
    float calculate_distance(int box_h, int frame_h);

    // Transforms human coordinates to robot coordinate system
    std::vector<float> camera2robot(float z, cv::Rect box, cv::Mat frame);

    // void avoidance_(cv::rect box, cv::Mat frame);

    ~HumanAvoidance();

};
