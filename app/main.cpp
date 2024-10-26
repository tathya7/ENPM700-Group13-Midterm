#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>
#include <ostream>
#include "human_detector.hpp"
#include "human_avoidance.hpp"

    
int main(int argc, char** argv) {
    std::string camera_device = argv[1];

    HumanDetector detection;

    while (1) {
     std::vector<cv::Mat> outs = detection.detect(camera_device);
     std::cout<<outs.size()<<std::endl;
     }

    return 0;

}