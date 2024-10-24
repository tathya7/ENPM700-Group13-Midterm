#include <array>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>
#include "../include/stream_data.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/utility.hpp"

class Detector{
    private:

        // Attribute for width of image
        int fwidth;
        // Attribute for height of image
        int fheight;
        // Attribute for nms threshold
        float nmsthresh;
        // Attribute for confidence threshold
        float confidenceThresh;

        float score_threshold;


    public:
        Detector();


        // Method to draw a bounding 
        void drawBbox(int classid,
                      float confidence,
                      int left,
                      int top,
                      int right,
                      int bottom,
                      cv::Mat &frame, 
                      const std::vector<std::string> &classes,
                      int uniq_id);


        cv::Mat rmOverlap(cv::Mat &frame,
                        std::vector<cv::Mat> &out_img,
                        std::vector<std::string> &classes);

        void detect(cv::CommandLineParser parser);

};


