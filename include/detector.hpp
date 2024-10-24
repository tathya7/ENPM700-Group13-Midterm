#include <array>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>
#include "../include/stream_data.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/utility.hpp"

/**
 * @brief Class for detecting humans in images using a specified model.
 */
class Detector {
    private:
        // Attribute for width of the input image
        int fwidth;
        // Attribute for height of the input image
        int fheight;
        // Attribute for NMS threshold
        float nmsthresh;
        // Attribute for confidence threshold
        float confidenceThresh;
        // Attribute for score threshold
        float score_threshold;

    public:
        /**
         * @brief Constructor for the Detector class.
         * 
         * Initializes the image dimensions and threshold values.
         */
        Detector();

        /**
         * @brief Draws a bounding box around detected objects in the image.
         * 
         * @param classid The class ID of the detected object.
         * @param confidence The confidence score of the detection.
         * @param left The left coordinate of the bounding box.
         * @param top The top coordinate of the bounding box.
         * @param right The right coordinate of the bounding box.
         * @param bottom The bottom coordinate of the bounding box.
         * @param frame The image frame where the bounding box will be drawn.
         * @param classes A vector of class names.
         * @param uniq_id A unique identifier for the detected object.
         */
        void drawBbox(int classid,
                      float confidence,
                      int left,
                      int top,
                      int right,
                      int bottom,
                      cv::Mat &frame, 
                      const std::vector<std::string> &classes,
                      int uniq_id);

        /**
         * @brief Removes overlapping bounding boxes using non-maximum suppression.
         */
        cv::Mat rmOverlap(cv::Mat &frame,
                          std::vector<cv::Mat> &out_img,
                          std::vector<std::string> &classes);

        /**
         * @brief Executes the detection algorithm on the input image or video.
         * 
         */
        void detect(cv::CommandLineParser parser);
};
