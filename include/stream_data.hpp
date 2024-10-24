#include <iostream>

#include <opencv2/opencv.hpp>
// #include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/core/utility.hpp>
#include <string>

class StreamData {
    private:

    /**
    * @brief To store the output height and width of the sreaming frame
     */

    int frame_width;
    int frame_height;
    

    public:

    // To store the input image path
    std::string image_path;
    cv::Mat frame;

    // Initializing default constructor 
    StreamData();

    // Method to set the Image path given the input path to a variable
    void setImgPath(std::string& imgpath);

    // Method to get the provided image path
    void getImgPath();

    // Method to get the input datatype from the command line
    // Returns the string of Image or Error
    std::string getImage(cv::CommandLineParser parser);

    /**
    * @brief Method to preprocess input image
    * @param frame The input frame
    * 
     */
    cv::Mat ImgProcessor(char);

    ~StreamData();
};
