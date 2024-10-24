#include "../include/detector.hpp"
#include "opencv2/core.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/operations.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/imgproc.hpp"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <fstream>


Detector::Detector(){

    fwidth = 640;
    fheight = 640;
    nmsthresh = 0.4;
    confidenceThresh = 0.45;
    score_threshold = 0.5;
}

void Detector::drawBbox(int classid,
                        float confidence,
                        int left,
                        int top,
                        int right,
                        int bottom,
                        cv::Mat &frame,
                        const std::vector<std::string> &classes,
                        int person_id){
            
            // std::string label;

            if(classid==0){

                cv::rectangle(frame, cv::Point(left,top), cv::Point(right,bottom), cv::Scalar(255, 180, 50), 3);

                // get the class name and class label
                // std::string label = cv::format("%.2f",confidence);
                std::string class_name = classes[classid];

                std::string label = "Class:" + class_name + "  Confidence:" + cv::format("%.2f", confidence) + "  ID:" + std::to_string(person_id);

            int baseline;

            cv::Size text_size = cv::getTextSize(label,
                                                cv::FONT_HERSHEY_COMPLEX,
                                                0.5,
                                                1, &baseline);

            // Find the top of the bounding box
            top = std::max(top, text_size.height);

            // Adding the label on top of the bounding box
            cv::rectangle(frame, cv::Point(left, top - round(1.5*text_size.height)),
                          cv::Point(left + round(1.5*text_size.width), top+baseline),
                          cv::Scalar(255,255,255), cv::FILLED);
            
            cv::putText(frame,label, cv::Point(left,top), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0,0,0),1);

            }
                        
}

cv::Mat Detector::rmOverlap(cv::Mat &input_img,
                         std::vector<cv::Mat> &out_imgs,
                         std::vector<std::string> &classes
                         ){

            std::vector<int> class_ids;
            std::vector<float> class_confidences;
            std::vector<cv::Rect> boxes;

            float x_factor = input_img.cols / fwidth;
            float y_factor = input_img.rows / fheight;
            float *data = (float *)out_imgs[0].data;

            int rows = 25200;
            int dimensions = 85;

            
            for (int i = 0; i<rows; ++i){
                float confidence = data[4];

                if (confidence >= confidenceThresh){
                    float *classes_scores = data+5;

                    cv::Mat scores(1, classes.size(), CV_32FC1, classes_scores);
                    cv::Point class_id;

                    double max_prob_class;
                    cv::minMaxLoc(scores, 0, &max_prob_class, 0, &class_id);

                    if (max_prob_class > score_threshold){

                        class_confidences.push_back(confidence);
                        class_ids.push_back(class_id.x);

                        float centerX = data[0];
                        float centerY = data[1];

                        float w = data[2];
                        float h = data[3];
                        int left = int((centerX - 0.5*w) * x_factor);
                        int top = int((centerY - 0.5 * h) * y_factor);
                        int width = int(w * x_factor);

                        int height = int(h * y_factor);

                        boxes.push_back(cv::Rect(left, top, width, height));
                    }
                    }

                    data += 85;

                }
                         

std::vector<int> indices;
cv::dnn::NMSBoxes(boxes, class_confidences, score_threshold,
                    nmsthresh, indices);

// int person_id = 1;
for (auto idx : indices){
    cv::Rect box = boxes[idx];
    int left = box.x;
    int top = box.y;
    int width = box.width;
    int height = box.height;
    cv::rectangle(input_img, cv::Point(left, top), cv::Point(left +width,top +height), cv::Scalar(255,178,50), 4);
    std::string label = cv::format("%.2f", class_confidences[idx]);
    label = classes[class_ids[idx]] + "|" + label;

    int baseLine;
    cv::Size label_size = getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
    int top_point = cv::max(top, label_size.height);
    // Top left corner.
    cv::Point top_left = cv::Point(left, top);
    // Bottom right corner.
    cv::Point bottom_right = cv::Point(left + label_size.width, top + label_size.height + baseLine);
    // Draw white rectangle.
    cv::rectangle(input_img, top_left, bottom_right, cv::Scalar(0,0,0), cv::FILLED);
    // Put the label on the black rectangle.
    cv::putText(input_img, label, cv::Point(left, top + label_size.height), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,255,255), 3);

    }

    return input_img;
}



// Implementation of the detect method
void Detector::detect(cv::CommandLineParser parser){
    std::vector<std::string> classes;
    std::string class_path = "./models/coco.names";
    std::string model_path = "./models/yolov5s.onnx";

    // Read class names from the file
    std::ifstream read_input(class_path);
    std::string text;
    while ( read_input >> text){
        getline(read_input, text);
        classes.push_back(text);
    }

    // Load the YOLO model
    cv::dnn::Net yolo_model = cv::dnn::readNet(model_path);

    StreamData input; // Ensure StreamData is defined and accessible
    cv::VideoCapture capture;
    cv::Mat frame, blob_img;

    try {
        std::string input_path = input.getImage(parser);
        input.setImgPath(input_path);
        frame = input.ImgProcessor('r');

        if (frame.empty()) {
            std::cout << "Could not load image" << std::endl;
            return; // Use return instead of break
        }

        // Prepare the image for the model
        cv::dnn::blobFromImage(frame, blob_img, 1 / 255.0, cv::Size(fwidth, fheight), cv::Scalar(0, 0, 0), true, false);

        // Set the input to the model
        yolo_model.setInput(blob_img);

        std::vector<cv::Mat> out_imgs;
        std::vector<cv::Mat> detections;
        yolo_model.forward(out_imgs, yolo_model.getUnconnectedOutLayersNames());
        
        detections = out_imgs;

        cv::Mat temp = frame;
        // Call the method to remove overlaps
        cv::Mat final_img = rmOverlap(temp, detections, classes);

        // Performance measurement
        std::vector<double> layer_time;
        double freq = cv::getTickFrequency() / 1000;
        double time = yolo_model.getPerfProfile(layer_time) / freq;
        std::string label = cv::format("Inference time: %.2f ms", time);
        cv::putText(final_img, label, cv::Point(0, 15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255));

        // Display the result
        cv::imshow("Human Detection", final_img);
        cv::waitKey(0);
        cv::destroyAllWindows();
        
    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }
}


