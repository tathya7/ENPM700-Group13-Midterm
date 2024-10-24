#include "../include/stream_data.hpp"
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/core/utility.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/videoio.hpp>
#include <string>

/**
 * @brief Constructor for the StreamData class.
 * 
 * Initializes the frame height and width.
 */
StreamData::StreamData() {
    frame_height = 640;
    frame_width = 480;
}

/**
 * @brief Sets the image path for processing.
 * 
 * @param imgpath A string reference representing the path of the image.
 */
void StreamData::setImgPath(std::string& imgpath) {
    image_path = imgpath;
}

/**
 * @brief Gets the image path from the command line parser.
 * 
 * @param parser A reference to the command line parser.
 * @return std::string The path to the input image, or "Invalid Input" if not found.
 */
std::string StreamData::getImage(cv::CommandLineParser parser) {
    if (parser.has("image")) {
        image_path = parser.get<std::string>("image");
        std::cout << image_path << std::endl;
        return image_path;
    } else {
        std::cout << "Not a valid input" << std::endl;
        return "Invalid Input";
    }
}

/**
 * @brief Processes the image based on the specified mode.
 * 
 * @param mode A character specifying the processing mode. 'r' for reading the image.
 * @return cv::Mat The processed image.
 */
cv::Mat StreamData::ImgProcessor(char mode) {
    if (mode == 'r') {
        frame = cv::imread(image_path);
        return frame;
    }
}

/**
 * @brief Destructor for the StreamData class.
 */
StreamData::~StreamData() {}
