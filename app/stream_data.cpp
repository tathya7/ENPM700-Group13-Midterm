
#include "../include/stream_data.hpp"
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/core/utility.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/videoio.hpp>
#include <string>

StreamData::StreamData(){
    frame_height = 640;
    frame_width = 480;
}

void StreamData::setImgPath(std::string& imgpath){
    image_path = imgpath;
    }

std::string StreamData::getImage(cv::CommandLineParser parser){
    if(parser.has("image")){
        
        image_path = parser.get<std::string>("image");
        std::cout<<image_path<<std::endl;
        return image_path;

    }

    else {
    std::cout<< "Not a valid input"<<std::endl;
    return "Invalid Input";
    }
}

cv::Mat StreamData::ImgProcessor(char mode){

    if(mode =='r'){

        frame = cv::imread(image_path);
        // cv::VideoCapture capture;
        // capture.open(image_path);
        return frame;
    }

    // else if (mode == 'w') {
    //     cv::imwrite("../output/Result.jpg", frame);
    //     return cv::VideoCapture();
    // }

//     else {
//     std::cout<<"Error Retrieving Image" <<std::endl;
//     return cv::VideoCapture();
//     }
}

StreamData::~StreamData() {}





